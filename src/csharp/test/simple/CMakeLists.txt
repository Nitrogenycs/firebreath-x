#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the FBX Simple Test Plugin (C#) project
#
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project(${PLUGIN_NAME})

file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
    )

file (GLOB WRAPPER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ../../../fbx/[^.]*.cpp
    ../../generated/[^.]*.cpp
    ../../generated/[^.]*.h
    )
    
include_directories(${PLUGIN_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../../../fbx)

# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

SOURCE_GROUP(Wrapper FILES
    ${WRAPPER}
    )

SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    ${WRAPPER}
    )

# This will include Win/projectDef.cmake, Linux/projectDef.cmake, etc
include_platform()
