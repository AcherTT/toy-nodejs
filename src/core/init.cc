#include "include/init.h"
#include "include/console.h"
#include "../utils/utils.h"

using namespace v8;
using namespace Utils;
using namespace ToyNode;
using namespace InternalModule;

void MyNode::init(v8::Isolate *isolate, Local<Object> &global)
{
    MyNode::initConsole(isolate, global);
}

void MyNode::initConsole(v8::Isolate *isolate, Local<Object> &global)
{
    Local<ObjectTemplate> console = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, console, "log", Console::log);
    SetModule::setObjectValue(isolate, global, "console", console);
}