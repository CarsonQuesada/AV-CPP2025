cmake_minimum_required(VERSION 3.20)
project(AV_CPP2025 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Let subprojects know if you want to force dependency fetching (for testing)
option(DEPS_FORCE_FETCH "Ignore local deps and always fetch/build (for testing)" OFF)

add_subdirectory(shared)
add_subdirectory(TCPClient)
#add_subdirectory(Vehicle)
