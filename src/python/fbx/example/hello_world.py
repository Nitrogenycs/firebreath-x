from fbx.jsapi import PyJSAPI
#from decimal import exp

class PyHelloWorld:

	def __init__(self):
		self.double_val = 1.0 # 2*math.asin(1)
#		self.int_val = 11
#		self.long_val = long(99999999999999999)
#		self.bool_val = True
		pass
		
	def hello_py(self):
		return "js? is it you? omg , this is awesome :)"
	
	def __str__(self):
		return "PyHelloWorld"

	def some_double_method(self, val):
		return self.double_val*val
	
#	def some_string_method(self, msg):
#		return "you said: " + str(msg)
#
#
#	def some_int_method(self, val):
#		return self.int_val + val
#
#	def some_long_method(self, val):
#		return self.long_val + val
#
#	def some_bool_method(self, val):
#		return self.bool_val ^ val

class HelloWorldExtension:
	
	@staticmethod
	def createJSAPI():
		libObj = PyHelloWorld()
		jsapi = PyJSAPI(libObj)
		return jsapi
