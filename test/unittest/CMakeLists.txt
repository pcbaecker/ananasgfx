cmake_minimum_required(VERSION 3.6)
project(AnanasGfxUnitTest)

find_package(Threads REQUIRED)

add_definitions(-D__UNITTEST__)
file(GLOB_RECURSE HEADER_FILES ../../include/ananasgfx/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ../../src/*.cpp ./*.cpp)

add_executable(AnanasGfxUnitTest ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(AnanasGfxUnitTest freetype EasyException Threads::Threads ${CMAKE_DL_LIBS})