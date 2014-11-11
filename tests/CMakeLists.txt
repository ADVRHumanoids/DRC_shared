cmake_minimum_required(VERSION 2.8.7)
include(ExternalProject)

set(PROJECTNAME tests)
project(${PROJECTNAME})

# compite GTest
set(gTestSource "/usr/src/gtest")
ExternalProject_Add(GTest-ext SOURCE_DIR ${gTestSource}
                              PREFIX "${CMAKE_CURRENT_BINARY_DIR}/external"
                              INSTALL_COMMAND "")
set(GTEST_LIB_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/src/GTest-ext-build/")
set(GTEST_INCLUDE_DIRS ${gTestSource})
set(GTEST_BOTH_LIBRARIES gtest gtest_main)
include_directories(${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_LIB_DIRS})

# add local include
include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
enable_testing()

if( YCM_EP_DEVEL_MODE_drc_shared)
    add_custom_target(  drc_shared_test ALL
                        COMMAND ${CMAKE_CTEST_COMMAND}
                        DEPENDS drc_utils
                                interfacesTest )
endif()
