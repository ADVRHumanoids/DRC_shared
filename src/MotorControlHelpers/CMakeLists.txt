cmake_minimum_required(VERSION 2.8.7)

set(PROJECTNAME ExampleModule)
set(LIB_NAME motorControlHelpers)

project(${PROJECTNAME})

# add local include
include_directories(${CMAKE_CURRENT_SOURCE_DIR} )

add_library(${LIB_NAME} MotorControlHelper.cpp RobotHelper.cpp)
add_executable(${PROJECTNAME}_bin Example/main.cpp Example/ExampleModule.cpp)
TARGET_LINK_LIBRARIES(${PROJECTNAME}_bin ${LIB_NAME} ${YARP_LIBRARIES} ${ACE_LIBRARIES})
