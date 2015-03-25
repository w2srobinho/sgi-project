if(__GMOCK_INCLUDED)
  return()
endif()
set(__GMOCK_INCLUDED TRUE)

include(gmock)
# Define Google Mock & Test Directories
###############################################################################
add_subdirectory("${THIRD_PARTY_DIR}/gmock-1.7.0")
set(GMOCK_INCLUDE_DIR "${gmock_SOURCE_DIR}/include" CACHE INTERNAL "Gmock include directory")
set(GTEST_INCLUDE_DIR "${gtest_SOURCE_DIR}/include" CACHE INTERNAL "Gtest include directory")