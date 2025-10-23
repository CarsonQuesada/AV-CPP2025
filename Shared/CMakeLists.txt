# Header-only "shared" target
add_library(shared INTERFACE)

# Export the REPO ROOT so includes like "Shared/Message.h" work
target_include_directories(shared
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
