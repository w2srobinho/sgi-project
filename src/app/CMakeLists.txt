cmake_minimum_required(VERSION 2.8.11)

project(cg_app)


qt5_add_resources(QRC_FILES images.qrc)

# Source files
file(GLOB SRC_FILES "*.cpp" "*.h")

include_directories(
  ${cg_gui_SOURCE_DIR}
  )

# Executable dependencies
if(SRC_FILES)
  add_executable(cg_app WIN32 ${SRC_FILES} ${QRC_FILES}) 
endif(SRC_FILES)

target_link_libraries(cg_app
  cg_gui
  )
