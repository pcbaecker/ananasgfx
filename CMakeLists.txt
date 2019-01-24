cmake_minimum_required(VERSION 3.12)

project(AnanasGfx)
option(USE_DOC "Build documentation" ON)
option(USE_EXAMPLES "Use examples" ON)

add_subdirectory(dependencies/freetype2)

set(EE_USE_TESTS OFF CACHE BOOL "Disable easy-exception tests" FORCE)
set(EE_USE_EXAMPLES OFF CACHE BOOL "Disable easy-exception examples" FORCE)
add_subdirectory(dependencies/easy-exception)

### Currently android seems to be not able to handle the c++17 definition in cmake
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(CMAKE_CXX_STANDARD 17)
endif()

### Source files
include_directories(
        include
        dependencies/glfw/include
        dependencies/glm
        dependencies/stb
        dependencies/freetype2/include
        dependencies/easy-exception/include
        ${ANDROID_NDK}/sources/android
)
file(GLOB_RECURSE HEADER_FILES "include/*.hpp" "include/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.c" ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

### Glfw only for Desktop
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin-*")
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(dependencies/glfw)
endif()

### The library
add_library(AnanasGfx STATIC ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(AnanasGfx PROPERTIES LINKER_LANGUAGE CXX)

### Link desktop specific
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin-*")
    target_link_libraries (AnanasGfx EasyException glfw freetype ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
endif()

### Link android specific
if (${CMAKE_SYSTEM_NAME} MATCHES "Android")
    find_library(log-lib log)
    find_library(android-lib android)
    target_link_libraries (AnanasGfx ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}
            ${log-lib} ${android-lib} GLESv3 EGL)
endif()

### Examples
if(USE_EXAMPLES)
    add_subdirectory(examples)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin-*")
    add_subdirectory(test/unittest)
endif()
### Documentation
#if (USE_DOC)
#    add_subdirectory(docs)
#endif()



