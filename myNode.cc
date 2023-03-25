#include <string>
#include <iostream>
#include "libplatform/libplatform.h"
#include "v8.h"
#include "src/utils/utils.hpp"
#include "src/core/include/console.hpp"
#include "src/core/include/init.hpp"
#include <ev.h>
#include "macroDefinition.hpp"
#include <filesystem>

using namespace v8;

int main(int argc, char *argv[])
{
    // 缓冲区设置-不缓冲
    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);

    // V8::InitializeICUDefaultLocation(argv[0]); -- 直接使用系统的icu库
    V8::InitializeExternalStartupData(argv[0]);

    std::unique_ptr<Platform> platform = platform::NewDefaultPlatform();
    V8::InitializePlatform(platform.get());
    V8::Initialize();

    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
    Isolate *isolate = Isolate::New(create_params);

    {
        Isolate::Scope isolate_scope(isolate);
        HandleScope handle_scope(isolate);

        Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
        Local<Context> context = Context::New(isolate, nullptr, global);
        Context::Scope context_scope(context);

        // 初始化内部模块
        Local<Object> InternalModuleObject = Object::New(isolate);
        ToyNode::MyNode::init(argc, argv, isolate, InternalModuleObject);

        // global
        Local<Object> globalInstance = context->Global();
        globalInstance->Set(context,
                            TO_STRING(isolate, "InternalModuleObject"),
                            InternalModuleObject)
            .Check();
        globalInstance->Set(context, TO_STRING(isolate, "global"), globalInstance).Check();

        // 运行js脚本
        {
            const std::string sourceStr = Utils::File::readFileToString("../toy-node.js");
            Local<String> source = String::NewFromUtf8(isolate, sourceStr.c_str(),
                                                       NewStringType::kNormal,
                                                       sourceStr.size())
                                       .ToLocalChecked();

            Local<Script> script = Script::Compile(context, source).ToLocalChecked();
            Local<Value> result = script->Run(context).ToLocalChecked();
        }
        ev_run(EV_DEFAULT_ 0); // 启动事件循环
    }

    // 销毁
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
    return 0;
}