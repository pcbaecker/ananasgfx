cmake_minimum_required(VERSION 3.12)
project(AnanasGfxIntegrationTest)

include_directories(../../include)
file(GLOB_RECURSE HEADER_FILES ./*.hpp)
file(GLOB_RECURSE SOURCE_FILES ./*.cpp)

add_executable(AnanasGfxIntegrationTest ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(AnanasGfxIntegrationTest AnanasGfx freetype EasyException ${CMAKE_DL_LIBS} ${OpenCV_LIBS})