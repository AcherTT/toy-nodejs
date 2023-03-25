#include "include/process.hpp"
#include "v8.h"
#include "macroDefinition.hpp"
#include "../utils/utils.hpp"

namespace InternalModule
{
    Local<Object> Process::init(COMMON_INIT_ARGS)
    {
        const std::string pwd = Utils::File::getPwd();
        Local<v8::Context> context = isolate->GetCurrentContext();
        Local<ObjectTemplate> process = ObjectTemplate::New(isolate);
        Local<Object> processInstance = process->NewInstance(context).ToLocalChecked();
        Local<Array> array = Array::New(isolate, argc);

        for (vector<string>::iterator it = argv.begin(); it != argv.end(); it++)
            array->Set(context, it - argv.begin(), TO_STRING(isolate, it->c_str()));

        processInstance->Set(context, TO_STRING(isolate, "argv"), array);
        processInstance->Set(context, TO_STRING(isolate, "argc"), Integer::New(isolate, argc));
        processInstance->Set(context, TO_STRING(isolate, "dirname"), TO_STRING(isolate, pwd.c_str()));
        processInstance->Set(context, TO_STRING(isolate, "pwd"), TO_STRING(isolate, pwd.c_str()));
        return processInstance;
    }
}