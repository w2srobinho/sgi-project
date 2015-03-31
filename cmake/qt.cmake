if(__QT_INCLUDED)
  return()
endif()
set(__QT_INCLUDED TRUE)

message("${CMAKE_PREFIX_PATH}")
if(DEFINED ENV{QT5DIR})
  message("nao tem prefix definido")
  set(CMAKE_PREFIX_PATH
    "${CMAKE_PREFIX_PATH}"
    "$ENV{QT5DIR}")
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)