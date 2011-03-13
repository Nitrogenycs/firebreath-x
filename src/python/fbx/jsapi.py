from FireBreath import *

class PyJSAPI(FBXJSAPI):

    def __init__(self, wrappedObj):
        FBXJSAPI.__init__(self)
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
        return False;

    def Invoke(self, methodName, args, result):
        return True
