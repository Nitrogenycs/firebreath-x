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

link_directories(${PYTHON_LIBRARIES})

# TODO:
#   To allow bundling Firebreath.py with the plugins dll
#   SWIGs output has to be adapted so that the init_FireBreath is loaded from plugin
#   I have created a patch which itself has to be configured for each plugin (->name of dll)
#   PyInstaller is therefor mandatory, otherwise we would have to install different firebreath.py modules for each plugin
#   With PyInstaller the python code is precompiled and bundled with the plugin's dll.
#   Start with the generated swig py module and apply a patch which has to be configured before, as so:
# TODO: is this name exported by FireBreath?
set(PLUGIN_NAME "PyHelloWorld")
#TODO: the plugin name should be exported by the plugin configuration
set(PLUGIN_LIBRARY np${PLUGIN_NAME}.dll)
configure_file(${FBX_PY_ROOT}/patches/FireBreath.py.patch ${CMAKE_CURRENT_BINARY_DIR}/FireBreath.py.${PLUGIN_NAME}.patch)


add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp
	COMMAND ${SWIG_EXE} -c++ -python 
						-outdir ${CMAKE_CURRENT_BINARY_DIR}/fbx 
						-o ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp 
						${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FireBreath.i
    # NOTE: Here the python FireBreath module is patched:
    COMMAND ${PATCH_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/fbx/FireBreath.py ${CMAKE_CURRENT_BINARY_DIR}/FireBreath.py.${PLUGIN_NAME}.patch 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FireBreath.i ${CMAKE_CURRENT_SOURCE_DIR}/../fbx/FBXVariant.h
	COMMENT "Generating python wrapper for firebreath"
	VERBATIM
)

add_library(fbx_py ${CMAKE_CURRENT_BINARY_DIR}/fbx/${FBPY_MODULE_NAME}_py_wrap.cpp)


add_custom_target(install_fbx
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/setup.py ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fbx ${CMAKE_CURRENT_BINARY_DIR}/fbx
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fbx/example ${CMAKE_CURRENT_BINARY_DIR}/fbx/example
	COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/setup.py install
	COMMENT "Intalling firebreath.py to python site-packages"
)
