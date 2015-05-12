if(__GMOCK_INCLUDED)
  return()
endif()
set(__GMOCK_INCLUDED TRUE)

include(init)

add_definitions(-DGMOCK_USE_OVERRIDENESS)

# Define Google Mock & Test Directories
###############################################################################

if(NOT MSVC)
  cmake_minimum_required(VERSION 2.8.11)

  set(gmock_ROOT_DIR "${THIRD_PARTY_DIR}/gmock-1.7.0")
  set(gmock_SOURCE_DIR "${gmock_ROOT_DIR}/src")
  set(gmock_INCLUDE_DIR  "${gmock_ROOT_DIR}/include" CACHE INTERNAL "Gmock include directories")
  set(gtest_ROOT_DIR "${gmock_ROOT_DIR}/gtest")
  set(gtest_SOURCE_DIR "${gtest_ROOT_DIR}/fused-src/gtest")
  set(gtest_INCLUDE_DIR  "${gtest_ROOT_DIR}/include" CACHE INTERNAL "Gtest include directories")

  set(GMOCK_SOURCE
    ${gmock_SOURCE_DIR}/gmock-all.cc
  )

  set(GTEST_SOURCE
    ${gtest_SOURCE_DIR}/gtest-all.cc
  )

  INCLUDE_DIRECTORIES(
    ${INCLUDE_DIRECTORIES}
    ${gmock_INCLUDE_DIR}
    ${gtest_INCLUDE_DIR}
  )

  add_library(gtest STATIC ${GTEST_SOURCE})
  target_include_directories(gtest PUBLIC ${gtest_INCLUDE_DIRS})

  if (BUILD_SHARED_LIBS)
    target_compile_definitions(gtest PRIVATE GTEST_CREATE_SHARED_LIBRARY=1)
    target_compile_definitions(gtest INTERFACE GTEST_LINKED_AS_SHARED_LIBRARY=1)
  endif()

  add_library(gmock STATIC ${GMOCK_SOURCE})
  target_include_directories(gmock PUBLIC ${gmock_INCLUDE_DIRS} PRIVATE ${gmock_ROOT_DIR})
  target_link_libraries(gmock gtest pthread)

  return()
endif()

include(ExternalProject)

set(gmock_BINARY_DIR "${CMAKE_BINARY_DIR}/gmock")

if(MSVC11)
  add_definitions(-D_VARIADIC_MAX=10) # gtest uses size 10 tuples, and fails with VS2012 faux variadics default size.
endif()
cmake_minimum_required(VERSION 2.8.11)
ExternalProject_Add(gtest_gmock
  SOURCE_DIR ${THIRD_PARTY_DIR}/gmock-1.7.0
  BINARY_DIR ${gmock_BINARY_DIR}
  CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -Dgtest_force_shared_crt=ON
  INSTALL_COMMAND ""
  )

add_library(gmock STATIC IMPORTED GLOBAL)
add_library(gtest STATIC IMPORTED GLOBAL)
foreach(configuration ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${configuration} config)
  if(MSVC)
    set_target_properties(gtest PROPERTIES IMPORTED_LOCATION_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.lib" )
    set_target_properties(gmock PROPERTIES IMPORTED_LOCATION_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.lib" )
  else()
    set_target_properties(gtest PROPERTIES IMPORTED_LOCATION_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.a" )
    set_target_properties(gmock PROPERTIES IMPORTED_LOCATION_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.a" )
  endif()
endforeach()

ExternalProject_Get_Property(gtest_gmock source_dir)

set(GMOCK_INCLUDE_DIR  "${source_dir}/include"       CACHE PATH "Gmock include directories")
set(GTEST_INCLUDE_DIR  "${source_dir}/gtest/include" CACHE INTERNAL "Gtest include directories")

if(BUILD_SHARED_LIBS)
  add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)
endif()

add_dependencies(gmock gtest_gmock)
add_dependencies(gtest gtest_gmock)
