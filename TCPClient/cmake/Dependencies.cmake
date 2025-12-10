# ---- Optional FFmpeg (RTSP) ----------------------------------------------
option(ENABLE_RTSP "Enable RTSP client via FFmpeg" OFF)
if (ENABLE_RTSP)
  if (NOT DEFINED FFMPEG_ROOT)
    message(FATAL_ERROR
      "ENABLE_RTSP=ON but FFMPEG_ROOT is not set. "
      "Set FFMPEG_ROOT to a folder containing include/ and lib/ (prebuilt FFmpeg).")
  endif()

  set(_FF_INC "${FFMPEG_ROOT}/include")
  set(_FF_LIB "${FFMPEG_ROOT}/lib")
  set(_FF_BIN "${FFMPEG_ROOT}/bin")

  if (NOT (EXISTS "${_FF_INC}" AND EXISTS "${_FF_LIB}"))
    message(FATAL_ERROR
      "FFMPEG_ROOT='${FFMPEG_ROOT}' is missing include/ and/or lib/. "
      "Expected layout:\n"
      "  ${FFMPEG_ROOT}/include/libavformat/avformat.h\n"
      "  ${FFMPEG_ROOT}/lib/libavformat.dll.a (MinGW) or avformat.lib (MSVC)\n")
  endif()

  # Helper to create imported targets
  function(_ff_add tgt basename)
    if (MSVC)
      find_library(${tgt}_LIB NAMES "${basename}.lib" PATHS "${_FF_LIB}" NO_DEFAULT_PATH)
    else() # MinGW
      find_library(${tgt}_LIB NAMES "lib${basename}.dll.a" "${basename}" "lib${basename}"
                   PATHS "${_FF_LIB}" NO_DEFAULT_PATH)
    endif()
    if (NOT ${tgt}_LIB)
      message(FATAL_ERROR "FFmpeg lib '${basename}' not found in ${_FF_LIB}")
    endif()
    add_library(${tgt} UNKNOWN IMPORTED)
    set_target_properties(${tgt} PROPERTIES
      IMPORTED_LOCATION "${${tgt}_LIB}"
      INTERFACE_INCLUDE_DIRECTORIES "${_FF_INC}")
  endfunction()

  _ff_add(ffmpeg::avutil   avutil)
  _ff_add(ffmpeg::avcodec  avcodec)
  _ff_add(ffmpeg::avformat avformat)
  _ff_add(ffmpeg::swscale  swscale)

  add_compile_definitions(ENABLE_RTSP=1)
  set(HAVE_FFMPEG ON)
else()
  set(HAVE_FFMPEG OFF)
endif()
# --------------------------------------------------------------------------
