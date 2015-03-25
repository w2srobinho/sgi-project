if(__INSTALL_INCLUDED)
  return()
endif()
set(__INSTALL_INCLUDED TRUE)

# default target to install CMAKE_INSTALL_PREFIX
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/bin")

# Get the subdirectories of ${curdir}
#
# GET_SUBDIRECTORIES(result out 
#                     curdir in
#                     )
# 
# result: returns a list containing the subdirectories.
# curdir: starting directory.
#
macro(GET_SUBDIRECTORIES result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${curdir}/${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
endmacro()

# Removes the files containing in ${files} that matches the ${exclude_files}.
#
# EXCLUDE_FILES(files in/out 
#                     exclude_files in
#                     )
# 
# files: input file list where the files must be removed.
# exclude_files: list of files to remove.
#
macro(EXCLUDE_FILES files exclude_files)
  set(exclude_file_list "")
  foreach(file ${files})
    foreach(exclude_file ${exclude_files})
      if("${file}" MATCHES "${exclude_file}")
        list(APPEND exclude_file_list ${file})
      endif()
    endforeach()
  endforeach()

  if(exclude_file_list)
    list(REMOVE_ITEM files ${exclude_file_list})
  endif()
endmacro()


# Installs the application in CMAKE_INSTALL_PREFIX directory.
#
# INSTALL_APP(TARGET <target> 
#                     CONFIGURATION <configuration> 
#                     INSTALL_DIR <directory>
#                     [ADDITIONAL_FILES files patterns...]
#                     [EXCLUDE_FILES exclude files patterns...]
#                     [COPY_DIRECTORIES copy directories patterns...]
#                     )
# 
# TARGET: the app cmake target.
# CONFIGURATION: the build configuration (Debug, Release...).
# INSTALL_DIR: installation directory, the app and its files will be installed 
#               in "CMAKE_INSTALL_PREFIX/INSTALL_DIR".
# ADDITIONAL_FILES: Additional include files list, this can be a regular expression.
# EXCLUDE_FILES: A list of files to be ignored, this can be a regular expression.
# COPY_DIRECTORIES: A list of directories to copy to the installation dir, this can be a regular expression.
#
macro(INSTALL_APP)
  set(oneValueArgs TARGET CONFIGURATION INSTALL_DIR)
  set(multiValueArgs ADDITIONAL_FILES EXCLUDE_FILES COPY_DIRECTORIES)
  cmake_parse_arguments(ARG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  install(
    TARGETS ${ARG_TARGET} 
    DESTINATION ${ARG_INSTALL_DIR} 
    CONFIGURATIONS ${ARG_CONFIGURATION}
    )
  
  FILE(GLOB files ${ARG_ADDITIONAL_FILES})
  EXCLUDE_FILES("${files}" "${ARG_EXCLUDE_FILES}")
  install(
    FILES ${files} 
    DESTINATION ${ARG_INSTALL_DIR} 
    CONFIGURATIONS ${ARG_CONFIGURATION}
    )

  GET_SUBDIRECTORIES(directories "${ARG_COPY_DIRECTORIES}")
  install(
    DIRECTORY ${directories} 
    DESTINATION ${ARG_INSTALL_DIR}
    CONFIGURATIONS ${ARG_CONFIGURATION}
    )
endmacro()
