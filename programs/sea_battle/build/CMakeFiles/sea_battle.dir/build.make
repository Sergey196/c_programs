# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /projects/c_programs/sea_battle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /projects/c_programs/sea_battle/build

# Include any dependencies generated for this target.
include CMakeFiles/sea_battle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sea_battle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sea_battle.dir/flags.make

src/include/moc_maingui.cpp: ../src/include/maingui.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating src/include/moc_maingui.cpp"
	cd /projects/c_programs/sea_battle/build/src/include && /usr/lib64/qt5/bin/moc @/projects/c_programs/sea_battle/build/src/include/moc_maingui.cpp_parameters

CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o: CMakeFiles/sea_battle.dir/flags.make
CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o: src/include/moc_maingui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o -c /projects/c_programs/sea_battle/build/src/include/moc_maingui.cpp

CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /projects/c_programs/sea_battle/build/src/include/moc_maingui.cpp > CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.i

CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /projects/c_programs/sea_battle/build/src/include/moc_maingui.cpp -o CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.s

CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o.requires:

.PHONY : CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o.requires

CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o.provides: CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o.requires
	$(MAKE) -f CMakeFiles/sea_battle.dir/build.make CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o.provides.build
.PHONY : CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o.provides

CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o.provides.build: CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o


CMakeFiles/sea_battle.dir/src/src/main.cpp.o: CMakeFiles/sea_battle.dir/flags.make
CMakeFiles/sea_battle.dir/src/src/main.cpp.o: ../src/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sea_battle.dir/src/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sea_battle.dir/src/src/main.cpp.o -c /projects/c_programs/sea_battle/src/src/main.cpp

CMakeFiles/sea_battle.dir/src/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sea_battle.dir/src/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /projects/c_programs/sea_battle/src/src/main.cpp > CMakeFiles/sea_battle.dir/src/src/main.cpp.i

CMakeFiles/sea_battle.dir/src/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sea_battle.dir/src/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /projects/c_programs/sea_battle/src/src/main.cpp -o CMakeFiles/sea_battle.dir/src/src/main.cpp.s

CMakeFiles/sea_battle.dir/src/src/main.cpp.o.requires:

.PHONY : CMakeFiles/sea_battle.dir/src/src/main.cpp.o.requires

CMakeFiles/sea_battle.dir/src/src/main.cpp.o.provides: CMakeFiles/sea_battle.dir/src/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/sea_battle.dir/build.make CMakeFiles/sea_battle.dir/src/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/sea_battle.dir/src/src/main.cpp.o.provides

CMakeFiles/sea_battle.dir/src/src/main.cpp.o.provides.build: CMakeFiles/sea_battle.dir/src/src/main.cpp.o


CMakeFiles/sea_battle.dir/src/src/cell.cpp.o: CMakeFiles/sea_battle.dir/flags.make
CMakeFiles/sea_battle.dir/src/src/cell.cpp.o: ../src/src/cell.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sea_battle.dir/src/src/cell.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sea_battle.dir/src/src/cell.cpp.o -c /projects/c_programs/sea_battle/src/src/cell.cpp

CMakeFiles/sea_battle.dir/src/src/cell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sea_battle.dir/src/src/cell.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /projects/c_programs/sea_battle/src/src/cell.cpp > CMakeFiles/sea_battle.dir/src/src/cell.cpp.i

CMakeFiles/sea_battle.dir/src/src/cell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sea_battle.dir/src/src/cell.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /projects/c_programs/sea_battle/src/src/cell.cpp -o CMakeFiles/sea_battle.dir/src/src/cell.cpp.s

CMakeFiles/sea_battle.dir/src/src/cell.cpp.o.requires:

.PHONY : CMakeFiles/sea_battle.dir/src/src/cell.cpp.o.requires

CMakeFiles/sea_battle.dir/src/src/cell.cpp.o.provides: CMakeFiles/sea_battle.dir/src/src/cell.cpp.o.requires
	$(MAKE) -f CMakeFiles/sea_battle.dir/build.make CMakeFiles/sea_battle.dir/src/src/cell.cpp.o.provides.build
.PHONY : CMakeFiles/sea_battle.dir/src/src/cell.cpp.o.provides

CMakeFiles/sea_battle.dir/src/src/cell.cpp.o.provides.build: CMakeFiles/sea_battle.dir/src/src/cell.cpp.o


CMakeFiles/sea_battle.dir/src/src/controller.cpp.o: CMakeFiles/sea_battle.dir/flags.make
CMakeFiles/sea_battle.dir/src/src/controller.cpp.o: ../src/src/controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sea_battle.dir/src/src/controller.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sea_battle.dir/src/src/controller.cpp.o -c /projects/c_programs/sea_battle/src/src/controller.cpp

