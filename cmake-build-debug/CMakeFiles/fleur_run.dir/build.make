# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Edgar/ClionProjects/Fleur

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Edgar/ClionProjects/Fleur/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/fleur_run.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fleur_run.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fleur_run.dir/flags.make

CMakeFiles/fleur_run.dir/main.cpp.o: CMakeFiles/fleur_run.dir/flags.make
CMakeFiles/fleur_run.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Edgar/ClionProjects/Fleur/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fleur_run.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fleur_run.dir/main.cpp.o -c /Users/Edgar/ClionProjects/Fleur/main.cpp

CMakeFiles/fleur_run.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fleur_run.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Edgar/ClionProjects/Fleur/main.cpp > CMakeFiles/fleur_run.dir/main.cpp.i

CMakeFiles/fleur_run.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fleur_run.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Edgar/ClionProjects/Fleur/main.cpp -o CMakeFiles/fleur_run.dir/main.cpp.s

CMakeFiles/fleur_run.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/fleur_run.dir/main.cpp.o.requires

CMakeFiles/fleur_run.dir/main.cpp.o.provides: CMakeFiles/fleur_run.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/fleur_run.dir/build.make CMakeFiles/fleur_run.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/fleur_run.dir/main.cpp.o.provides

CMakeFiles/fleur_run.dir/main.cpp.o.provides.build: CMakeFiles/fleur_run.dir/main.cpp.o


# Object files for target fleur_run
fleur_run_OBJECTS = \
"CMakeFiles/fleur_run.dir/main.cpp.o"

# External object files for target fleur_run
fleur_run_EXTERNAL_OBJECTS =

fleur_run: CMakeFiles/fleur_run.dir/main.cpp.o
fleur_run: CMakeFiles/fleur_run.dir/build.make
fleur_run: fleur_src/libfleur_src.a
fleur_run: lib/libcpr.a
fleur_run: gumbo-query/src/libgq.dylib
fleur_run: libtwitcurl/liblibtwitcurl.a
fleur_run: /usr/lib/libcurl.dylib
fleur_run: /usr/local/lib/libgumbo.dylib
fleur_run: CMakeFiles/fleur_run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Edgar/ClionProjects/Fleur/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fleur_run"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fleur_run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fleur_run.dir/build: fleur_run

.PHONY : CMakeFiles/fleur_run.dir/build

CMakeFiles/fleur_run.dir/requires: CMakeFiles/fleur_run.dir/main.cpp.o.requires

.PHONY : CMakeFiles/fleur_run.dir/requires

CMakeFiles/fleur_run.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fleur_run.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fleur_run.dir/clean

CMakeFiles/fleur_run.dir/depend:
	cd /Users/Edgar/ClionProjects/Fleur/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Edgar/ClionProjects/Fleur /Users/Edgar/ClionProjects/Fleur /Users/Edgar/ClionProjects/Fleur/cmake-build-debug /Users/Edgar/ClionProjects/Fleur/cmake-build-debug /Users/Edgar/ClionProjects/Fleur/cmake-build-debug/CMakeFiles/fleur_run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fleur_run.dir/depend

