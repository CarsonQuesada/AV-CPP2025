project(TCPClient_App LANGUAGES C CXX)
include(FetchContent)

# Portable EXE on MinGW
if(MINGW)
  add_link_options(-static -static-libgcc -static-libstdc++)
endif()
set(BUILD_SHARED_LIBS OFF)

# ---- Paths relative to this subdir ----
set(APP_DIR   "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR   "${APP_DIR}/src")
set(IMGUI_DIR "${APP_DIR}/Dependencies/imgui")
set(GLAD_DIR  "${APP_DIR}/Dependencies/glad")
set(STB_DIR   "${APP_DIR}/Dependencies/stb_image")

file(GLOB TCPCLIENT_SRC CONFIGURE_DEPENDS
  "${SRC_DIR}/*.cpp"
  "${SRC_DIR}/UI/*.cpp"
  "${SRC_DIR}/UI/Panels/*.cpp"
  "${SRC_DIR}/video/*.cpp"
)
list(APPEND TCPCLIENT_SRC
  "${GLAD_DIR}/src/glad.c"
  "${IMGUI_DIR}/imgui.cpp"
  "${IMGUI_DIR}/imgui_draw.cpp"
  "${IMGUI_DIR}/imgui_tables.cpp"
  "${IMGUI_DIR}/imgui_widgets.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
  "${STB_DIR}/stb_image.cpp"
)

add_executable(TCPClient ${TCPCLIENT_SRC})
target_include_directories(TCPClient PRIVATE
  "${APP_DIR}"
  "${SRC_DIR}"
  "${SRC_DIR}/UI"
  "${SRC_DIR}/UI/Panels"
  "${SRC_DIR}/video"
  "${IMGUI_DIR}"
  "${IMGUI_DIR}/backends"
  "${GLAD_DIR}/include"
  "${STB_DIR}"
)
target_compile_definitions(TCPClient PRIVATE
  IMGUI_IMPL_OPENGL_LOADER_CUSTOM
  GLFW_INCLUDE_NONE
  GLFW_STATIC
  CURL_STATICLIB
  $<$<CONFIG:Debug>:DEBUG>
)

# ---- OpenGL ----
find_package(OpenGL REQUIRED)
target_link_libraries(TCPClient PRIVATE OpenGL::GL)

# ---- GLFW: local if present, else fetch ----
set(GLFW_LOCAL_INCLUDE "${APP_DIR}/Dependencies/glfw/include")
set(GLFW_LOCAL_LIB     "${APP_DIR}/Dependencies/glfw/lib-mingw/libglfw3.a")
if(NOT DEPS_FORCE_FETCH AND EXISTS "${GLFW_LOCAL_INCLUDE}" AND EXISTS "${GLFW_LOCAL_LIB}")
  add_library(glfw_local STATIC IMPORTED GLOBAL)
  set_target_properties(glfw_local PROPERTIES
    IMPORTED_LOCATION "${GLFW_LOCAL_LIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW_LOCAL_INCLUDE}"
  )
  add_library(glfw ALIAS glfw_local)
else()
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
  set(GLFW_LIBRARY_TYPE STATIC CACHE STRING "" FORCE)
  FetchContent_Declare(glfw_src
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
  )
  FetchContent_MakeAvailable(glfw_src) # provides 'glfw'
endif()

# ---- cURL: local if present, else fetch (Schannel, minimal) ----
set(CURL_LOCAL_INCLUDE "${APP_DIR}/Dependencies/curl/include")
set(CURL_LOCAL_LIB "")
foreach(cand libcurl.a libcurl_imp.a libcurl_static.a)
  if(EXISTS "${APP_DIR}/Dependencies/curl/lib/${cand}")
    set(CURL_LOCAL_LIB "${APP_DIR}/Dependencies/curl/lib/${cand}")
    break()
  endif()
endforeach()

if(NOT DEPS_FORCE_FETCH AND EXISTS "${CURL_LOCAL_INCLUDE}" AND EXISTS "${CURL_LOCAL_LIB}")
  add_library(curl_local STATIC IMPORTED GLOBAL)
  set_target_properties(curl_local PROPERTIES
    IMPORTED_LOCATION "${CURL_LOCAL_LIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${CURL_LOCAL_INCLUDE}"
  )
  add_library(CURL::libcurl ALIAS curl_local)
else()
  # IMPORTANT: cURL uses CMAKE_USE_* flags, not CURL_USE_*
  set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
  set(BUILD_CURL_EXE   OFF CACHE BOOL "" FORCE)

  # Pick Windows native TLS and turn OFF everything else
  set(CMAKE_USE_SCHANNEL ON  CACHE BOOL "" FORCE)
  set(CMAKE_USE_OPENSSL  OFF CACHE BOOL "" FORCE)
  set(CMAKE_USE_MBEDTLS  OFF CACHE BOOL "" FORCE)
  set(CMAKE_USE_GNUTLS   OFF CACHE BOOL "" FORCE)
  set(CMAKE_USE_WOLFSSL  OFF CACHE BOOL "" FORCE)
  set(CMAKE_USE_BEARSSL  OFF CACHE BOOL "" FORCE)
  set(CMAKE_USE_NSS      OFF CACHE BOOL "" FORCE)
  set(CMAKE_USE_MESALINK OFF CACHE BOOL "" FORCE)

  # Trim optional features to avoid crypto code paths
  set(HTTP_ONLY          ON  CACHE BOOL "" FORCE)
  set(CURL_ZLIB          OFF CACHE BOOL "" FORCE)
  set(CURL_BROTLI        OFF CACHE BOOL "" FORCE)
  set(CURL_ZSTD          OFF CACHE BOOL "" FORCE)
  set(CURL_DISABLE_LDAP  ON  CACHE BOOL "" FORCE)
  set(CURL_DISABLE_NTLM  ON  CACHE BOOL "" FORCE)  # avoids md4/ntlm sources

  include(FetchContent)
  FetchContent_Declare(curl_src
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG curl-8_10_1
  )
  FetchContent_MakeAvailable(curl_src)

  if(NOT TARGET CURL::libcurl AND TARGET libcurl_static)
    add_library(CURL::libcurl ALIAS libcurl_static)
  elseif(NOT TARGET CURL::libcurl AND TARGET libcurl)
    add_library(CURL::libcurl ALIAS libcurl)
  elseif(NOT TARGET CURL::libcurl)
    message(FATAL_ERROR "libcurl target not found")
  endif()
endif()

# ---- Link third-party + shared + system libs ----
target_link_libraries(TCPClient PRIVATE shared)
target_link_libraries(TCPClient PRIVATE glfw CURL::libcurl shared)
target_link_libraries(TCPClient PRIVATE
  ws2_32 crypt32 bcrypt gdi32 dinput8 dxguid
)
if(MINGW)
  target_link_libraries(TCPClient PRIVATE winmm uxtheme)
endif()

# --- RTSP toggle ---
option(ENABLE_RTSP "Enable RTSP via FFmpeg" OFF)

if (ENABLE_RTSP)
  if (NOT DEFINED FFMPEG_ROOT)
    message(FATAL_ERROR "ENABLE_RTSP=ON but FFMPEG_ROOT is not set")
  endif()

  # Headers
  target_include_directories(TCPClient PRIVATE
    "${FFMPEG_ROOT}/include"
  )

  # 1. build-time link
  target_link_libraries(TCPClient PRIVATE
    "${FFMPEG_ROOT}/lib/libavformat.dll.a"
    "${FFMPEG_ROOT}/lib/libavcodec.dll.a"
    "${FFMPEG_ROOT}/lib/libavutil.dll.a"
    "${FFMPEG_ROOT}/lib/libswscale.dll.a"
  )

  # 2. runtime copy
  if (FFMPEG_COPY_DLLS)
    file(GLOB FFMPEG_DLLS
      "${FFMPEG_ROOT}/bin/avformat-*.dll"
      "${FFMPEG_ROOT}/bin/avcodec-*.dll"
      "${FFMPEG_ROOT}/bin/avutil-*.dll"
      "${FFMPEG_ROOT}/bin/swscale-*.dll"
      "${FFMPEG_ROOT}/bin/swresample-*.dll"
    )

    add_custom_command(TARGET TCPClient POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${FFMPEG_DLLS} "$<TARGET_FILE_DIR:TCPClient>"
      COMMENT "Copying minimal FFmpeg DLLs"
      COMMAND_EXPAND_LISTS
    )
  endif()


  add_compile_definitions(ENABLE_RTSP=1)
endif()

# Output + assets
set_target_properties(TCPClient PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${APP_DIR}/build"
  OUTPUT_NAME "TCPClient"
)
add_custom_command(TARGET TCPClient POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${APP_DIR}/assets"
          "$<TARGET_FILE_DIR:TCPClient>/assets"
)
