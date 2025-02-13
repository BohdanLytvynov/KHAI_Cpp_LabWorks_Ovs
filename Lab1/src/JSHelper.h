
#ifndef JSHELPER_H
#include <AppCore/AppCore.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <functional>

#define JSHELPER_H

struct JSHelper
{
	JSValueRef CallJSFunction(
		ultralight::View* caller,
		const char* JSfuncName,
		std::function<void(JSValueRef*, size_t&)> buildArgs,
		JSValueRef* exception);
};

#endif

