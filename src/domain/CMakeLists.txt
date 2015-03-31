cmake_minimum_required(VERSION 2.8.11)

project(cg_domain)

# Source files
file(GLOB SRC_FILES "*.cpp" "*.h")

include_directories(
  ${cg_geometries_SOURCE_DIR}
)

# Executable dependencies
if(SRC_FILES)
  add_library(cg_domain STATIC ${SRC_FILES}) 
endif(SRC_FILES)
