# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/apachetest/Documents/mtrain/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/apachetest/Documents/mtrain/tests/build-dir

# Utility rule file for test-adc-prog.

# Include the progress variables for this target.
include CMakeFiles/test-adc-prog.dir/progress.make

CMakeFiles/test-adc-prog:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/apachetest/Documents/mtrain/tests/build-dir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Copying binary to MCU"
	./adc.bin

test-adc-prog: CMakeFiles/test-adc-prog
test-adc-prog: CMakeFiles/test-adc-prog.dir/build.make

.PHONY : test-adc-prog

# Rule to build all files generated by this target.
CMakeFiles/test-adc-prog.dir/build: test-adc-prog

.PHONY : CMakeFiles/test-adc-prog.dir/build

CMakeFiles/test-adc-prog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test-adc-prog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test-adc-prog.dir/clean

CMakeFiles/test-adc-prog.dir/depend:
	cd /home/apachetest/Documents/mtrain/tests/build-dir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/apachetest/Documents/mtrain/tests /home/apachetest/Documents/mtrain/tests /home/apachetest/Documents/mtrain/tests/build-dir /home/apachetest/Documents/mtrain/tests/build-dir /home/apachetest/Documents/mtrain/tests/build-dir/CMakeFiles/test-adc-prog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test-adc-prog.dir/depend
