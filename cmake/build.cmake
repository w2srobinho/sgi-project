if(__BUILD_INCLUDED)
  return()
endif()
set(__BUILD_INCLUDED TRUE)


# global flags
if(CMAKE_COMPILER_IS_GNUCXX)
  # Extra warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wno-write-strings -Wextra")
  if(CMAKE_CXX_FLAGS_DEBUG)
    add_definitions(-D_DEBUG)
  else()
    add_definitions(-DNDEBUG)
  endif()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MACHINE:X64")
endif()