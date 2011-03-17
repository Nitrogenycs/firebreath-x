%module(directors="1") FireBreath

%{
	#include "FBXJSAPI.h"
	#include "FBXVariant.h"
%}

%include "std_string.i"
%include "std_wstring.i"
%include "std_vector.i"

%template(StringVector) std::vector<std::string>;

%ignore fbxvariant::set(const FB::variant& Var);
%ignore fbxvariant::var;
%ignore fbxvariant::get_variant;

%include "FBXVariant.h"
%template(VariantVector) std::vector<fbxvariant>;

%ignore FBXJSAPI::FBXJSAPI(FB::JSAPIPtr wrapped);
%feature("director") FBXJSAPI;
%include "FBXJSAPI.h"