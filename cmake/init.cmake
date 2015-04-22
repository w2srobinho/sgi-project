if(__INIT_INCLUDED)
  return()
endif()
set(__INIT_INCLUDED TRUE)

# define third_party path
set(THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}/third_party")

# define Debug and Release configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug and Release configurations")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build to shared libraries (DLL's)")

set(TARGETS "" CACHE INTERNAL "Internal target list.") # This is CACHE INTERNAL
                                                       # only for its global
                                                       # status, and is always
                                                       # reset.
