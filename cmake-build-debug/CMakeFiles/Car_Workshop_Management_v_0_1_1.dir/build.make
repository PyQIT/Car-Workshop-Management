# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2018.1.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2018.1.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/flags.make

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/flags.make
CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\main.c.obj   -c C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\main.c

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\main.c > CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\main.c.i

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\main.c -o CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\main.c.s

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj.requires:

.PHONY : CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj.requires

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj.provides: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\build.make CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj.provides

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj.provides.build: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj


CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/flags.make
CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj: ../sqlite3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\sqlite3.c.obj   -c C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\sqlite3.c

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\sqlite3.c > CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\sqlite3.c.i

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\sqlite3.c -o CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\sqlite3.c.s

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj.requires:

.PHONY : CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj.requires

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj.provides: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj.requires
	$(MAKE) -f CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\build.make CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj.provides.build
.PHONY : CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj.provides

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj.provides.build: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj


# Object files for target Car_Workshop_Management_v_0_1_1
Car_Workshop_Management_v_0_1_1_OBJECTS = \
"CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj" \
"CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj"

# External object files for target Car_Workshop_Management_v_0_1_1
Car_Workshop_Management_v_0_1_1_EXTERNAL_OBJECTS =

Car_Workshop_Management_v_0_1_1.exe: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj
Car_Workshop_Management_v_0_1_1.exe: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj
Car_Workshop_Management_v_0_1_1.exe: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/build.make
Car_Workshop_Management_v_0_1_1.exe: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/linklibs.rsp
Car_Workshop_Management_v_0_1_1.exe: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/objects1.rsp
Car_Workshop_Management_v_0_1_1.exe: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Car_Workshop_Management_v_0_1_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/build: Car_Workshop_Management_v_0_1_1.exe

.PHONY : CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/build

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/requires: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/main.c.obj.requires
CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/requires: CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/sqlite3.c.obj.requires

.PHONY : CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/requires

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/clean

CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1 C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1 C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\cmake-build-debug C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\cmake-build-debug C:\Users\MSI\CLionProjects\Car-Workshop-Management-v-0.1.1\cmake-build-debug\CMakeFiles\Car_Workshop_Management_v_0_1_1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Car_Workshop_Management_v_0_1_1.dir/depend
