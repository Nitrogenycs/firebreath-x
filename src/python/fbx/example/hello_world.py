from fbx.jsapi import PyJSAPI

class PyHelloWorld:

	def __init__(self):
		pass
		
	def hello_py(self, msg):
		return msg

class HelloWorldExtension:
	
	@staticmethod
	def createJSAPI():
		libObj = PyHelloWorld()
		jsapi = PyJSAPI(libObj)
		return jsapi
