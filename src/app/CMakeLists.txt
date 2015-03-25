cmake_minimum_required(VERSION 2.8.11)

project(cg_app)


# Source files
file(GLOB SRC_FILES "*.cpp" "*.h")

include_directories(
  ${cg_gui_SOURCE_DIR}
  )

# Executable dependencies
if(SRC_FILES)
  add_executable(cg_app ${SRC_FILES} ${UI_FILES}) 
endif(SRC_FILES)

target_link_libraries(cg_app 
  cg_gui
  )
