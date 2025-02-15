#include "JSHelper.h"

JSValueRef js_interop::JSHelper::CallJSFunction(
	JSContextRef ctx,
	const char* JSfuncName,
	std::function<void(JSObjectRef&, size_t&)> buildArgs,
	JSValueRef* exception)
{
	JSValueRef result = 0;	
	//Convert the func name represented as a char pointer to JSUTF8String
	JSRetainPtr<JSStringRef> str = adopt(JSStringCreateWithUTF8CString(JSfuncName));
	//Check the JS Script
	JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);
	//Check if func is the JS Object Type
	if (JSValueIsObject(ctx, func))
	{
		//Get JSObjectRef
		JSObjectRef funcObj = JSValueToObject(ctx, func, 0);
		//Check wether funcObj is not nullptr and it is the JS function
		if (funcObj != nullptr && JSObjectIsFunction(ctx, funcObj))
		{
			JSObjectRef args;

			size_t num_args = 0;

			buildArgs(args, num_args);

			result = JSObjectCallAsFunction(ctx, funcObj, 0,
				num_args, &args,
				exception);				
		}
	}

	return result;
}