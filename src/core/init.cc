#include "../utils/utils.h"
#include "include/init.h"
#include "include/console.h"
#include "include/timeUtils.h"
#include "include/buffer.h"
#include "include/commonjs.h"
#include "include/process.h"
#include "macroDefinition.h"

using namespace v8;
using namespace Utils;
using namespace ToyNode;
using namespace InternalModule;

void MyNode::init(int argc, char *argv[], COMMON_INIT_ARGS)
{
    MyNode::initConsole(isolate, InternalModuleObject);
    MyNode::initTimeUtils(isolate, InternalModuleObject);
    MyNode::initBuffer(isolate, InternalModuleObject);
    MyNode::initCommonJs(isolate, InternalModuleObject);
    MyNode::initProcess(argc, argv, isolate, InternalModuleObject);
}

void MyNode::initConsole(COMMON_INIT_ARGS)
{
    Local<ObjectTemplate> console = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, console, "log", Console::log);
    SetModule::setObjectValue(isolate, InternalModuleObject, "console", console);
}

void MyNode::initTimeUtils(COMMON_INIT_ARGS)
{
    Local<ObjectTemplate> timeUtils = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, timeUtils, "setTimeout", TimeUtils::setTimeout);
    SetModule::setModuleFunction(isolate, timeUtils, "setInterval", TimeUtils::setInterval);
    SetModule::setModuleFunction(isolate, timeUtils, "clearTimeout", TimeUtils::clearTimeout);
    SetModule::setModuleFunction(isolate, timeUtils, "clearInterval", TimeUtils::clearInterval);

    SetModule::setObjectValue(isolate, InternalModuleObject, "timeUtils", timeUtils);
}

void MyNode::initBuffer(COMMON_INIT_ARGS)
{
    Local<ObjectTemplate> buffer = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, buffer, "from", Buffer::from);
    SetModule::setModuleFunction(isolate, buffer, "clean", Buffer::clean);

    SetModule::setObjectValue(isolate, InternalModuleObject, "Buffer", buffer);
}

void MyNode::initCommonJs(COMMON_INIT_ARGS)
{
    Local<ObjectTemplate> commonJs = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, commonJs, "require", CommonJSModule::require);

    SetModule::setObjectValue(isolate, InternalModuleObject, "CommonJSModule", commonJs);
}

void MyNode::initProcess(int argc, char *argv[], COMMON_INIT_ARGS)
{
    Process process(argc, argv);
    Local<Object> processInstance = process.init(isolate, InternalModuleObject);
    SetModule::setObjectValue(isolate, InternalModuleObject, "process", processInstance);
}