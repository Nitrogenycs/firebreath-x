cmake_minimum_required(VERSION 2.6)

project(firebreath.py)

set(FIREBREATH_INCLUDE_DIRS 
		${FIREBREATH_ROOT}/src/ScriptingCore
		${FIREBREATH_ROOT}/src/config
)

set (FBPY_MODULE_NAME FireBreath)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}.py 
		   ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp 
		   ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.h
	COMMAND ${SWIG_EXE} -c++ -python 
						-outdir ${CMAKE_CURRENT_BINARY_DIR}/fbx 
						-o ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp 
						${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FireBreath.i
#	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FireBreath.i ${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FBXAPI.h ${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FBXVariant.h
	COMMENT "Generating python wrapper for firebreath"
	VERBATIM
)

include_directories(
					${BOOST_ROOT}
					${PYTHON_INCLUDE_DIRS} 
					${CMAKE_CURRENT_SOURCE_DIR}/../fbx 
					${CMAKE_CURRENT_BINARY_DIR}/fbx
					${FIREBREATH_INCLUDE_DIRS}
)

if(WIN32)
	add_definitions(-DFB_WIN)
endif()
	
set(FBPY_SOURCES 
	${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FBXVariant.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FBXJSAPI.cpp)
add_library(fb_py ${FBPY_SOURCES})
