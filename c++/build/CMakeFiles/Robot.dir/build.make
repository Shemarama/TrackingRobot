# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/barbie/Documents/python/opencv/robot/c++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/barbie/Documents/python/opencv/robot/c++/build

# Include any dependencies generated for this target.
include CMakeFiles/Robot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Robot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Robot.dir/flags.make

CMakeFiles/Robot.dir/main.cpp.o: CMakeFiles/Robot.dir/flags.make
CMakeFiles/Robot.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/barbie/Documents/python/opencv/robot/c++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Robot.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Robot.dir/main.cpp.o -c /home/barbie/Documents/python/opencv/robot/c++/main.cpp

CMakeFiles/Robot.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Robot.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/barbie/Documents/python/opencv/robot/c++/main.cpp > CMakeFiles/Robot.dir/main.cpp.i

CMakeFiles/Robot.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Robot.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/barbie/Documents/python/opencv/robot/c++/main.cpp -o CMakeFiles/Robot.dir/main.cpp.s

CMakeFiles/Robot.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Robot.dir/main.cpp.o.requires

CMakeFiles/Robot.dir/main.cpp.o.provides: CMakeFiles/Robot.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Robot.dir/build.make CMakeFiles/Robot.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Robot.dir/main.cpp.o.provides

CMakeFiles/Robot.dir/main.cpp.o.provides.build: CMakeFiles/Robot.dir/main.cpp.o


# Object files for target Robot
Robot_OBJECTS = \
"CMakeFiles/Robot.dir/main.cpp.o"

# External object files for target Robot
Robot_EXTERNAL_OBJECTS =

Robot: CMakeFiles/Robot.dir/main.cpp.o
Robot: CMakeFiles/Robot.dir/build.make
Robot: libserial.a
Robot: /usr/lib/libopencv_stitching.so.3.2.0
Robot: /usr/lib/libopencv_superres.so.3.2.0
Robot: /usr/lib/libopencv_videostab.so.3.2.0
Robot: /usr/lib/libopencv_aruco.so.3.2.0
Robot: /usr/lib/libopencv_bgsegm.so.3.2.0
Robot: /usr/lib/libopencv_bioinspired.so.3.2.0
Robot: /usr/lib/libopencv_ccalib.so.3.2.0
Robot: /usr/lib/libopencv_dpm.so.3.2.0
Robot: /usr/lib/libopencv_freetype.so.3.2.0
Robot: /usr/lib/libopencv_fuzzy.so.3.2.0
Robot: /usr/lib/libopencv_hdf.so.3.2.0
Robot: /usr/lib/libopencv_line_descriptor.so.3.2.0
Robot: /usr/lib/libopencv_optflow.so.3.2.0
Robot: /usr/lib/libopencv_reg.so.3.2.0
Robot: /usr/lib/libopencv_saliency.so.3.2.0
Robot: /usr/lib/libopencv_stereo.so.3.2.0
Robot: /usr/lib/libopencv_structured_light.so.3.2.0
Robot: /usr/lib/libopencv_surface_matching.so.3.2.0
Robot: /usr/lib/libopencv_tracking.so.3.2.0
Robot: /usr/lib/libopencv_xfeatures2d.so.3.2.0
Robot: /usr/lib/libopencv_ximgproc.so.3.2.0
Robot: /usr/lib/libopencv_xobjdetect.so.3.2.0
Robot: /usr/lib/libopencv_xphoto.so.3.2.0
Robot: /usr/lib/libopencv_shape.so.3.2.0
Robot: /usr/lib/libopencv_phase_unwrapping.so.3.2.0
Robot: /usr/lib/libopencv_rgbd.so.3.2.0
Robot: /usr/lib/libopencv_calib3d.so.3.2.0
Robot: /usr/lib/libopencv_video.so.3.2.0
Robot: /usr/lib/libopencv_datasets.so.3.2.0
Robot: /usr/lib/libopencv_dnn.so.3.2.0
Robot: /usr/lib/libopencv_face.so.3.2.0
Robot: /usr/lib/libopencv_plot.so.3.2.0
Robot: /usr/lib/libopencv_text.so.3.2.0
Robot: /usr/lib/libopencv_features2d.so.3.2.0
Robot: /usr/lib/libopencv_flann.so.3.2.0
Robot: /usr/lib/libopencv_objdetect.so.3.2.0
Robot: /usr/lib/libopencv_ml.so.3.2.0
Robot: /usr/lib/libopencv_highgui.so.3.2.0
Robot: /usr/lib/libopencv_photo.so.3.2.0
Robot: /usr/lib/libopencv_videoio.so.3.2.0
Robot: /usr/lib/libopencv_imgcodecs.so.3.2.0
Robot: /usr/lib/libopencv_imgproc.so.3.2.0
Robot: /usr/lib/libopencv_core.so.3.2.0
Robot: CMakeFiles/Robot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/barbie/Documents/python/opencv/robot/c++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Robot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Robot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Robot.dir/build: Robot

.PHONY : CMakeFiles/Robot.dir/build

CMakeFiles/Robot.dir/requires: CMakeFiles/Robot.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Robot.dir/requires

CMakeFiles/Robot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Robot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Robot.dir/clean

CMakeFiles/Robot.dir/depend:
	cd /home/barbie/Documents/python/opencv/robot/c++/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/barbie/Documents/python/opencv/robot/c++ /home/barbie/Documents/python/opencv/robot/c++ /home/barbie/Documents/python/opencv/robot/c++/build /home/barbie/Documents/python/opencv/robot/c++/build /home/barbie/Documents/python/opencv/robot/c++/build/CMakeFiles/Robot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Robot.dir/depend

