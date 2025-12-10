#include "FfmpegRtspClient.h"
#include <iostream>
#include <chrono>

extern "C" {
  #include <libavformat/avformat.h>
  #include <libavcodec/avcodec.h>     // <-- needed for avcodec_* and AVCodecContext
  #include <libavutil/opt.h>
  #include <libavutil/imgutils.h>     // <-- needed for av_image_* helpers
  #include <libswscale/swscale.h>
}

FfmpegRtspClient::FfmpegRtspClient(const std::string& url, FrameProcessor& sink)
    : url_(url), out_(sink) {}

FfmpegRtspClient::~FfmpegRtspClient() { stop(); }

void FfmpegRtspClient::setUrl(const std::string& u) {
    std::lock_guard<std::mutex> lk(urlMtx_);
    url_ = u;
}

void FfmpegRtspClient::start() {
    if (running_.exchange(true)) return;
    th_ = std::thread(&FfmpegRtspClient::run, this);
}

void FfmpegRtspClient::stop() {
    if (!running_.exchange(false)) return;
    if (th_.joinable()) th_.join();
}

static void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void FfmpegRtspClient::run() {
    // Alloc once
    AVFrame* f = av_frame_alloc();
    AVFrame* rgb = av_frame_alloc();
    AVPacket* pkt = av_packet_alloc();

    while (running_) {
        std::string url; { std::lock_guard<std::mutex> lk(urlMtx_); url = url_; }

        AVFormatContext* fmt = nullptr;
        AVCodecContext* dec = nullptr;
        SwsContext* sws = nullptr;
        uint8_t* rgbBuf = nullptr;

        auto cleanup = [&](){
            if (sws) sws_freeContext(sws);
            if (dec) avcodec_free_context(&dec);
            if (fmt) { avformat_close_input(&fmt); fmt = nullptr; }
            if (rgb) { if (rgbBuf) av_free(rgbBuf); rgbBuf = nullptr; }
        };

        // --- Open with low-latency demux options ---
        AVDictionary* opts = nullptr;
        av_dict_set(&opts, "rtsp_transport", "udp", 0);     // use "udp" on LAN if you want even lower latency
        av_dict_set(&opts, "max_delay", "0", 0);       // 100 ms
        av_dict_set(&opts, "probesize", "32768", 0);
        av_dict_set(&opts, "analyzeduration", "0", 0);

        if (avformat_open_input(&fmt, url.c_str(), nullptr, &opts) < 0) {
            out_.setStreamAvailable(false);
            av_dict_free(&opts);
            std::cerr << "[RTSP] open failed, retry in 1s\n";
            sleep_ms(1000);
            continue;
        }
        out_.setStreamAvailable(true);
        av_dict_free(&opts);
        fmt->flags |= AVFMT_FLAG_NOBUFFER;                  // ffplay -fflags nobuffer

        if (avformat_find_stream_info(fmt, nullptr) < 0) {
            out_.setStreamAvailable(false);
            std::cerr << "[RTSP] find_stream_info failed\n";
            cleanup(); sleep_ms(500); continue;
        }

        int vindex = av_find_best_stream(fmt, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
        if (vindex < 0) {
            out_.setStreamAvailable(false);
            std::cerr << "[RTSP] no video stream\n";
            cleanup(); sleep_ms(500); continue;
        }

        const AVCodecParameters* par = fmt->streams[vindex]->codecpar;
        const AVCodec* codec = avcodec_find_decoder(par->codec_id);
        if (!codec) { 
            out_.setStreamAvailable(false);
            std::cerr << "[RTSP] decoder not found\n"; 
            cleanup(); sleep_ms(500); continue; 
        }

        dec = avcodec_alloc_context3(codec);
        avcodec_parameters_to_context(dec, par);
        dec->thread_type = 0;
        dec->thread_count = 1;
        dec->flags |= AV_CODEC_FLAG_LOW_DELAY;

        if (avcodec_open2(dec, codec, nullptr) < 0) {
            out_.setStreamAvailable(false);
            std::cerr << "[RTSP] open decoder failed\n";
            cleanup(); sleep_ms(500); continue;
        }

        // --- Read/decode/convert loop ---
        while (running_ && av_read_frame(fmt, pkt) >= 0) {
            if (pkt->stream_index != vindex) { av_packet_unref(pkt); continue; }
            if (avcodec_send_packet(dec, pkt) == 0) {
                while (avcodec_receive_frame(dec, f) == 0) {
                    const int w = f->width, h = f->height;
                    if (w <= 0 || h <= 0) { av_frame_unref(f); continue; }

                    if (!sws || rgb->width != w || rgb->height != h) {
                        if (sws) sws_freeContext(sws);
                        sws = sws_getContext(w, h, (AVPixelFormat)f->format,
                                             w, h, AV_PIX_FMT_RGB24,
                                             SWS_BILINEAR, nullptr, nullptr, nullptr);
                        if (rgbBuf) { av_free(rgbBuf); rgbBuf = nullptr; }
                        int bufSz = av_image_get_buffer_size(AV_PIX_FMT_RGB24, w, h, 1);
                        rgbBuf = (uint8_t*)av_malloc(bufSz);
                        av_image_fill_arrays(rgb->data, rgb->linesize, rgbBuf,
                                             AV_PIX_FMT_RGB24, w, h, 1);
                        rgb->width = w; rgb->height = h;
                    }

                    sws_scale(sws, f->data, f->linesize, 0, h, rgb->data, rgb->linesize);
                    out_.updateFrame(rgb->data[0], rgb->width, rgb->height);
                    av_frame_unref(f);
                }
            }
            av_packet_unref(pkt);
        }

        cleanup();
        if (running_) sleep_ms(250); // backoff before re-open
    }

    if (pkt) av_packet_free(&pkt);
    if (f) av_frame_free(&f);
    if (rgb) av_frame_free(&rgb);
}
