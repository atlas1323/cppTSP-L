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
include app/CMakeFiles/TSP-exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include app/CMakeFiles/TSP-exe.dir/compiler_depend.make

# Include the progress variables for this target.
include app/CMakeFiles/TSP-exe.dir/progress.make

# Include the compile flags for this target's objects.
include app/CMakeFiles/TSP-exe.dir/flags.make

app/CMakeFiles/TSP-exe.dir/main.cpp.o: app/CMakeFiles/TSP-exe.dir/flags.make
app/CMakeFiles/TSP-exe.dir/main.cpp.o: ../app/main.cpp
app/CMakeFiles/TSP-exe.dir/main.cpp.o: app/CMakeFiles/TSP-exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dingo1323/Code/cppTSP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object app/CMakeFiles/TSP-exe.dir/main.cpp.o"
	cd /home/dingo1323/Code/cppTSP/build/app && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT app/CMakeFiles/TSP-exe.dir/main.cpp.o -MF CMakeFiles/TSP-exe.dir/main.cpp.o.d -o CMakeFiles/TSP-exe.dir/main.cpp.o -c /home/dingo1323/Code/cppTSP/app/main.cpp

app/CMakeFiles/TSP-exe.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TSP-exe.dir/main.cpp.i"
	cd /home/dingo1323/Code/cppTSP/build/app && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dingo1323/Code/cppTSP/app/main.cpp > CMakeFiles/TSP-exe.dir/main.cpp.i

app/CMakeFiles/TSP-exe.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TSP-exe.dir/main.cpp.s"
	cd /home/dingo1323/Code/cppTSP/build/app && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dingo1323/Code/cppTSP/app/main.cpp -o CMakeFiles/TSP-exe.dir/main.cpp.s

# Object files for target TSP-exe
TSP__exe_OBJECTS = \
"CMakeFiles/TSP-exe.dir/main.cpp.o"

# External object files for target TSP-exe
TSP__exe_EXTERNAL_OBJECTS =

app/TSP-exe: app/CMakeFiles/TSP-exe.dir/main.cpp.o
app/TSP-exe: app/CMakeFiles/TSP-exe.dir/build.make
app/TSP-exe: src/libassist.a
app/TSP-exe: src/liboptimizers.a
app/TSP-exe: app/CMakeFiles/TSP-exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dingo1323/Code/cppTSP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TSP-exe"
	cd /home/dingo1323/Code/cppTSP/build/app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TSP-exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app/CMakeFiles/TSP-exe.dir/build: app/TSP-exe
.PHONY : app/CMakeFiles/TSP-exe.dir/build

app/CMakeFiles/TSP-exe.dir/clean:
	cd /home/dingo1323/Code/cppTSP/build/app && $(CMAKE_COMMAND) -P CMakeFiles/TSP-exe.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/TSP-exe.dir/clean

app/CMakeFiles/TSP-exe.dir/depend:
	cd /home/dingo1323/Code/cppTSP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dingo1323/Code/cppTSP /home/dingo1323/Code/cppTSP/app /home/dingo1323/Code/cppTSP/build /home/dingo1323/Code/cppTSP/build/app /home/dingo1323/Code/cppTSP/build/app/CMakeFiles/TSP-exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app/CMakeFiles/TSP-exe.dir/depend
