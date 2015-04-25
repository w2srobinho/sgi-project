cmake_minimum_required(VERSION 2.8.11)

project(cg_geometries_tests)

# Source files
file(GLOB SRC_FILES "*.cpp" "*.h")

include_directories(
  ${cg_geometries_SOURCE_DIR}
  ${GTEST_INCLUDE_DIR}
  ${GMOCK_INCLUDE_DIR}
)

if(MSVC)  
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

# Executable dependencies
if(SRC_FILES)
  add_executable(cg_geometries_tests ${SRC_FILES}) 
endif(SRC_FILES)

target_link_libraries(cg_geometries_tests 
	gmock
	cg_geometries
)
