#include "../utils/utils.hpp"
#include "macroDefinition.hpp"
#include "include/init.hpp"
#include "include/console.hpp"
#include "include/timeUtils.hpp"
#include "include/buffer.hpp"
#include "include/commonjs.hpp"
#include "include/process.hpp"
#include "include/eventEmitter.hpp"

using namespace v8;
using namespace Utils;
using namespace ToyNode;
using namespace InternalModule;

void initConsole(COMMON_INIT_ARGS)
{
    Local<ObjectTemplate> console = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, console, "log", Console::log);
    SetModule::setObjectValue(isolate, InternalModuleObject, "console", console);
}

void initTimeUtils(COMMON_INIT_ARGS)
{
    Local<ObjectTemplate> timeUtils = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, timeUtils, "setTimeout", TimeUtils::setTimeout);
    SetModule::setModuleFunction(isolate, timeUtils, "setInterval", TimeUtils::setInterval);
    SetModule::setModuleFunction(isolate, timeUtils, "clearTimeout", TimeUtils::clearTimeout);
    SetModule::setModuleFunction(isolate, timeUtils, "clearInterval", TimeUtils::clearInterval);

    SetModule::setObjectValue(isolate, InternalModuleObject, "timeUtils", timeUtils);
}

void initBuffer(COMMON_INIT_ARGS)
{
    Local<ObjectTemplate> buffer = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, buffer, "from", Buffer::from);
    SetModule::setModuleFunction(isolate, buffer, "clean", Buffer::clean);

    SetModule::setObjectValue(isolate, InternalModuleObject, "Buffer", buffer);
}

void initCommonJs(COMMON_INIT_ARGS)
{
    Local<ObjectTemplate> commonJs = ObjectTemplate::New(isolate);
    SetModule::setModuleFunction(isolate, commonJs, "compare", CommonJSModule::compare);

    SetModule::setObjectValue(isolate, InternalModuleObject, "CommonJSModule", commonJs);
}

void initProcess(int argc, char *argv[], COMMON_INIT_ARGS)
{
    Process process(argc, argv);
    Local<Object> processInstance = process.init(isolate, InternalModuleObject);
    SetModule::setObjectValue(isolate, InternalModuleObject, "process", processInstance);
}

void initEventEmitter(COMMON_INIT_ARGS)
{
    Local<FunctionTemplate> EventEmitterObj =
        FunctionTemplate::New(isolate, EventEmitter::CreateObject);
    EventEmitterObj->SetClassName(TO_STRING(isolate, "EventEmitter"));
    EventEmitterObj->InstanceTemplate()->SetInternalFieldCount(13); // TODO 13 is a hard code
    // EventEmitterObj->PrototypeTemplate()->Set(TO_STRING(isolate, "on"), FunctionTemplate::New(isolate, EventEmitter::on));
}

void MyNode::init(int argc, char *argv[], COMMON_INIT_ARGS)
{
    initConsole(isolate, InternalModuleObject);
    initTimeUtils(isolate, InternalModuleObject);
    initBuffer(isolate, InternalModuleObject);
    initCommonJs(isolate, InternalModuleObject);
    initProcess(argc, argv, isolate, InternalModuleObject);
}
