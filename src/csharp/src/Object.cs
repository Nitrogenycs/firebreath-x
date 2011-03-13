using System;
using System.Reflection;
using System.Collections;
using System.Linq;
using FireBreath;

using System.Dynamic;

namespace FireBreath
{
    public class MyJSAPI : JSAPI
    {
        public override bool TryGetMember(GetMemberBinder binder, out dynamic result)
        {
            getbinder.Name
            return false;
        }
    }
    
    public class ObjectJSAPI : FBXJSAPI
    {
        object wrappedObject;
        Type type;

        public ObjectJSAPI(object WrappedObject)
        {
            wrappedObject = WrappedObject;
            type = wrappedObject.GetType();
        }

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

        public override bool HasProperty(string propertyName)
        {
            if ( type.GetMember(propertyName, MemberTypes.All, BindingFlags.Default).Length != 0 ) return true;
            IDictionary dict = this.wrappedObject as IDictionary;
            if ( dict != null )
                return dict.Contains(propertyName);

            return false;
        }
        public override bool HasProperty(int idx)
        {
            IList indexable = this.wrappedObject as IList;
            if ( indexable != null )
                return (idx >= 0) && (idx < indexable.Count);

            IDictionary dict = this.wrappedObject as IDictionary;
            if ( dict != null )
                return dict.Contains(idx);

            return false;
        }

        public override bool GetProperty(int idx, fbxvariant value)
        {
            IList indexable = this.wrappedObject as IList;
            if ( indexable != null )
                return indexable[idx].ConvertFromNet(value);

            IDictionary dict = this.wrappedObject as IDictionary;
            if ( dict != null )
                return dict[idx].ConvertFromNet(value);

            // need to check if this.wrappedObject can be indexed directly?
            return false;
        }
        public override bool GetProperty(string propertyName, fbxvariant value)
        {
            // possible types: all, constructor, custom, event, field, method, nested type, property, typeinfo
            FieldInfo field = type.GetField(propertyName);
            if (field != null)
                return field.GetValue(this.wrappedObject).ConvertFromNet(value);

            /*MethodInfo method = type.GetMethod(propertyName);
            if (method != null)
                return (new MethodCall(this.wrappedObject, method)).ConvertFromNet(value);*/

            PropertyInfo property = type.GetProperty(propertyName);
            if ( property != null )
                return property.GetValue(this.wrappedObject, null).ConvertFromNet(value);

            IDictionary dict = this.wrappedObject as IDictionary;
            if ( dict != null )
                return dict.Contains(propertyName);

            return false;
        }

        public override bool SetProperty(int idx, fbxvariant value)
        {
            IList indexable = this.wrappedObject as IList;
            if (indexable != null)
            {
                indexable[idx] = value.ConvertToNet();
                return true;
            }

            IDictionary dict = this.wrappedObject as IDictionary;
            if (dict != null)
            {
                dict[idx] = value.ConvertToNet();
                return true;
            }

            // need to check if this.wrappedObject can be indexed directly?
            return false;
        }
        public override bool SetProperty(string propertyName, fbxvariant value)
        {
            // possible types: all, constructor, custom, event, field, method, nested type, property, typeinfo
            FieldInfo field = type.GetField(propertyName);
            if (field != null)
            {
                field.SetValue(this.wrappedObject, value.ConvertToNet());
                return true;
            }

            /*MethodInfo method = type.GetMethod(propertyName);
            if (method != null)
                return (new MethodCall(this.wrappedObject, method)).ConvertFromNet(value);*/

            PropertyInfo property = type.GetProperty(propertyName);
            if (property != null)
            {
                property.SetValue(this.wrappedObject, value.ConvertToNet(), null);
                return true;
            }

            IDictionary dict = this.wrappedObject as IDictionary;
            if (dict != null)
            {
                dict[propertyName] = value;
                return true;
            }

            return false;
        }

        public override bool HasMethod(string methodName)
        {
            return type.GetMethod(methodName) != null;
        }

        public override bool Invoke(string methodName, VariantVector args, fbxvariant result)
        {
            System.Collections.Generic.List<object> arguments = new System.Collections.Generic.List<object>();
            foreach( fbxvariant arg in args )
            {
                arguments.Add( arg.ConvertToNet() );
            }

            if ( methodName == "" )
                ((MethodCall)this.wrappedObject).call(arguments.ToArray()).ConvertFromNet(result);
            else
                type.InvokeMember(methodName, BindingFlags.Default, null, this.wrappedObject, arguments.ToArray()).ConvertFromNet(result);

            return true;
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