# Queue CMake configuration file:
# This file is meant to be placed in a cmake subfolder of QUEUE-devel-2.x.y-VC

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)
set_package_properties(QUEUE PROPERTIES
    URL "https://g10.app/status/#abstract_data_ii"
    DESCRIPTION "double queue ADT"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(QUEUE_FOUND TRUE)

# For compatibility with autotools QUEUE-config.cmake, provide QUEUE_* variables.

set_and_check(QUEUE_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(QUEUE_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(QUEUE_INCLUDE_DIR  "${QUEUE_PREFIX}/include")
set(QUEUE_INCLUDE_DIRS           "${QUEUE_INCLUDE_DIR}")
set_and_check(QUEUE_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(QUEUE_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(QUEUE_LIBRARIES double_queue::double_queue)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated QUEUE-target.cmake files.

set(_QUEUE_library     "${QUEUE_LIBDIR}/double_queue.lib")
set(_QUEUE_dll_library "${QUEUE_BINDIR}/double_queue.dll")
if(EXISTS "${_QUEUE_library}" AND EXISTS "${_QUEUE_dll_library}")
    if(NOT TARGET double_queue::double_queue)
        add_library(double_queue::double_queue SHARED IMPORTED)
        set_target_properties(double_queue::double_queue
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${QUEUE_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_QUEUE_library}"
                IMPORTED_LOCATION "${_QUEUE_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "QUEUE_SHARED"
                INTERFACE_QUEUE_SHARED "ON"
        )
    endif()
    set(QUEUE_QUEUE_FOUND TRUE)
else()
    set(QUEUE_QUEUE_FOUND FALSE)
endif()
unset(_QUEUE_library)
unset(_QUEUE_dll_library)

check_required_components(QUEUE)
