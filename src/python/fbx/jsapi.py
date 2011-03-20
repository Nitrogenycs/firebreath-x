from FireBreath import *
from conversion import ConvertToPy

class PyJSAPI(FBXJSAPI):

    def __init__(self, wrappedObj):
        
        FBXJSAPI.__init__(self)
        self.wrappedObj = wrappedObj
        
        self.member_names = StringVector()

        self.dict = wrappedObj.__class__.__dict__
        self.property_names = set()
        self.method_names = set()
        
        for m in self.dict.keys():
            self.member_names.append(m)
            if callable(getattr(wrappedObj, m)):
                self.method_names.add(m)
            else:
                self.property_names.add(m)
                
        self.method_map = {'constructor': '__init__', 'length': '__len__'}

        pass

    def getMemberNames(self):
        return self.member_names
    
    def getMemberName(self, idx):
        return self.member_names[idx]

    def getMemberCount(self):
        return self.member_names.size()
        
    def HasProperty(self, arg):
        if isinstance(arg, str):
            return self.property_names.__contains__(arg)
        elif isinstance(arg, int):
            return self.property_names.__contains__(self.member_names[arg])

        return False

    def GetProperty0(self, propertyName, value):
        prop = getattr(self.wrappedObj, propertyName)
        try:
            value.set(prop)
        except RuntimeError as err:
            return FBXResult(False, str(err))

        return FBXResult(True)

    def GetProperty(self, arg, value):
        if isinstance(arg, str):
            return self.GetProperty0(arg, value)
        elif isinstance(arg, int):
            return self.GetProperty0(self.member_names[arg], value)
        
    def SetProperty0(self, propertyName, value):
        try:
            new_val = ConvertToPy(value)
            setattr(self.wrappedObj, propertyName, new_val)
        except RuntimeError as err:
            return FBXResult(False, str(err))
        
        return FBXResult(True)

    def SetProperty(self, arg, value):

        if isinstance(arg, str):
            return self.SetProperty0(arg, value)

        elif isinstance(arg, int):
            return self.SetProperty0(self.member_names[arg], value)


    def HasMethod(self, methodName):
        # TODO: there are some methods that must be mapped to python naming
        # "compilation_unit_type"
        # "__proto__"
        if self.method_map.__contains__(methodName):
            return self.method_names.__contains__(self.method_map[methodName])
        else:
            return self.method_names.__contains__(methodName)

    def Invoke(self, methodName, args, result):
        
        func = getattr(self.wrappedObj, methodName)

        if func == None:
            return FBXResult(False, "Could not get function " + str(methodName))
            
        py_args = []
        try:
            for arg in args:
                pyArg = ConvertToPy(arg)
                py_args.append(pyArg)
        except RuntimeError as err:
            return FBXResult(False, "Could not convert argument " + str(arg) + ": " + str(err))
                
        try:
            py_result = apply(func, py_args)
            result.set(py_result)
        except object as err:
            return FBXResult(False, "Error in method " + str(func)+ ": " + str(err))
        
        return FBXResult(True)
