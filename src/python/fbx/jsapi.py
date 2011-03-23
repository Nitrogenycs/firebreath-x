from FireBreath import *
    
def jsMethodWrapper(jsapiObj, name):
    try:
        def _func(*pyArgs):
            result = fbxvariant()
            jsArgs = VariantVector()
            for arg in pyArgs:
                jsArgs.push_back(ConvertFromPy(arg))
            jsapiObj.Invoke(name, jsArgs, result)
            return ConvertToPy(result)
        return _func
    except:
        raise RuntimeError("Could not wrap method %s"%(name))

class JSDirector(object):
    def __init__(self, obj):
        members = {}
        memberNames = obj.getMemberNames()
        for name in memberNames:
            if obj.HasMethod(name):
                members[name] = jsMethodWrapper(obj, name)
            else:
                members[name] = None
                
        object.__setattr__(self, 'jsapiObj', obj)
        object.__setattr__(self, 'members', members)

    def __getattr__(self, name):
        if not self.__dict__['members'].__contains__(name):
            raise AttributeError("Missing attribute %s"%(name))
        
        if self.__dict__['members'][name] == None:
            jsProp = fbxvariant()
            fbxresult = self.__dict__['jsapiObj'].GetProperty(name, jsProp)
            if not fbxresult.success:
                raise RuntimeError("Error in get_%s: %d"%(name, err))
            return ConvertToPy(jsProp)
        else:
            # then it is a method wrapper
            return self.__dict__['members'][name]
        
    def __setattr__(self, name, value):
        if not self.__dict__['members'].__contains__(name):
            raise AttributeError("Missing attribute %s"%(name))
        
        if self.__dict__['members'][name] == None:
            jsProp = fbxvariant()
            ConvertFromPy(jsProp, value)
            fbxresult = self.__dict__['jsapiObj'].SetProperty(name, jsProp)
            if not fbxresult.success:
                raise RuntimeError("Error in set_%s: %d"%(name, err))
        else:
            raise RuntimeError('Director methods are read only')

        return None
    

def ConvertToPy(value):
    _type_ = value.get_type()
    
    if _type_ == "bool":
        return value.get_bool()
    elif _type_ == "int":
        return value.get_int()
    elif _type_ == "uint":
        return value.get_uint()
    elif _type_ == "double":
        return value.get_double()
    elif _type_ == "float":
        return value.get_float()
    elif _type_ == "wstring":
        return value.get_wstring()
    elif _type_ ==  "short":
        return value.get_short()
    elif _type_ ==  "ushort":
        return value.get_ushort()
    elif _type_ ==  "char":
        return value.get_char()
    elif _type_ ==  "uchar":
        return value.get_uchar()
    elif _type_ ==  "int64":
        return value.get_int64()
    elif _type_ ==  "uint64":
        return value.get_uint64()
    elif _type_ ==  "object" or _type_ == "jsapi":
        try:
            jsapiObj = value.get_object()
            return JSDirector(jsapiObj)
        except SyntaxError as syntaxErr:
            raise RuntimeError("SyntaxError: %s"%(str(syntaxErr)))
        except AttributeError as attErr:
            raise RuntimeError("Error: %s"%(str(attErr)))
        except:
            raise RuntimeError("Error: could not convert js object")
    else:
        raise RuntimeError("Unknown type: %s"%(_type_))

def ConvertFromPy(result, value):
    if(value == None):
        result.set_empty()
        return FBXResult(True)
    elif ( isinstance(value, int) or isinstance(value, float) or isinstance(value, bool) or isinstance(value, str)):
        result.set(value)
        return FBXResult(True)
    else:
        try:
            jsWrapper = PyJSAPI(value)
            jsWrapper.__disown__()
            result.set(jsWrapper)
            return FBXResult(True)
        except:
            return FBXResult(False, 'Could not wrap non-primitive type %s'%(str(type(value))))

class PyExtension():
    
    def __init__(self, pluginObj):
        self.pluginObj = pluginObj
        
    def getPlugin(self):
        return self.pluginObj

    def analyze(self, val):
        return str(val.__dict__)

class PyJSAPI(FBXJSAPI):

    def __init__(self, wrappedObj):
        
        FBXJSAPI.__init__(self)
        self.wrappedObj = wrappedObj
        
        self.member_names = StringVector()

        self.dir = dir(wrappedObj)
        self.property_names = set()
        self.method_names = set()
        
        for m in self.dir:
            self.member_names.append(m)
            if callable(getattr(wrappedObj, m)):
                self.method_names.add(m)
            else:
                self.property_names.add(m)
                
        self.method_map = {'constructor': '__init__', 'length': '__len__', 'toString': '__str__'}

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
        
        if(prop == None):
            value.set_empty()
            return FBXResult(False, "Tried to access non existing property: %s"%(propertyName))
        
        try:
            value.set(prop)
        except RuntimeError as err:
            return FBXResult(False, str(err))
        except:
            return FBXResult(False, "Could not get property %s"%(propertyName))

        return FBXResult(True)

    def GetProperty(self, arg, value):
        if isinstance(arg, str):
            return self.GetProperty0(arg, value)
        elif isinstance(arg, int):
            return self.GetProperty0(self.member_names[arg], value)
        
    def SetProperty0(self, propertyName, value):

        if not self.HasProperty(propertyName):
            return FBXResult(False, "Tried to set non existing property: %s"%(propertyName))

        try:
            new_val = ConvertToPy(value)
            setattr(self.wrappedObj, propertyName, new_val)
        except RuntimeError as err:
            return FBXResult(False, str(err))
        except:
            return FBXResult(False, "Could not set property %s"%(propertyName))
        
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

        if self.method_map.__contains__(methodName):
            methodName = self.method_map[methodName];
        
        if not self.method_names.__contains__(methodName):
            return FBXResult(False, "Instance %s has no method %s.\n Available methods: %s"%(str(self.wrappedObj), str(methodName), str(self.method_names)))
            
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
        except: 
            return FBXResult(False, "Could not convert argument " + str(arg))
        
        try:
            py_result = apply(func, py_args)
        except RuntimeError as err:
            return FBXResult(False, "Error in method " + str(func)+ ": " + str(err))
        except:
            return FBXResult(False, "Error during call of method %s. Tried: apply(%s, %s)"%(methodName, str(func), str(py_args)))

        try:
            ConvertFromPy(result, py_result)
        except RuntimeError as err:
            return FBXResult(False, "Could not convert result of method " + str(func)+ ": " + str(err))
        except: 
            return FBXResult(False, "Could not convert result of method " + str(func))
        
        return FBXResult(True)


#if __name__ == '__main__':
#        
#        bla = object()
#        jsapi = PyJSAPI(bla)
#        jsval = fbxvariant()
#        jsval.set(jsapi)
#        pyval = ConvertToPy(jsval)
#        print(pyval.bla())
#        pyval.x = 42
#        print("x=%d"%(pyval.x))
        
