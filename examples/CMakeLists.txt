cmake_minimum_required(VERSION 3.6)

file(GLOB_RECURSE HEADER_FILES src/*.hpp src/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.c)

### Desktop
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Android")
    add_executable(AnanasGfxExamples ${SOURCE_FILES} ${HEADER_FILES})
    target_link_libraries(AnanasGfxExamples EasyException AnanasGfx)
endif()

### Android
if(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    add_library(AnanasGfxExamples SHARED ${SOURCE_FILES} ${HEADER_FILES} src/primitives2d/Primitives2d.cpp)
    target_link_libraries (AnanasGfxExamples EasyException -Wl,--whole-archive AnanasGfx -Wl,--no-whole-archive)
endif()

### Emscripten
if (DEFINED EMSCRIPTEN)
    # set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(AnanasGfxExamples
            PROPERTIES SUFFIX ".html"
            LINK_FLAGS " --bind -s USE_GLFW=3 -s WASM=1 -s USE_WEBGL2=1 -s DISABLE_EXCEPTION_CATCHING=0 -s BINARYEN_TRAP_MODE='clamp' -g4 --preload-file resource")
endif ()


