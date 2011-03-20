cmake_minimum_required(VERSION 2.4.4)

project(firebreath-x)

# Pre-Requisites:
# ===============

# Boost:
# -------
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/FireBreath/src/3rdParty/boost" CACHE PATH "Path to boost")

# Python:
# -------
find_package(PythonInterp)
# note: there is some bug in FindPythonLibs module (does not find installed directories)
# 		so it is deactivated
#find_package(PythonLibs)
#if(!PYTHONLIBS_FOUND)
	set(PYTHON_ROOT "" CACHE PATH "Path to python")
	set(PYTHON_INCLUDE_DIR ${PYTHON_ROOT}/Include CACHE INTERNAL "python includes" FORCE)
	set(PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_DIR} CACHE INTERNAL "python includes" FORCE)
	set(PYTHON_LIBRARIES ${PYTHON_ROOT}/libs CACHE INTERNAL "python includes" FORCE)
#endif()


# SWIG:
# -----
set (SWIG_EXE "swig.exe" CACHE FILEPATH "Swig executable.")


# PATCH:
# ------
find_program(PATCH_EXECUTABLE patch ENV PATH)
if (${PATCH_EXECUTABLE-NOTFOUND})
   message(FATAL_ERROR "Could not find 'patch' utility in path.")
endif()


# Internal variables:
# ===================

set(FBX_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(FBX_PY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/python)

set(FIREBREATH_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/FireBreath" CACHE FILEPATH "Path to firebreath")
set(FIREBREATH_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/third_party/FireBreath" CACHE INTERNAL "Path of fb projects")
set(FB_PROJECTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/projects" CACHE FILEPATH "root directory for fb projects")

# Sub-projects:
# =============
   
add_subdirectory(third_party)
add_subdirectory(src/python)

# Patching:
# =========

file(GLOB_RECURSE PROJECT_CMAKE_FILES ${FB_PROJECTS_DIR}/**/CMakeLists.txt)
#message("Found project configurations: " ${PROJECT_CMAKE_FILES})
foreach(CONFIG_FILE ${PROJECT_CMAKE_FILES})
    if(NOT EXISTS ${CONFIG_FILE}.orig)
        message("saving original firebreath project configuration file ${CONFIG_FILE}.")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy ${CONFIG_FILE} ${CONFIG_FILE}.orig
        )
    endif()
    # NOTE: for registering a successful patch, ${CONFIG_FILE}.readme is created 
    # TODO: this is somewhat hacky...
    if(NOT EXISTS ${CONFIG_FILE}.patched)
        message("patching project configuration ${CONFIG_FILE}.")
        execute_process(
            COMMAND ${PATCH_EXECUTABLE} -N ${CONFIG_FILE} ${FBX_PY_ROOT}/patches/CMakeLists.FireBreath.patch
            ERROR_VARIABLE CONFIG_FILE_PATCH_ERROR
        )
        if(NOT DEFINED ${CONFIG_FILE_PATCH_ERROR})
            file(WRITE ${CONFIG_FILE}.patched "CMakeLists.txt has been patched successfully.")
        endif()
    endif()
endforeach()
