cmake_minimum_required(VERSION 2.8.11)

project(cg_gui)
# main program executable
###############################################################################

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

QT5_WRAP_UI(UI_FILES
    ui_files/mainwindow.ui
)

# Source files
file(GLOB SRC_FILES "*.cpp" "*.h")

include_directories(
  ${cg_geometries_SOURCE_DIR}
  ${cg_domain_SOURCE_DIR}
)

# Executable dependencies
if(SRC_FILES)
  add_library(cg_gui STATIC ${SRC_FILES} ${UI_FILES}) 
endif()

target_link_libraries(cg_gui 
  Qt5::Widgets
  cg_geometries
  cg_domain
)
