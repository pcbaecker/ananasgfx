set(CMAKE_HOST_SYSTEM "Linux-4.15.0-1026-gcp")
set(CMAKE_HOST_SYSTEM_NAME "Linux")
set(CMAKE_HOST_SYSTEM_VERSION "4.15.0-1026-gcp")
set(CMAKE_HOST_SYSTEM_PROCESSOR "x86_64")

include("/emsdk_portable/sdk/cmake/Modules/Platform/Emscripten.cmake")

set(CMAKE_SYSTEM "Emscripten-1")
set(CMAKE_SYSTEM_NAME "Emscripten")
set(CMAKE_SYSTEM_VERSION "1")
set(CMAKE_SYSTEM_PROCESSOR "x86")

set(CMAKE_CROSSCOMPILING "TRUE")

set(CMAKE_SYSTEM_LOADED 1)
