if(__GMOCK_INCLUDED)
  return()
endif()
set(__GMOCK_INCLUDED TRUE)

include(init)

add_definitions(-DGMOCK_USE_OVERRIDENESS)

include(ExternalProject)

set(gmock_BINARY_DIR "${CMAKE_BINARY_DIR}/gmock")

if(MSVC11)
  add_definitions(-D_VARIADIC_MAX=10) # gtest uses size 10 tuples, and fails with VS2012 faux variadics default size.
endif()

# Define Google Mock & Test Directories
###############################################################################
cmake_minimum_required(VERSION 2.8.11)
if(BUILD_SHARED_LIBS)
#  ExternalProject_Add(gtest_gmock
#    SOURCE_DIR ${THIRD_PARTY_DIR}/gmock-1.7.0
#    BINARY_DIR ${gmock_BINARY_DIR}
#    CMAKE_ARGS -Dgtest_force_shared_crt=ON
#    INSTALL_COMMAND ""
#    )
#
#  add_custom_command(
#    TARGET gtest_gmock POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${gmock_BINARY_DIR}/$<CONFIGURATION>/gmock.lib" "${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>/gmock.lib"
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${gmock_BINARY_DIR}/$<CONFIGURATION>/gmock.dll" "${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>/gmock.dll"
#    )
#
#  add_library(gmock SHARED IMPORTED GLOBAL)
#  add_library(gtest SHARED IMPORTED GLOBAL)
#
#  foreach(configuration ${CMAKE_CONFIGURATION_TYPES})
#    string(TOUPPER ${configuration} config)
#    set_target_properties(gtest PROPERTIES IMPORTED_IMPLIB_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.lib" )
#    set_target_properties(gmock PROPERTIES IMPORTED_IMPLIB_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.lib" )
#    set_target_properties(gtest PROPERTIES IMPORTED_LOCATION_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.dll" )
#    set_target_properties(gmock PROPERTIES IMPORTED_LOCATION_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.dll" )
#  endforeach()

else()
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
    set_target_properties(gtest PROPERTIES IMPORTED_LOCATION_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.lib" )
    set_target_properties(gmock PROPERTIES IMPORTED_LOCATION_${config} "${gmock_BINARY_DIR}/${configuration}/gmock.lib" )
  endforeach()
endif()

ExternalProject_Get_Property(gtest_gmock source_dir)

set(GMOCK_INCLUDE_DIR  "${source_dir}/include"       CACHE PATH "Gmock include directories")
set(GTEST_INCLUDE_DIR  "${source_dir}/gtest/include" CACHE INTERNAL "Gtest include directories")

if(BUILD_SHARED_LIBS)
  add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)
endif()

add_dependencies(gmock gtest_gmock)
add_dependencies(gtest gtest_gmock)