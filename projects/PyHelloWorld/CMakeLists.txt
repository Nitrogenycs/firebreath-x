#/**********************************************************\ 
# 
# Auto-generated CMakeLists.txt for the PyHelloWorld project
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

include_directories(${PLUGIN_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${FBX_ROOT}/src/fbx)
link_directories(${PYTHON_LIBRARIES})

# Generated files are stored in ${GENERATED} by the project configuration
SET_SOURCE_FILES_PROPERTIES(
    ${GENERATED}
    PROPERTIES
        GENERATED 1
    )

SOURCE_GROUP(Generated FILES
    ${GENERATED}
    )

SET( SOURCES
    ${GENERAL}
    ${GENERATED}
    )

# This will include Win/projectDef.cmake, Linux/projectDef.cmake, etc
include_platform()

target_link_libraries(${PLUGIN_NAME} fbxlib fbx_py)

execute_process(
    #COMMAND ${CMAKE_COMMAND} -E copy ${FIREBREATH_BINARY_DIR}/projects/${PLUGIN_NAME}/gen/FireBreathWin.def.orig ${FIREBREATH_BINARY_DIR}/projects/${PLUGIN_NAME}/gen/FireBreathWin.def
    COMMAND ${PATCH_EXECUTABLE} ${FIREBREATH_BINARY_DIR}/projects/${PLUGIN_NAME}/gen/FireBreathWin.def ${FBX_PY_ROOT}/patches/FireBreath.def.patch
)
