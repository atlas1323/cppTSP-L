# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dingo1323/Code/cppTSP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dingo1323/Code/cppTSP/build

# Include any dependencies generated for this target.
include sandbox/CMakeFiles/sandbox-exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include sandbox/CMakeFiles/sandbox-exe.dir/compiler_depend.make

# Include the progress variables for this target.
include sandbox/CMakeFiles/sandbox-exe.dir/progress.make

# Include the compile flags for this target's objects.
include sandbox/CMakeFiles/sandbox-exe.dir/flags.make

sandbox/CMakeFiles/sandbox-exe.dir/sandbox.cpp.o: sandbox/CMakeFiles/sandbox-exe.dir/flags.make
sandbox/CMakeFiles/sandbox-exe.dir/sandbox.cpp.o: ../sandbox/sandbox.cpp
sandbox/CMakeFiles/sandbox-exe.dir/sandbox.cpp.o: sandbox/CMakeFiles/sandbox-exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dingo1323/Code/cppTSP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sandbox/CMakeFiles/sandbox-exe.dir/sandbox.cpp.o"
	cd /home/dingo1323/Code/cppTSP/build/sandbox && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sandbox/CMakeFiles/sandbox-exe.dir/sandbox.cpp.o -MF CMakeFiles/sandbox-exe.dir/sandbox.cpp.o.d -o CMakeFiles/sandbox-exe.dir/sandbox.cpp.o -c /home/dingo1323/Code/cppTSP/sandbox/sandbox.cpp

sandbox/CMakeFiles/sandbox-exe.dir/sandbox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sandbox-exe.dir/sandbox.cpp.i"
	cd /home/dingo1323/Code/cppTSP/build/sandbox && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dingo1323/Code/cppTSP/sandbox/sandbox.cpp > CMakeFiles/sandbox-exe.dir/sandbox.cpp.i

sandbox/CMakeFiles/sandbox-exe.dir/sandbox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sandbox-exe.dir/sandbox.cpp.s"
	cd /home/dingo1323/Code/cppTSP/build/sandbox && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dingo1323/Code/cppTSP/sandbox/sandbox.cpp -o CMakeFiles/sandbox-exe.dir/sandbox.cpp.s

# Object files for target sandbox-exe
sandbox__exe_OBJECTS = \
"CMakeFiles/sandbox-exe.dir/sandbox.cpp.o"

# External object files for target sandbox-exe
sandbox__exe_EXTERNAL_OBJECTS =

sandbox/sandbox-exe: sandbox/CMakeFiles/sandbox-exe.dir/sandbox.cpp.o
sandbox/sandbox-exe: sandbox/CMakeFiles/sandbox-exe.dir/build.make
sandbox/sandbox-exe: src/libassist.a
sandbox/sandbox-exe: src/liboptimizers.a
sandbox/sandbox-exe: sandbox/CMakeFiles/sandbox-exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dingo1323/Code/cppTSP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sandbox-exe"
	cd /home/dingo1323/Code/cppTSP/build/sandbox && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sandbox-exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sandbox/CMakeFiles/sandbox-exe.dir/build: sandbox/sandbox-exe
.PHONY : sandbox/CMakeFiles/sandbox-exe.dir/build

sandbox/CMakeFiles/sandbox-exe.dir/clean:
	cd /home/dingo1323/Code/cppTSP/build/sandbox && $(CMAKE_COMMAND) -P CMakeFiles/sandbox-exe.dir/cmake_clean.cmake
.PHONY : sandbox/CMakeFiles/sandbox-exe.dir/clean

sandbox/CMakeFiles/sandbox-exe.dir/depend:
	cd /home/dingo1323/Code/cppTSP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dingo1323/Code/cppTSP /home/dingo1323/Code/cppTSP/sandbox /home/dingo1323/Code/cppTSP/build /home/dingo1323/Code/cppTSP/build/sandbox /home/dingo1323/Code/cppTSP/build/sandbox/CMakeFiles/sandbox-exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sandbox/CMakeFiles/sandbox-exe.dir/depend

