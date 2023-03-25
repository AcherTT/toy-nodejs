#include "include/process.hpp"
#include "v8.h"
#include "macroDefinition.hpp"

namespace InternalModule
{
    Local<Object> Process::init(COMMON_INIT_ARGS)
    {
        Local<v8::Context> context = isolate->GetCurrentContext();
        Local<ObjectTemplate> process = ObjectTemplate::New(isolate);
        Local<Object> processInstance = process->NewInstance(context).ToLocalChecked();
        Local<Array> array = Array::New(isolate, argc);

        for (vector<string>::iterator it = argv.begin(); it != argv.end(); it++)
            array->Set(context, it - argv.begin(), TO_STRING(isolate, it->c_str()));

        processInstance->Set(context, TO_STRING(isolate, "argv"), array);
        processInstance->Set(context, TO_STRING(isolate, "argc"), Integer::New(isolate, argc));
        return processInstance;
    }
}