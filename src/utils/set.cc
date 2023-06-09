#include "v8.h"
#include <string>
#include "utils.hpp"
#include "macroDefinition.hpp"

using namespace v8;

void Utils::SetModule::setModuleFunction(Isolate *isolate,
                                         Local<ObjectTemplate> &recv,
                                         const std::string name,
                                         FunctionCallback callback)
{
    recv->Set(TO_STRING(isolate, name.c_str()),
              FunctionTemplate::New(isolate, callback));
}

static void setModuleFunction(Isolate *isolate,
                              Local<Object> &recv,
                              const std::string name,
                              FunctionCallback callback)
{
    const Local<Context> context = isolate->GetCurrentContext();
    recv->Set(context, TO_STRING(isolate, name.c_str()),
              FunctionTemplate::New(isolate, callback));
}

// 设置对象的属性，属性为非函数
void Utils::SetModule::setObjectValue(Isolate *isolate,
                                      Local<Object> &recv,
                                      const std::string name,
                                      Local<ObjectTemplate> value)
{
    const Local<Context> context = isolate->GetCurrentContext();
    recv->Set(context, TO_STRING(isolate, name.c_str()),
              value->NewInstance(context).ToLocalChecked())
        .FromJust();
}

void Utils::SetModule::setObjectValue(Isolate *isolate,
                                      Local<Object> &recv,
                                      const std::string name,
                                      Local<Object> value)
{
    const Local<Context> context = isolate->GetCurrentContext();
    recv->Set(context, TO_STRING(isolate, name.c_str()), value)
        .FromJust();
}