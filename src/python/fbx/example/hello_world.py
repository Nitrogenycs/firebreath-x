from fbx.jsapi import PyJSAPI, PyExtension
import math
from fbx.FireBreath import *

class Callback():
	
	def callMe(self):
		pass
	
	def __str__(self):
		return "Callback"

class PyHelloWorld:

	def __init__(self):
		self.double_val = 2*math.asin(1)
		self.int_val = 11
		self.long_val = long(99999999999999999)
		self.bool_val = True
		self.callbacks = []
		
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

	def dict_method(self, val):
		return str(dir(val))
	
	def get_list(self):
		return [1,2,3]
	
	def get_dict(self):
		return {"key1": 1, "key2": 2}

	def addCallback(self, callback):
		self.callbacks.append(callback)
		
	def shout(self):
		for callback in self.callbacks:
			callback.callMe()
		return None

	def callMeBackWithDirector(self, bla):
		res = bla.callMe()
		return res


class HelloWorldExtension():
	
	@staticmethod
	def createJSAPI():
		pyObj = PyHelloWorld()
		return PyJSAPI(PyExtension(pyObj))
