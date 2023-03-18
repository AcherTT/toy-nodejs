#pragma once
#include "v8.h"
#include <string>

namespace InternalModule
{
    class Console
    {
    private:
        static void _log(v8::Isolate *isolate, v8::Local<v8::String> &str);
        static void _log(std::string str);
        static void _log(bool value);

    public:
        static void log(const v8::FunctionCallbackInfo<v8::Value> &args);
    };
}
