cmake_minimum_required(VERSION 2.6)

# =============================================================================
# fbx module
# =============================================================================

project(firebreath.py)

if(WIN32)
foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
   endif(${flag_var} MATCHES "/MD")
endforeach(flag_var)
endif()

set(FIREBREATH_INCLUDE_DIRS 
		${FIREBREATH_ROOT}/src/ScriptingCore
		${FIREBREATH_ROOT}/src/config
)

set (FBPY_MODULE_NAME FireBreath)

	# set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} /MT)
	# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" /MT)
	# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE}" /MT)
	# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" /MT)
	# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE}" /MT)

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
	
set(FBX_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FBXVariant.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FBXJSAPI.cpp)
add_library(fbxlib ${FBX_SOURCES})
#target_link_libraries(fbxlib ScriptingCore)

	
add_custom_command(
    TARGET fbxlib
    PRE_BUILD
	# OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}.py 
		   # ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp 
		   # ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.h
	COMMAND ${SWIG_EXE} -c++ -python 
						-outdir ${CMAKE_CURRENT_BINARY_DIR}/fbx 
						-o ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp 
						${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FireBreath.i
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FireBreath.i ${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FBXVariant.h
	COMMENT "Generating python wrapper for firebreath"
	VERBATIM
)


link_directories(${PYTHON_LIBRARIES})

add_library(fbx_py MODULE ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp)
target_link_libraries(fbx_py fbxlib ScriptingCore)

get_property(fbx_py_location TARGET fbx_py PROPERTY LOCATION)

add_custom_command(
    TARGET fbx_py
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${fbx_py_location} ${CMAKE_CURRENT_BINARY_DIR}/fbx/_FireBreath.pyd
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/setup.py ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fbx ${CMAKE_CURRENT_BINARY_DIR}/fbx
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fbx/example ${CMAKE_CURRENT_BINARY_DIR}/fbx/example
	COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/setup.py install
)
