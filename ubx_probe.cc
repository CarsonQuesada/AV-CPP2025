#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>

static speed_t toSpeedT(int baud){
  switch(baud){
    case 9600: return B9600;
    case 38400: return B38400;
    case 57600: return B57600;
    case 115200: return B115200;
    default: return B115200;
  }
}

static int openSerial(const std::string& dev, int baud){
  int fd = ::open(dev.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
  if (fd < 0) { perror("open"); return -1; }
  termios tio{};
  if (tcgetattr(fd, &tio) < 0) { perror("tcgetattr"); ::close(fd); return -1; }
  cfmakeraw(&tio);
  tio.c_cflag |= (CLOCAL | CREAD);
  tio.c_cflag &= ~CRTSCTS;
  tio.c_cflag &= ~PARENB; tio.c_cflag &= ~CSTOPB;
  tio.c_cflag &= ~CSIZE;  tio.c_cflag |= CS8;
  cfsetispeed(&tio, toSpeedT(baud));
  cfsetospeed(&tio, toSpeedT(baud));
  tio.c_cc[VMIN]=0; tio.c_cc[VTIME]=1; // nonblocking-ish
  if (tcsetattr(fd, TCSANOW, &tio) < 0) { perror("tcsetattr"); ::close(fd); return -1; }
  int flags = fcntl(fd, F_GETFL, 0);
  fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
  return fd;
}

static void ubxChecksum(const uint8_t* data, size_t len, uint8_t& a, uint8_t& b){
  a=0; b=0; for(size_t i=0;i<len;i++){ a += data[i]; b += a; }
}

static bool sendUBX(int fd, uint8_t cls, uint8_t id, const std::vector<uint8_t>& payload){
  std::vector<uint8_t> pkt;
  pkt.reserve(8 + payload.size());
  pkt.push_back(0xB5); pkt.push_back(0x62);
  pkt.push_back(cls);  pkt.push_back(id);
  uint16_t len = (uint16_t)payload.size();
  pkt.push_back(len & 0xFF); pkt.push_back((len >> 8) & 0xFF);
  pkt.insert(pkt.end(), payload.begin(), payload.end());
  uint8_t ckA, ckB;
  ubxChecksum(&pkt[2], 4 + payload.size(), ckA, ckB); // class,id,lenL,lenH,payload
  pkt.push_back(ckA); pkt.push_back(ckB);

  ssize_t n = ::write(fd, pkt.data(), pkt.size());
  if (n != (ssize_t)pkt.size()) { perror("write"); return false; }
  tcdrain(fd);
  return true;
}

static int64_t nowMs(){
  using namespace std::chrono;
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

// Wait for UBX-ACK {class=0x05, id=0x01/0x00, len=2, payload[0]=cls, payload[1]=id}
static int waitAck(int fd, uint8_t expect_cls, uint8_t expect_id, int timeout_ms){
  int64_t end = nowMs() + timeout_ms;
  std::vector<uint8_t> buf; buf.reserve(1024);
  while (nowMs() < end){
    uint8_t tmp[256];
    ssize_t n = ::read(fd, tmp, sizeof(tmp));
    if (n > 0) buf.insert(buf.end(), tmp, tmp+n);

    for (size_t i=0; i + 6 <= buf.size(); ++i){
      if (buf[i]==0xB5 && buf[i+1]==0x62 && buf[i+2]==0x05){ // ACK class
        uint8_t ackid = buf[i+3];
        uint16_t len  = buf[i+4] | (buf[i+5]<<8);
        size_t need   = i + 6 + len + 2;
        if (need > buf.size()) continue; // wait for more bytes

        // (optional) checksum verify
        uint8_t ckA, ckB;
        ubxChecksum(&buf[i+2], 4+len, ckA, ckB);
        if (buf[need-2]!=ckA || buf[need-1]!=ckB) continue;

        if ((ackid==0x01 || ackid==0x00) && len==2){
          if (buf[i+6]==expect_cls && buf[i+7]==expect_id){
            return (ackid==0x01) ? 1 : -1; // 1=ACK, -1=NAK
          }
        }
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return 0; // timeout
}

// Force UBX+NMEA in/out at current baud (CFG-PRT rescue)
static bool forceUbxNmeaIO(int fd, int baud){
  std::vector<uint8_t> p(20,0);
  p[0]=1; // UART1
  uint32_t mode = 0x000008D0; // 8N1
  p[4]=mode&0xFF; p[5]=(mode>>8)&0xFF; p[6]=(mode>>16)&0xFF; p[7]=(mode>>24)&0xFF;
  uint32_t b=(uint32_t)baud;
  p[8]=b&0xFF; p[9]=(b>>8)&0xFF; p[10]=(b>>16)&0xFF; p[11]=(b>>24)&0xFF;
  uint16_t inMask=0x0003, outMask=0x0003; // UBX|NMEA in/out
  p[12]=inMask&0xFF; p[13]=(inMask>>8)&0xFF; p[14]=outMask&0xFF; p[15]=(outMask>>8)&0xFF;
  tcflush(fd, TCIFLUSH);
  if (!sendUBX(fd, 0x06, 0x00, p)) return false; // CFG-PRT
  int r = waitAck(fd, 0x06, 0x00, 1200);
  std::cout << "CFG-PRT rescue: " << (r==1?"ACK OK": (r==-1?"NAK":"TIMEOUT")) << "\n";
  return r==1;
}

int main(int argc, char** argv){
  if (argc < 4){
    std::cerr << "Usage: " << argv[0] << " /dev/ttyS0 9600 rate5|rate10|rescue\n";
    return 1;
  }
  std::string dev = argv[1];
  int baud = std::stoi(argv[2]);
  std::string cmd = argv[3];

  int fd = openSerial(dev, baud);
  if (fd < 0) return 2;

  if (cmd == "rescue"){
    (void)forceUbxNmeaIO(fd, baud);
    ::close(fd);
    return 0;
  }

  // Always try to ensure UBX/NMEA IO first (silent if already fine)
  (void)forceUbxNmeaIO(fd, baud);

  if (cmd == "rate5" || cmd == "rate10"){
    int hz = (cmd=="rate5")?5:10;
    if (hz>10) hz=10; if (hz<1) hz=1;
    int meas_ms = 1000 / hz; // 5=>200, 10=>100
    std::vector<uint8_t> p(6,0);
    uint16_t meas=meas_ms, nav=1, tref=1;
    p[0]=meas&0xFF; p[1]=(meas>>8)&0xFF;
    p[2]=nav&0xFF;  p[3]=(nav>>8)&0xFF;
    p[4]=tref&0xFF; p[5]=(tref>>8)&0xFF;

    tcflush(fd, TCIFLUSH);
    if (!sendUBX(fd, 0x06, 0x08, p)) { std::cerr<<"write CFG-RATE failed\n"; ::close(fd); return 3; }
    int r = waitAck(fd, 0x06, 0x08, 1500);
    std::cout << "CFG-RATE("<<hz<<"Hz): " << (r==1?"ACK OK": (r==-1?"NAK":"TIMEOUT")) << "\n";
    ::close(fd);
    return (r==1)?0:4;
  }

  std::cerr << "Unknown command\n";
  ::close(fd);
  return 5;
}
