from fbx.jsapi import PyJSAPI
#from decimal import exp

class PyHelloWorld:

	def __init__(self):
		self.double_val = 1.0 # 2*math.asin(1)
		self.int_val = 11
		self.long_val = long(99999999999999999)
		self.bool_val = True
		
	def hello_py(self):
		return "js? is it you? omg , this is awesome :)"
	
	def __str__(self):
		return "PyHelloWorld"

	def double_method(self, val):
		return self.double_val*val
	
	def string_method(self, msg):
		return "you said: " + str(msg)

	def int_method(self, val):
		return self.int_val + val

	def long_method(self, val):
		return self.long_val + val

	def bool_method(self, val):
		return self.bool_val ^ val

class HelloWorldExtension:
	
	@staticmethod
	def createJSAPI():
		libObj = PyHelloWorld()
		jsapi = PyJSAPI(libObj)
		return jsapi
