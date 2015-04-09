cmake_minimum_required(VERSION 2.8.11)

project(utils)

# Source files
file(GLOB SRC_FILES "*.cpp" "*.h")

# Executable dependencies
if(SRC_FILES)
  add_library(utils STATIC ${SRC_FILES}) 
endif(SRC_FILES)
