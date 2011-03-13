cmake_minimum_required(VERSION 2.4.4)

project(firebreath-x)

set(FIREBREATH_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/FireBreath" CACHE PATH "Path to firebreath")
set(FB_PROJECTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/projects" CACHE PATH "root directory for fb projects")

set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/FireBreath/src/3rdParty/boost" CACHE PATH "Path to boost")

#include(FindPythonLibs)

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

set (SWIG_EXE "swig.exe" CACHE FILE "Swig executable.")

   
add_subdirectory(third_party)

add_subdirectory(src/python)

