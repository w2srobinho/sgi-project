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

#includes 
CMAKE_POLICY(SET CMP0020 NEW)
include(build)
# Third_party
# include(gmock)
include(qt)

# src
add_subdirectory(src/utils)
add_subdirectory(src/geometries)
add_subdirectory(src/domain)
add_subdirectory(src/gui)
add_subdirectory(src/app)

# tests

