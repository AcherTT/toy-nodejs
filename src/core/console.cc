#include "include/console.h"
#include <iostream>

void InternalModule::Console::log(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();
    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::String> str = args[0]->ToString(context).ToLocalChecked();
    v8::String::Utf8Value utf8(isolate, str);
    std::cout << *utf8 << std::endl;
}