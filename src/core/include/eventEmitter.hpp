#pragma once
#include "macroDefinition.hpp"
#include "v8.h"
#include <map>
#include <vector>

namespace InternalModule
{
    class EventEmitter
    {
    private:
        std::map<v8::Local<v8::String>, std::vector<v8::Persistent<v8::Function>>> listenersMap;

    public:
        void on(V8_FUNCTION_ARGS);
        void emit(V8_FUNCTION_ARGS);
        void listeners(V8_FUNCTION_ARGS);
        void listenerCount(V8_FUNCTION_ARGS);
        void removeListener(V8_FUNCTION_ARGS);
        void removeAllListeners(V8_FUNCTION_ARGS);
        void once(V8_FUNCTION_ARGS);
        void prependListener(V8_FUNCTION_ARGS);
        void prependOnceListener(V8_FUNCTION_ARGS);
        void eventNames(V8_FUNCTION_ARGS);
        void rawListeners(V8_FUNCTION_ARGS);
        void off(V8_FUNCTION_ARGS);
        void setMaxListeners(V8_FUNCTION_ARGS);

        static void CreateObject(const v8::FunctionCallbackInfo<v8::Value> &args)
        {
            v8::Isolate *isolate = args.GetIsolate();
            EventEmitter *event = new EventEmitter();
            v8::Local<v8::Object> instance = args.This();
            instance->SetInternalField(0, v8::External::New(isolate, event));
        };
    };
}