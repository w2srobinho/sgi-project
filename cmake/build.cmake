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
endif()

# enable file folders on generated visual studio projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

function(use_qt5_module _target) 
  foreach(plugin ${ARGN})
    foreach(configuration ${CMAKE_CONFIGURATION_TYPES})

      if(NOT TARGET ${plugin})
        break()
      endif()

      if(${configuration} MATCHES "Debug")
        get_target_property(module_location ${plugin} LOCATION_DEBUG)
        get_target_property(module_dependencies ${plugin} IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG)
      else()
        get_target_property(module_location ${plugin} LOCATION_RELEASE)
        get_target_property(module_dependencies ${plugin} IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE)
      endif()

      set(plugin_type "")
      get_filename_component(module_folder ${module_location} PATH)
      if(${module_folder} MATCHES "plugin")
        get_filename_component(plugin_type ${module_folder} NAME)
      endif()
      
      #if(ALL_DYN_LINK)
      #  file(COPY ${module_location} DESTINATION "${CMAKE_BINARY_DIR}/bin/${configuration}/${plugin_type}")
      #else()
        file(COPY ${module_location} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${configuration}/${plugin_type}")
      #endif()

      if(module_dependencies)
        use_qt5_module(${_target} ${module_dependencies})
      endif()

    endforeach()
  endforeach() 
endfunction()

# USE_QT5_MODULES(target ARGS): Find the provided Qt's modules Dlls and its 
#                                       dependencies and copy to the target output
#                                       to run it out of the box.
macro(USE_QT5_MODULES _target)
  foreach(module ${ARGN})
    if(NOT TARGET ${module})
      message( FATAL_ERROR "Qt 5 Module not found: " ${module})
    endif()
  endforeach() 
  use_qt5_module(${_target} ${ARGN}) 
endmacro()

# ADD_TEST(_target ARGS): Add target to run on ctest command.
macro(ADD_TEST _target)
  add_test(NAME ${_target}
           WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIR}
           COMMAND ${_target}
           #--gtest_output=xml:${CMAKE_BINARY_DIR}/Reports/tests/${_target}.xml
           ${ARGN}
          )
endmacro()