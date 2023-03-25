#include "include/console.hpp"
#include <iostream>

using namespace v8;

// TODO: Add more types
namespace InternalModule
{
    void Console::_log(Isolate *isolate, Local<String> &str)
    {
        String::Utf8Value utf8(isolate, str);
        std::cout << *utf8 << std::endl;
    };

    void Console::_log(std::string str)
    {
        std::cout << str << std::endl;
    };

    void Console::_log(bool value)
    {
        std::cout << value << std::endl;
    };

    void Console::log(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        HandleScope scope(isolate);
        Local<Context> context = isolate->GetCurrentContext();
        for (int i = 0; i < args.Length(); i++)
        {
            if (args[i]->IsNumber())
            {
                std::cout << args[i]->NumberValue(context).FromJust() << std::endl;
                continue;
            }
            if (args[i]->IsString())
            {
                Local<String> str = args[i]->ToString(context).ToLocalChecked();
                Console::_log(isolate, str);
                continue;
            }
            if (args[i]->IsBoolean())
            {
                Console::_log(args[i]->BooleanValue(isolate));
                continue;
            }
            if (args[i]->IsObject())
            {
                Local<String> str = JSON::Stringify(context, args[i]->ToObject(context).ToLocalChecked()).ToLocalChecked();
                Console::_log(isolate, str);
                continue;
            }

            // TODO: 此处判断应该有bug
            if (args[i]->IsFunction())
            {
                Local<Function> function = Local<Function>::Cast(args[i]);
                Local<String> str = function->FunctionProtoToString(context).ToLocalChecked();
                Console::_log(isolate, str);
                continue;
            }
        }
    }
}
