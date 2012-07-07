#include <node.h>
#include "includes/cef_sync_handler.h"
#include "includes/cef_handler.h"
#include "includes/util.h"

namespace appjs {

using namespace v8;


bool AppjsSyncHandler::Execute(const CefString& name,
                               CefRefPtr<CefV8Value> object,
                               const CefV8ValueList& arguments,
                               CefRefPtr<CefV8Value>& retval,
                               CefString& exception) {
  REQUIRE_UI_THREAD();
  Local<Value> argv[] = { CefStringToV8(args[0]->GetStringValue()) };
  Handle<Object> handle = g_handler->GetV8WindowHandle(browser_);
  Local<Function> handler = Local<Function>::Cast(handle->GetValue(String::NewSymbol("receiveSync")));
  retval = V8StringToCef(handler->Call(Context::GetCurrent()->Global(), 1, argv));
  return true;
}


}
