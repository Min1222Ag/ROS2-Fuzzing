# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_secretserver_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED secretserver_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(secretserver_FOUND FALSE)
  elseif(NOT secretserver_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(secretserver_FOUND FALSE)
  endif()
  return()
endif()
set(_secretserver_CONFIG_INCLUDED TRUE)

# output package information
if(NOT secretserver_FIND_QUIETLY)
  message(STATUS "Found secretserver: 0.0.0 (${secretserver_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'secretserver' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${secretserver_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(secretserver_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${secretserver_DIR}/${_extra}")
endforeach()
