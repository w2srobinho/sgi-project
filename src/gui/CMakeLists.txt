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

qt5_add_resources(QRC_FILES images.qrc)

# Source files
file(GLOB SRC_FILES "*.cpp" "*.h")

# Executable dependencies
if(SRC_FILES)
  add_library(cg_gui STATIC ${SRC_FILES} ${UI_FILES} ${QRC_FILES}) 
endif(SRC_FILES)

target_link_libraries(cg_gui Qt5::Widgets)
