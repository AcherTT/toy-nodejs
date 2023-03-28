#pragma once

#define TO_STRING(isolate, str) v8::String::NewFromUtf8(isolate, str, v8::NewStringType::kNormal).ToLocalChecked()

#define V8_FUNCTION_ARGS const v8::FunctionCallbackInfo<v8::Value> &args

#define COMMON_INIT_ARGS v8::Isolate *isolate, v8::Local<v8::Object> &InternalModuleObject

#define V8_ISOLATE_CONTEXT                    \
    v8::Isolate *isolate = args.GetIsolate(); \
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
