using System;
using System.Reflection;
using System.Collections;
using System.Linq;
using FireBreath;

using System.Dynamic;

//using System.Windows.Forms; // remember to remove the assembly

namespace FireBreath
{
    public class ObjectJSAPI : FBXJSAPI
    {
        object wrappedObject;
        Type type;

        public ObjectJSAPI(object WrappedObject)
        {
            wrappedObject = WrappedObject;
            type = wrappedObject.GetType();
        }


        // ----- member enumeration ------

        public override StringVector getMemberNames()
        {
            StringVector result = new StringVector();
            foreach (MemberInfo memberInfo in type.GetMembers())
            {
                result.Add(memberInfo.Name);
            }
            return result;
        }

        public override uint getMemberCount()
        {
            return (uint)type.GetMembers().Length;
        }


        // ----- HasProperty methods ------

        public override bool HasProperty(string propertyName)
        {
            fbxvariant temp = new fbxvariant();
            return GetProperty(propertyName, temp).success;
        }
        public override bool HasProperty(int idx)
        {
            fbxvariant temp = new fbxvariant();
            return GetProperty(idx, temp).success;
        }


        // ----- GetProperty methods ------

        FBXResult GetIndexedProperty(object idx, fbxvariant value)
        {
            object obj;
            PropertyInfo property = type.GetProperty("Item");
            if (property != null)
            {
                try
                {
                    obj = property.GetValue(this.wrappedObject, new object[] { idx });
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return obj.ConvertFromNet(value);
            }
            // need to check if this.wrappedObject can be indexed directly?
            return new FBXResult(false, "Property '" + idx + "' not found");
        }

        public override FBXResult GetProperty(int idx, fbxvariant value)
        {
            //MessageBox.Show("GetProperty #1 " + idx);
            return GetIndexedProperty(idx, value);
        }

        public override FBXResult GetProperty(string propertyName, fbxvariant value)
        {
            // possible types: all, constructor, custom, event, field, method, nested type, property, typeinfo
            object obj;
            FieldInfo field = type.GetField(propertyName);
            if (field != null)
            {
                try
                {
                    obj = field.GetValue(this.wrappedObject);
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return obj.ConvertFromNet(value);
            }

            PropertyInfo property = type.GetProperty(propertyName);
            if ( property != null )
            {
                try
                {
                    obj = property.GetValue(this.wrappedObject, null);
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return obj.ConvertFromNet(value);
            }

            /*MethodInfo method = type.GetMethod(propertyName);
            if (method != null)
                return (new MethodCall(this.wrappedObject, method)).ConvertFromNet(value);*/

            FBXResult result = GetIndexedProperty(propertyName, value);
            if (!result.success)
            {
                int idx;
                if (Int32.TryParse(propertyName, out idx))
                {
                    return GetIndexedProperty(idx, value);
                }
            }
            return result;
        }


        // ----- SetProperty methods ------

        FBXResult SetIndexedProperty(object idx, object value)
        {
            PropertyInfo property = type.GetProperty("Item");
            if (property != null)
            {
                try
                {
                    property.SetValue(this.wrappedObject, value, new object[]{idx});
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return FBXResult.successful;
            }

            return new FBXResult(false, "Property '" + idx + "' not found");
        }
        
        
        public override FBXResult SetProperty(int idx, fbxvariant value)
        {
            object result;
            FBXResult returnValue = value.ConvertToNet(out result);
            if (!returnValue.success)
                return returnValue;

            return SetIndexedProperty(idx, result);
        }

        public override FBXResult SetProperty(string propertyName, fbxvariant value)
        {
            object convertedValue;
            FBXResult returnValue = value.ConvertToNet(out convertedValue);
            if (!returnValue.success)
                return returnValue;

            FieldInfo field = type.GetField(propertyName);
            if (field != null)
            {
                try
                {
                    field.SetValue(this.wrappedObject, convertedValue);
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return returnValue;
            }

            PropertyInfo property = type.GetProperty(propertyName);
            if (property != null)
            {
                try
                {
                    property.SetValue(this.wrappedObject, convertedValue, null);
                }
                catch (Exception e)
                {
                    return new FBXResult(false, e.ToString());
                }
                return returnValue;
            }

            /*MethodInfo method = type.GetMethod(propertyName);
            if (method != null)
                return (new MethodCall(this.wrappedObject, method)).ConvertFromNet(value);*/

            FBXResult result = SetIndexedProperty(propertyName, convertedValue);
            if (!result.success)
            {
                int idx;
                if (Int32.TryParse(propertyName, out idx))
                {
                    return SetIndexedProperty(idx, convertedValue);
                }
            }
            return result;
        }


        // ------- Method related -------

        public override bool HasMethod(string methodName)
        {
            //MessageBox.Show("HasMethod " + methodName);
            return type.GetMethod(methodName) != null;
        }

        public override FBXResult Invoke(string methodName, VariantVector args, fbxvariant result)
        {
            //MessageBox.Show("Invoke " + methodName);
            System.Collections.Generic.List<object> convertedArgs = new System.Collections.Generic.List<object>();
            foreach( fbxvariant arg in args )
            {
                object converted;
                FBXResult returnValue = arg.ConvertToNet(out converted);
                if (!returnValue.success)
                    return returnValue;
                convertedArgs.Add(converted);
            }
            object[] arguments = convertedArgs.ToArray();

            if (methodName == "")
            {
                //MessageBox.Show("InvokeConstructor " + (this.wrappedObject is Type));
                if (this.wrappedObject is Type)
                {
                    System.Collections.Generic.List<Type> types = new System.Collections.Generic.List<Type>();
                    foreach (object arg in arguments)
                    {
                        types.Add(arg.GetType());
                    }
                    ConstructorInfo constructorInfo = ((Type)this.wrappedObject).GetConstructor(types.ToArray());
                    if (constructorInfo != null)
                    {
                        object newObject;
                        try
                        {
                            newObject = constructorInfo.Invoke(arguments);
                        }
                        catch (Exception e)
                        {
                            return new FBXResult(false, e.ToString());
                        }
                        return newObject.ConvertFromNet(result);
                    }
                }
                return new FBXResult(false, "Method '" + methodName + "' not callable");
                //((MethodCall)this.wrappedObject).call(arguments).ConvertFromNet(result);
            }
            else
            {
                MethodInfo method = type.GetMethod(methodName);
                if ( method != null)
                {
                    object methodResult;
                    //type.InvokeMember(methodName, BindingFlags.Public /*| BindingFlags.NonPublic */| BindingFlags.Instance | BindingFlags.Static, null, this.wrappedObject, arguments).ConvertFromNet(result);
                    try
                    {
                        methodResult = method.Invoke(this.wrappedObject, arguments);
                    }
                    catch (Exception e)
                    {
                        return new FBXResult(false, e.ToString());
                    }
                    return methodResult.ConvertFromNet(result);
                }
            }

            return new FBXResult(false, "Method '" + methodName + "' not found");
        }
    }
    
}


/*

    nitrogenycs	JSAPI::HasProperty is called when you do obj['blabla'] or obj.blbla right?
	nitrogenycs	Now, when is JSAPI::HasMethod called?
	nitrogenycs	if HasProperty() is called with a name like "myMethod" should it return the method or not?
	nitrogenycs	I guess no?
	taxilian		nitrogenycs: sorry, I'm back

	nitrogenycs	taxilian: no problem
	taxilian	so that's a tricky question
	taxilian	it always calls HasProperty
	taxilian	to see if it is a property or not
	taxilian	in FireBreath, as of 1.4, HasProperty will return true for methods most of hte time as well
	taxilian	and then it returns a JSAPI method object
	taxilian	which is a jsapi object which you can call ->Invoke("", <args>)
	nitrogenycs	ok
	taxilian	that's not really required, though; it just makes it so you can do something like:
	nitrogenycs	So will Invoke ever be called with something else than ""?
	taxilian	var a = plugin.myMethod
	taxilian	a(1,2,3)
	taxilian	well, it could be
	taxilian	but by default usually isn't
	nitrogenycs	okay
	taxilian	I think there is a flag you can set to disable methodobjects
	taxilian	not sure, 'cause the guy who wrote all this stuff is a slacker who doesn't document things well
	nitrogenycs	lol
	nitrogenycs	is it enough to implement only the pure virtuals for a custom JSAPI?
	nitrogenycs	e.g. are things like the event automatically mapped to the GetProperty/GetMethod things?
	taxilian	hang on, let me open the class def for JSAPI
	taxilian	honestly I really should pull some things out of JSAPI because they don't always apply
	taxilian	the event stuff in particular
	taxilian	and make JSAPI more of an interface than it is
	taxilian	ignore all the zone stuff
	taxilian	ignore all the event stuff
	nitrogenycs	ok, currently trying to implement it for c# and python, we have the wrappers already written and they compile 
	taxilian	okay
	nitrogenycs	ok, I ignored events
	nitrogenycs	and only had zone for the constructor
	taxilian	other than those, most of the methods that aren't pure virtual are just specializations of methods that are
	taxilian	i.e. allow wstring instead of string
	nitrogenycs	yes
	nitrogenycs	I used only the pure virtuals
	nitrogenycs	ok, now last question about the method objects
	taxilian	HasMethodObject, etc, is just if you want to support those
	taxilian	it's optional
	nitrogenycs	method object is so you could do the var a= plugin.myMethod; a(1,2,3); stuff right?
	taxilian	right
	nitrogenycs	if I don't implement methodobject I can only do plugin.myMethod(1,2,3)
	nitrogenycs	correct?
	taxilian	right
	nitrogenycs	ok cool
	nitrogenycs	then I'll implement those as well
	taxilian	I'd start without
	taxilian	and then add them
	taxilian	I'm not totally sure I did it in as clean of a way as it should be
	taxilian	but look at JSAPIAuto for an example of how it works
	nitrogenycs	ok
	taxilian	I think it ends up sometimes getting it from GetProperty instead of GetMethodObject, but I don't remember for sure
	nitrogenycs	okay
	nitrogenycs	I'll write some test code to check
	nitrogenycs	ohhh
	nitrogenycs	property deletion is triggered by SetProperty(name, undefined)?
	taxilian	currently, actually, I don't think it's implemented
	nitrogenycs	ok
	taxilian	feel free to implement it
	taxilian	=]
	taxilian	and send me a patch
	nitrogenycs	 ok
	nitrogenycs	i'll first get this going, then I'll refine
	taxilian	would actually be pretty easy

*/