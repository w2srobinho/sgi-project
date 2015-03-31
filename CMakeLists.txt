if(MSVC14)
  cmake_minimum_required(VERSION 3.1)
elseif()
  cmake_minimum_required(VERSION 2.8.11)
endif()

set(CMAKE_MODULE_PATH
  "${CMAKE_MODULE_PATH}"
  "${CMAKE_SOURCE_DIR}/cmake"
)

include(init)

project(cg_project)

CMAKE_POLICY(SET CMP0020 NEW)
include(build)
# Third_party
# include(gmock)
include(qt)

# src
add_subdirectory(src/geometries)
add_subdirectory(src/domain)
add_subdirectory(src/gui)
add_subdirectory(src/app)

set_property(TARGET cg_app      PROPERTY FOLDER "src/app")
set_property(TARGET cg_gui      PROPERTY FOLDER "src/gui")
# tests


### Main program executable
#################################################################################
##set(EXECUTABLE_NAME "program")
##
### Set link libraries
### target_link_libraries($EXECUTABLE_NAME ...)
##
### Tests executable
#################################################################################
##set(TEST_EXECUTABLE_NAME "tests")
##
### Test files
##file(GLOB TEST_FILES "test/*.cpp")
##
### Don't include Main.cpp from src
##file(GLOB MAIN_SRC "src/Main.cpp")
##list(REMOVE_ITEM SRC_FILES ${MAIN_SRC})
##
##add_executable("${TEST_EXECUTABLE_NAME}" ${TEST_FILES} ${SRC_FILES})
##
### Set link libraries (order matters)
##target_link_libraries("${TEST_EXECUTABLE_NAME}" gmock gtest pthread)
##
### Include root directory
##include_directories(BEFORE ".")
##include_directories(BEFORE "src/")

