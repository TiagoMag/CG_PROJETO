# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/build

# Include any dependencies generated for this target.
include CMakeFiles/generator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/generator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/generator.dir/flags.make

CMakeFiles/generator.dir/src/Generator/generator.cpp.o: CMakeFiles/generator.dir/flags.make
CMakeFiles/generator.dir/src/Generator/generator.cpp.o: ../src/Generator/generator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/generator.dir/src/Generator/generator.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/generator.dir/src/Generator/generator.cpp.o -c /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/src/Generator/generator.cpp

CMakeFiles/generator.dir/src/Generator/generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/generator.dir/src/Generator/generator.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/src/Generator/generator.cpp > CMakeFiles/generator.dir/src/Generator/generator.cpp.i

CMakeFiles/generator.dir/src/Generator/generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/generator.dir/src/Generator/generator.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/src/Generator/generator.cpp -o CMakeFiles/generator.dir/src/Generator/generator.cpp.s

CMakeFiles/generator.dir/src/Generator/generator.cpp.o.requires:

.PHONY : CMakeFiles/generator.dir/src/Generator/generator.cpp.o.requires

CMakeFiles/generator.dir/src/Generator/generator.cpp.o.provides: CMakeFiles/generator.dir/src/Generator/generator.cpp.o.requires
	$(MAKE) -f CMakeFiles/generator.dir/build.make CMakeFiles/generator.dir/src/Generator/generator.cpp.o.provides.build
.PHONY : CMakeFiles/generator.dir/src/Generator/generator.cpp.o.provides

CMakeFiles/generator.dir/src/Generator/generator.cpp.o.provides.build: CMakeFiles/generator.dir/src/Generator/generator.cpp.o


# Object files for target generator
generator_OBJECTS = \
"CMakeFiles/generator.dir/src/Generator/generator.cpp.o"

# External object files for target generator
generator_EXTERNAL_OBJECTS =

generator: CMakeFiles/generator.dir/src/Generator/generator.cpp.o
generator: CMakeFiles/generator.dir/build.make
generator: CMakeFiles/generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable generator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/generator.dir/build: generator

.PHONY : CMakeFiles/generator.dir/build

CMakeFiles/generator.dir/requires: CMakeFiles/generator.dir/src/Generator/generator.cpp.o.requires

.PHONY : CMakeFiles/generator.dir/requires

CMakeFiles/generator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/generator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/generator.dir/clean

CMakeFiles/generator.dir/depend:
	cd /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3 /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3 /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/build /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/build /Users/joaonunoabreu/Desktop/2ºSemestre/PROJETOS/CG/Fase3/build/CMakeFiles/generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/generator.dir/depend
