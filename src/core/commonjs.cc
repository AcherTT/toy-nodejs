#include "v8.h"
#include "macroDefinition.h"
#include "include/commonjs.h"
#include <string>
#include "../utils/utils.h"
#include <iostream>

namespace InternalModule
{
    using namespace v8;
    using namespace std;

    // TODO: 核心函数，未实现模块寻址机制，只对指定路径做了搜索
    void CommonJSModule::compare(V8_FUNCTION_ARGS)
    {
        Isolate *isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();
        Local<String> path = args[0]->ToString(context).ToLocalChecked();
        String::Utf8Value str(isolate, path);
        string data = *str;
        const string content = Utils::File::readFileToString(data);
        Local<String> sourceString = TO_STRING(isolate, content.c_str());
        ScriptOrigin origin(isolate, sourceString);
        ScriptCompiler::Source source(sourceString, origin);
        Local<String> params[] = {
            TO_STRING(isolate, "require"),
            TO_STRING(isolate, "module"),
            TO_STRING(isolate, "exports"),
        };
        MaybeLocal<Function> maybeFun =
            ScriptCompiler::CompileFunctionInContext(context, &source, 3, params, 0, nullptr);
        if (maybeFun.IsEmpty())
        {
            args.GetReturnValue().Set(Undefined(isolate));
            return;
        }
        Local<Function> function = maybeFun.ToLocalChecked();
        auto aa = function->ToString(context).ToLocalChecked();
        String::Utf8Value str2(isolate, aa);
        cout << *str2 << endl;
        args.GetReturnValue().Set(function);
    };
}