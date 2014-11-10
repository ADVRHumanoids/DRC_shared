cmake_minimum_required(VERSION 2.8.12)
include(ExternalProject)
project(drc_shared)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

FIND_PACKAGE(YARP REQUIRED)
FIND_PACKAGE(rosconsole REQUIRED)
FIND_PACKAGE(roscpp REQUIRED)
find_package(PCL 1.7 REQUIRED COMPONENTS common)

set(VARS_PREFIX "DRC_SHARED")
                            
find_package(YCM REQUIRED)
include(YCMDefaultDirs)
ycm_default_dirs(${VARS_PREFIX})

include_directories(include ${PCL_INCLUDE_DIRS})

# for every file in drc_INCLUDES CMake already sets the property HEADER_FILE_ONLY
file(GLOB_RECURSE drc_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include" *.h)

# find YARP
find_package(YARP 2.3.60)
include_directories(${YARP_INCLUDE_DIRS})

add_subdirectory(src/MotorControlHelpers)

## Declare drc_shared library
add_library(drc_shared SHARED   src/OccupancyGrid.cpp
                                src/utils/module_state_streamer.cpp
                                src/planner_msgs/flat_walk_cmd.cpp
                                src/planner_msgs/flat_walk_plan.cpp
                                ${drc_INCLUDES})

target_link_libraries(drc_shared   PUBLIC   ${YARP_LIBRARIES}
                                   PRIVATE  ${PCL_LIBRARIES})

# examples
add_executable(grabber_example src/examples/grabber_example.cpp)
add_executable(module_state_streamer_example src/examples/module_state_streamer_example.cpp)
target_link_libraries(module_state_streamer_example
                      ${YARP_LIBRARIES}
                      drc_shared)
                      
target_link_libraries(grabber_example
		                ${YARP_LIBRARIES})


target_include_directories(drc_shared PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>"
                                               "$<INSTALL_INTERFACE:${${VARS_PREFIX}_INSTALL_INCLUDEDIR}>")
               

install(DIRECTORY include/ 
        DESTINATION "${${VARS_PREFIX}_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h*")

install(TARGETS drc_shared  
        EXPORT drc_shared
        ARCHIVE DESTINATION "${${VARS_PREFIX}_INSTALL_BINDIR}" COMPONENT lib
        RUNTIME DESTINATION "${${VARS_PREFIX}_INSTALL_BINDIR}" COMPONENT bin
        LIBRARY DESTINATION "${${VARS_PREFIX}_INSTALL_LIBDIR}" COMPONENT shlib
        PUBLIC_HEADER DESTINATION "${${VARS_PREFIX}_INSTALL_INCLUDEDIR}/drc_shared" COMPONENT dev)

        
set_property(GLOBAL APPEND PROPERTY ${VARS_PREFIX}_TARGETS drc_shared)


include(InstallBasicPackageFiles)

install_basic_package_files(drc_shared VARS_PREFIX ${VARS_PREFIX}
                                       VERSION "1.0.0"
                                       TARGETS_PROPERTY ${VARS_PREFIX}_TARGETS
                                       COMPATIBILITY SameMajorVersion

)

include(AddUninstallTarget)

#TESTING
add_subdirectory(tests)