if(__QT_INCLUDED)
  return()
endif()
set(__QT_INCLUDED TRUE)

if(DEFINED ENV{QT5DIR} AND NOT CMAKE_PREFIX_PATH)
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