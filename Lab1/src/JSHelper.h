
#ifndef JSHELPER_H
#include <AppCore/AppCore.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <functional>

#define JSHELPER_H
namespace js_interop
{
	struct JSHelper
	{
		static JSValueRef CallJSFunction(
			JSContextRef ctx,
			const char* JSfuncName,
			std::function<void(JSObjectRef&, size_t&)> buildArgs,
			JSValueRef* exception);
	};

}

#endif

