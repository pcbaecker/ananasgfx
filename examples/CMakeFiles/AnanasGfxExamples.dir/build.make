# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /src/cmake-build-emscripten

# Include any dependencies generated for this target.
include examples/CMakeFiles/AnanasGfxExamples.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/AnanasGfxExamples.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/AnanasGfxExamples.dir/flags.make

examples/CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/flags.make
examples/CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/includes_CXX.rsp
examples/CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.o: ../examples/src/Overview.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.o"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.o -c /src/examples/src/Overview.cpp

examples/CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.i"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/examples/src/Overview.cpp > CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.i

examples/CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.s"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/examples/src/Overview.cpp -o CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.s

examples/CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/flags.make
examples/CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/includes_CXX.rsp
examples/CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.o: ../examples/src/labels/Labels.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.o"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.o -c /src/examples/src/labels/Labels.cpp

examples/CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.i"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/examples/src/labels/Labels.cpp > CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.i

examples/CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.s"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/examples/src/labels/Labels.cpp -o CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.s

examples/CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/flags.make
examples/CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/includes_CXX.rsp
examples/CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.o: ../examples/src/materialdesign/MaterialDesign.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object examples/CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.o"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.o -c /src/examples/src/materialdesign/MaterialDesign.cpp

examples/CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.i"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/examples/src/materialdesign/MaterialDesign.cpp > CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.i

examples/CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.s"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/examples/src/materialdesign/MaterialDesign.cpp -o CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.s

examples/CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/flags.make
examples/CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/includes_CXX.rsp
examples/CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.o: ../examples/src/multiwindow/MultiWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object examples/CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.o"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.o -c /src/examples/src/multiwindow/MultiWindow.cpp

examples/CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.i"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/examples/src/multiwindow/MultiWindow.cpp > CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.i

examples/CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.s"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/examples/src/multiwindow/MultiWindow.cpp -o CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.s

examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/flags.make
examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/includes_CXX.rsp
examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.o: ../examples/src/primitives2d/Primitives2d.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.o"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.o -c /src/examples/src/primitives2d/Primitives2d.cpp

examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.i"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/examples/src/primitives2d/Primitives2d.cpp > CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.i

examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.s"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/examples/src/primitives2d/Primitives2d.cpp -o CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.s

examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/flags.make
examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/includes_CXX.rsp
examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.o: ../examples/src/primitives3d/Primitives3d.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.o"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.o -c /src/examples/src/primitives3d/Primitives3d.cpp

examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.i"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/examples/src/primitives3d/Primitives3d.cpp > CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.i

examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.s"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/examples/src/primitives3d/Primitives3d.cpp -o CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.s

examples/CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/flags.make
examples/CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/includes_CXX.rsp
examples/CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.o: ../examples/src/rendertexture/Rendertexture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object examples/CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.o"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.o -c /src/examples/src/rendertexture/Rendertexture.cpp

examples/CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.i"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/examples/src/rendertexture/Rendertexture.cpp > CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.i

examples/CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.s"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/examples/src/rendertexture/Rendertexture.cpp -o CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.s

examples/CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/flags.make
examples/CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.o: examples/CMakeFiles/AnanasGfxExamples.dir/includes_CXX.rsp
examples/CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.o: ../examples/src/uiviews/UIViews.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object examples/CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.o"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.o -c /src/examples/src/uiviews/UIViews.cpp

examples/CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.i"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /src/examples/src/uiviews/UIViews.cpp > CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.i

examples/CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.s"
	cd /src/cmake-build-emscripten/examples && /emsdk_portable/sdk/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /src/examples/src/uiviews/UIViews.cpp -o CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.s

# Object files for target AnanasGfxExamples
AnanasGfxExamples_OBJECTS = \
"CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.o" \
"CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.o" \
"CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.o" \
"CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.o" \
"CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.o" \
"CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.o" \
"CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.o" \
"CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.o"

# External object files for target AnanasGfxExamples
AnanasGfxExamples_EXTERNAL_OBJECTS =

examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/src/Overview.cpp.o
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/src/labels/Labels.cpp.o
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/src/materialdesign/MaterialDesign.cpp.o
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/src/multiwindow/MultiWindow.cpp.o
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives2d/Primitives2d.cpp.o
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/src/primitives3d/Primitives3d.cpp.o
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/src/rendertexture/Rendertexture.cpp.o
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/src/uiviews/UIViews.cpp.o
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/build.make
examples/AnanasGfxExamples.html: dependencies/easy-exception/libEasyException.a
examples/AnanasGfxExamples.html: libAnanasGfx.a
examples/AnanasGfxExamples.html: dependencies/easy-exception/libEasyException.a
examples/AnanasGfxExamples.html: dependencies/freetype2/libfreetype.a
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/linklibs.rsp
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/objects1.rsp
examples/AnanasGfxExamples.html: examples/CMakeFiles/AnanasGfxExamples.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/src/cmake-build-emscripten/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable AnanasGfxExamples.html"
	cd /src/cmake-build-emscripten/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AnanasGfxExamples.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/AnanasGfxExamples.dir/build: examples/AnanasGfxExamples.html

.PHONY : examples/CMakeFiles/AnanasGfxExamples.dir/build

examples/CMakeFiles/AnanasGfxExamples.dir/clean:
	cd /src/cmake-build-emscripten/examples && $(CMAKE_COMMAND) -P CMakeFiles/AnanasGfxExamples.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/AnanasGfxExamples.dir/clean

examples/CMakeFiles/AnanasGfxExamples.dir/depend:
	cd /src/cmake-build-emscripten && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /src /src/examples /src/cmake-build-emscripten /src/cmake-build-emscripten/examples /src/cmake-build-emscripten/examples/CMakeFiles/AnanasGfxExamples.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/AnanasGfxExamples.dir/depend