CMakeFiles/sea_battle.dir/src/src/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sea_battle.dir/src/src/controller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /projects/c_programs/sea_battle/src/src/controller.cpp > CMakeFiles/sea_battle.dir/src/src/controller.cpp.i

CMakeFiles/sea_battle.dir/src/src/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sea_battle.dir/src/src/controller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /projects/c_programs/sea_battle/src/src/controller.cpp -o CMakeFiles/sea_battle.dir/src/src/controller.cpp.s

CMakeFiles/sea_battle.dir/src/src/controller.cpp.o.requires:

.PHONY : CMakeFiles/sea_battle.dir/src/src/controller.cpp.o.requires

CMakeFiles/sea_battle.dir/src/src/controller.cpp.o.provides: CMakeFiles/sea_battle.dir/src/src/controller.cpp.o.requires
	$(MAKE) -f CMakeFiles/sea_battle.dir/build.make CMakeFiles/sea_battle.dir/src/src/controller.cpp.o.provides.build
.PHONY : CMakeFiles/sea_battle.dir/src/src/controller.cpp.o.provides

CMakeFiles/sea_battle.dir/src/src/controller.cpp.o.provides.build: CMakeFiles/sea_battle.dir/src/src/controller.cpp.o


CMakeFiles/sea_battle.dir/src/src/logic.cpp.o: CMakeFiles/sea_battle.dir/flags.make
CMakeFiles/sea_battle.dir/src/src/logic.cpp.o: ../src/src/logic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/sea_battle.dir/src/src/logic.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sea_battle.dir/src/src/logic.cpp.o -c /projects/c_programs/sea_battle/src/src/logic.cpp

CMakeFiles/sea_battle.dir/src/src/logic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sea_battle.dir/src/src/logic.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /projects/c_programs/sea_battle/src/src/logic.cpp > CMakeFiles/sea_battle.dir/src/src/logic.cpp.i

CMakeFiles/sea_battle.dir/src/src/logic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sea_battle.dir/src/src/logic.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /projects/c_programs/sea_battle/src/src/logic.cpp -o CMakeFiles/sea_battle.dir/src/src/logic.cpp.s

CMakeFiles/sea_battle.dir/src/src/logic.cpp.o.requires:

.PHONY : CMakeFiles/sea_battle.dir/src/src/logic.cpp.o.requires

CMakeFiles/sea_battle.dir/src/src/logic.cpp.o.provides: CMakeFiles/sea_battle.dir/src/src/logic.cpp.o.requires
	$(MAKE) -f CMakeFiles/sea_battle.dir/build.make CMakeFiles/sea_battle.dir/src/src/logic.cpp.o.provides.build
.PHONY : CMakeFiles/sea_battle.dir/src/src/logic.cpp.o.provides

CMakeFiles/sea_battle.dir/src/src/logic.cpp.o.provides.build: CMakeFiles/sea_battle.dir/src/src/logic.cpp.o


CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o: CMakeFiles/sea_battle.dir/flags.make
CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o: ../src/src/maingui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o -c /projects/c_programs/sea_battle/src/src/maingui.cpp

CMakeFiles/sea_battle.dir/src/src/maingui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sea_battle.dir/src/src/maingui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /projects/c_programs/sea_battle/src/src/maingui.cpp > CMakeFiles/sea_battle.dir/src/src/maingui.cpp.i

CMakeFiles/sea_battle.dir/src/src/maingui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sea_battle.dir/src/src/maingui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /projects/c_programs/sea_battle/src/src/maingui.cpp -o CMakeFiles/sea_battle.dir/src/src/maingui.cpp.s

CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o.requires:

.PHONY : CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o.requires

CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o.provides: CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o.requires
	$(MAKE) -f CMakeFiles/sea_battle.dir/build.make CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o.provides.build
.PHONY : CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o.provides

CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o.provides.build: CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o


CMakeFiles/sea_battle.dir/src/src/ship.cpp.o: CMakeFiles/sea_battle.dir/flags.make
CMakeFiles/sea_battle.dir/src/src/ship.cpp.o: ../src/src/ship.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/sea_battle.dir/src/src/ship.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sea_battle.dir/src/src/ship.cpp.o -c /projects/c_programs/sea_battle/src/src/ship.cpp

CMakeFiles/sea_battle.dir/src/src/ship.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sea_battle.dir/src/src/ship.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /projects/c_programs/sea_battle/src/src/ship.cpp > CMakeFiles/sea_battle.dir/src/src/ship.cpp.i

CMakeFiles/sea_battle.dir/src/src/ship.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sea_battle.dir/src/src/ship.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /projects/c_programs/sea_battle/src/src/ship.cpp -o CMakeFiles/sea_battle.dir/src/src/ship.cpp.s

CMakeFiles/sea_battle.dir/src/src/ship.cpp.o.requires:

