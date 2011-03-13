#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for PyHelloWorld
#
#\**********************************************************/

set(PLUGIN_NAME "PyHelloWorld")
set(PLUGIN_PREFIX "PHW")
set(COMPANY_NAME "FireBreath")

# ActiveX constants:
set(FBTYPELIB_NAME PyHelloWorldLib)
set(FBTYPELIB_DESC "PyHelloWorld 1.0 Type Library")
set(IFBControl_DESC "PyHelloWorld Control Interface")
set(FBControl_DESC "PyHelloWorld Control Class")
set(IFBComJavascriptObject_DESC "PyHelloWorld IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "PyHelloWorld ComJavascriptObject Class")
set(IFBComEventSource_DESC "PyHelloWorld IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 5eee79fe-6db6-500e-93ae-ce280928abdc)
set(IFBControl_GUID 7072971e-0e86-5646-bd32-6cd26430a068)
set(FBControl_GUID 8c5ba8a9-94cd-5972-8357-dc546024e3c8)
set(IFBComJavascriptObject_GUID 4d7f21b5-d214-56ba-88bd-497615b3ec65)
set(FBComJavascriptObject_GUID 2b5d297a-e116-5c2b-a1ef-17d22d355f54)
set(IFBComEventSource_GUID 8e4525b3-9b0d-5cb4-82ac-1d8fc85f4c9c)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "FireBreath.PyHelloWorld")
set(MOZILLA_PLUGINID "firebreath.org/PyHelloWorld")

# strings
set(FBSTRING_CompanyName "firebreath-x")
set(FBSTRING_FileDescription "a simple plugin that's actions are done in a py runtime")
set(FBSTRING_PLUGIN_VERSION "1.0.0")
set(FBSTRING_LegalCopyright "Copyright 2011 firebreath-x")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "PyHelloWorld")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "PyHelloWorld")
set(FBSTRING_MIMEType "application/x-pyhelloworld")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
