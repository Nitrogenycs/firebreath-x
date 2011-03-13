#/**********************************************************\ 
# Auto-generated Windows project definition file for the
# FBX Simple Test Plugin (C#) project
#\**********************************************************/

# Windows template platform definition CMake file
# Included from ../CMakeLists.txt

# remember that the current source dir is the project root; this file is in Win/
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Win/[^.]*.cpp
    Win/[^.]*.h
    Win/[^.]*.cmake
    )

# use this to add preprocessor definitions
add_definitions(
    /D "_ATL_STATIC_REGISTRY"
)

SOURCE_GROUP(Win FILES ${PLATFORM})

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

add_windows_plugin(${PROJECT_NAME} SOURCES)

get_filename_component(PLATFORMSDK_DIR "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows\\v7.0A;InstallationFolder]" REALPATH CACHE)  
include_directories( ${PLATFORMSDK_DIR}/include )

# This is an example of how to add a build step to sign the plugin DLL before
# the WiX installer builds.  The first filename (certificate.pfx) should be
# the path to your pfx file.  If it requires a passphrase, the passphrase
# should be located inside the second file. If you don't need a passphrase
# then set the second filename to "".  If you don't want signtool to timestamp
# your DLL then make the last parameter "".
#
# Note that this will not attempt to sign if the certificate isn't there --
# that's so that you can have development machines without the cert and it'll
# still work. Your cert should only be on the build machine and shouldn't be in
# source control!
# -- uncomment lines below this to enable signing --
#firebreath_sign_plugin(${PROJECT_NAME}
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
#    "http://timestamp.verisign.com/scripts/timestamp.dll")

# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there unless you know what you're doing!
target_link_libraries(${PROJECT_NAME}
    ${PLUGIN_INTERNAL_DEPS}
	${PLATFORMSDK_DIR}/lib/mscoree.lib
    )

set(WIX_HEAT_FLAGS
    -gg                 # Generate GUIDs
    -srd                # Suppress Root Dir
    -cg PluginDLLGroup  # Set the Component group name
    -dr INSTALLDIR      # Set the directory ID to put the files in
    )

add_wix_installer( ${PLUGIN_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Win/WiX/FBXSimpleTestPluginCSharpInstaller.wxs
    PluginDLLGroup
    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/
    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll
    ${PROJECT_NAME}
    )

# This is an example of how to add a build step to sign the WiX installer
# -- uncomment lines below this to enable signing --
#firebreath_sign_file("${PLUGIN_NAME}_WiXInstall"
#    "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${PLUGIN_NAME}.msi"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
#    "http://timestamp.verisign.com/scripts/timestamp.dll")
