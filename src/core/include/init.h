#pragma once
#include "v8.h"

using namespace v8;

namespace ToyNode
{
    class MyNode
    {
    public:
        static void init(Isolate *isolate, Local<Object> &global);
        static void initConsole(Isolate *isolate, Local<Object> &global);
        static void initTimeUtils(Isolate *isolate, Local<Object> &global);
    };
}