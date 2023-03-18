#include "include/init.h"
#include "include/console.h"
#include "include/timeUtils.h"
#include "../utils/utils.h"

using namespace v8;
using namespace Utils;
using namespace ToyNode;
using namespace InternalModule;

void MyNode::init(v8::Isolate *isolate, Local<Object> &global)
{
    MyNode::initConsole(isolate, global);
    MyNode::initTimeUtils(isolate, global);
}

void MyNode::initConsole(v8::Isolate *isolate, Local<Object> &global)
{
    Local<ObjectTemplate> console = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, console, "log", Console::log);
    SetModule::setObjectValue(isolate, global, "console", console);
}

void MyNode::initTimeUtils(v8::Isolate *isolate, Local<Object> &global)
{
    Local<ObjectTemplate> timeUtils = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, timeUtils, "setTimeout", TimeUtils::setTimeout);
    SetModule::setModuleFunction(isolate, timeUtils, "setInterval", TimeUtils::setInterval);
    SetModule::setModuleFunction(isolate, timeUtils, "clearTimeout", TimeUtils::clearTimeout);
    SetModule::setModuleFunction(isolate, timeUtils, "clearInterval", TimeUtils::clearInterval);

    SetModule::setObjectValue(isolate, global, "timeUtils", timeUtils);
}