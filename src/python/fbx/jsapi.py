from FireBreath import *

class JSAPI(FBXJSAPI):

	def __init__(self, wrappedObj):
		self.wrappedObj = wrappedObj

	def getMemberNames(self):
		names = ["xxx"]
		return names

    def getMemberCount(self):
		return 1

    def HasProperty(self):
		return False
		
	def HasProperty(self, idx):
		return True
        
    def GetProperty(self, idx, value):
		return True
		
	def GetProperty(self, propertyName, value):
		return True

    def SetProperty(self, idx, value):
		return True

	def SetProperty(self, propertyName, value):
		return True

    def HasMethod(self, methodName):
		return false;

    def Invoke(self, methodName, args, result):
		return True
