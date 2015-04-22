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

# third_party
include(qt)
include(gmock)

enable_testing()

# src
add_subdirectory(src/utils)
add_subdirectory(src/geometries)
add_subdirectory(src/domain)
add_subdirectory(src/gui)
add_subdirectory(src/app)

# tests
add_subdirectory(test/domain)

if(MSVC)
  set_property(TARGET utils           PROPERTY FOLDER "src")
  set_property(TARGET cg_geometries   PROPERTY FOLDER "src")
  set_property(TARGET cg_domain       PROPERTY FOLDER "src")
  set_property(TARGET cg_gui          PROPERTY FOLDER "src")
  set_property(TARGET cg_app          PROPERTY FOLDER "src")

  set_property(TARGET cg_domain_tests  PROPERTY FOLDER "test")

  set_property(TARGET gtest_gmock     PROPERTY FOLDER "third_party")
endif()