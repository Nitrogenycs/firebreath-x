from fbx.jsapi import PyJSAPI

class PyHelloWorld:

	def __init__(self):
		pass
		
	def hello_py(self, msg):
		return "js? is it you? omg , this is awesome :)"

class HelloWorldExtension:
	
	@staticmethod
	def createJSAPI():
		libObj = PyHelloWorld()
		jsapi = PyJSAPI(libObj)
		return jsapi
