#include "v8.h"
#include "macroDefinition.h"
#include "include/commonjs.h"
#include <string>
#include "../utils/utils.h"

namespace InternalModule
{
    using namespace v8;
    using namespace std;

    // TODO: 核心函数，未实现模块寻址机制，只对指定路径做了搜索
    void CommonJSModule::require(V8_FUNCTION_ARGS)
    {
        Isolate *isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();
        Local<String> path = args[0]->ToString(context).ToLocalChecked();
        String::Utf8Value str(isolate, path);
        string data = *str;
        const string content = Utils::File::readFileToString(data);
        ScriptCompiler::Source source(TO_STRING(isolate, content.c_str()));
        Local<String> params[] = {
            TO_STRING(isolate, "require"),
            TO_STRING(isolate, "module"),
            TO_STRING(isolate, "exports"),
        };
        MaybeLocal<Function> fun =
            ScriptCompiler::CompileFunctionInContext(context, &source, 3, params, 0, nullptr);
        if (fun.IsEmpty())
            args.GetReturnValue().Set(Undefined(isolate));
        else
            args.GetReturnValue().Set(fun.ToLocalChecked());
    };
}