.PHONY : CMakeFiles/sea_battle.dir/src/src/ship.cpp.o.requires

CMakeFiles/sea_battle.dir/src/src/ship.cpp.o.provides: CMakeFiles/sea_battle.dir/src/src/ship.cpp.o.requires
	$(MAKE) -f CMakeFiles/sea_battle.dir/build.make CMakeFiles/sea_battle.dir/src/src/ship.cpp.o.provides.build
.PHONY : CMakeFiles/sea_battle.dir/src/src/ship.cpp.o.provides

CMakeFiles/sea_battle.dir/src/src/ship.cpp.o.provides.build: CMakeFiles/sea_battle.dir/src/src/ship.cpp.o


CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o: CMakeFiles/sea_battle.dir/flags.make
CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o: ../src/src/pipconnectplayers.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o -c /projects/c_programs/sea_battle/src/src/pipconnectplayers.cpp

CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /projects/c_programs/sea_battle/src/src/pipconnectplayers.cpp > CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.i

CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /projects/c_programs/sea_battle/src/src/pipconnectplayers.cpp -o CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.s

CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o.requires:

.PHONY : CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o.requires

CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o.provides: CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o.requires
	$(MAKE) -f CMakeFiles/sea_battle.dir/build.make CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o.provides.build
.PHONY : CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o.provides

CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o.provides.build: CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o


# Object files for target sea_battle
sea_battle_OBJECTS = \
"CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o" \
"CMakeFiles/sea_battle.dir/src/src/main.cpp.o" \
"CMakeFiles/sea_battle.dir/src/src/cell.cpp.o" \
"CMakeFiles/sea_battle.dir/src/src/controller.cpp.o" \
"CMakeFiles/sea_battle.dir/src/src/logic.cpp.o" \
"CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o" \
"CMakeFiles/sea_battle.dir/src/src/ship.cpp.o" \
"CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o"

# External object files for target sea_battle
sea_battle_EXTERNAL_OBJECTS =

../bin/sea_battle: CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o
../bin/sea_battle: CMakeFiles/sea_battle.dir/src/src/main.cpp.o
../bin/sea_battle: CMakeFiles/sea_battle.dir/src/src/cell.cpp.o
../bin/sea_battle: CMakeFiles/sea_battle.dir/src/src/controller.cpp.o
../bin/sea_battle: CMakeFiles/sea_battle.dir/src/src/logic.cpp.o
../bin/sea_battle: CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o
../bin/sea_battle: CMakeFiles/sea_battle.dir/src/src/ship.cpp.o
../bin/sea_battle: CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o
../bin/sea_battle: CMakeFiles/sea_battle.dir/build.make
../bin/sea_battle: /usr/lib64/libQt5Widgets.so.5.9.4
../bin/sea_battle: /usr/lib64/libQt5Gui.so.5.9.4
../bin/sea_battle: /usr/lib64/libQt5Core.so.5.9.4
../bin/sea_battle: CMakeFiles/sea_battle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/projects/c_programs/sea_battle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ../bin/sea_battle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sea_battle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sea_battle.dir/build: ../bin/sea_battle

.PHONY : CMakeFiles/sea_battle.dir/build

CMakeFiles/sea_battle.dir/requires: CMakeFiles/sea_battle.dir/src/include/moc_maingui.cpp.o.requires
CMakeFiles/sea_battle.dir/requires: CMakeFiles/sea_battle.dir/src/src/main.cpp.o.requires
CMakeFiles/sea_battle.dir/requires: CMakeFiles/sea_battle.dir/src/src/cell.cpp.o.requires
CMakeFiles/sea_battle.dir/requires: CMakeFiles/sea_battle.dir/src/src/controller.cpp.o.requires
CMakeFiles/sea_battle.dir/requires: CMakeFiles/sea_battle.dir/src/src/logic.cpp.o.requires
CMakeFiles/sea_battle.dir/requires: CMakeFiles/sea_battle.dir/src/src/maingui.cpp.o.requires
CMakeFiles/sea_battle.dir/requires: CMakeFiles/sea_battle.dir/src/src/ship.cpp.o.requires
CMakeFiles/sea_battle.dir/requires: CMakeFiles/sea_battle.dir/src/src/pipconnectplayers.cpp.o.requires

.PHONY : CMakeFiles/sea_battle.dir/requires

CMakeFiles/sea_battle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sea_battle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sea_battle.dir/clean

CMakeFiles/sea_battle.dir/depend: src/include/moc_maingui.cpp
	cd /projects/c_programs/sea_battle/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /projects/c_programs/sea_battle /projects/c_programs/sea_battle /projects/c_programs/sea_battle/build /projects/c_programs/sea_battle/build /projects/c_programs/sea_battle/build/CMakeFiles/sea_battle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sea_battle.dir/depend

