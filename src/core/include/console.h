#pragma once
#include "v8.h"

namespace InternalModule
{
    class Console
    {
    public:
        static void log(const v8::FunctionCallbackInfo<v8::Value> &args);
    };
}
