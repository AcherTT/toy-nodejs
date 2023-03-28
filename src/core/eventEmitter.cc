#include "include/eventEmitter.hpp"
#include "v8.h"
#include "macroDefinition.hpp"

// js 中的 EventEmitter
namespace InternalModule
{
    using namespace v8;

    void EventEmitter::on(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<String> eventName = args[0]->ToString(context).ToLocalChecked();
        Local<Function> listener = Local<Function>::Cast(args[0]);
        const auto persistentListener = Persistent<Function>(isolate, listener);
        auto it = listenersMap.find(eventName);
        if (it == listenersMap.end())
        {
            std::vector<Persistent<Function>> listeners;
            listeners.push_back(persistentListener);
            listenersMap.insert(std::pair<Local<String>, std::vector<Persistent<Function>>>(eventName, listeners));
        }
        else
        {
            it->second.push_back(persistentListener);
        }
    };

    void EventEmitter::emit(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<String> eventName = args[0]->ToString(context).ToLocalChecked();
        std::vector<Local<Value>> argsVector;
        for (int i = 1; i < args.Length(); i++)
        {
            argsVector.push_back(args[i]);
        }
        auto it = listenersMap.find(eventName);
        if (it != listenersMap.end())
        {
            for (auto &listener : it->second)
                listener.Get(isolate)->Call(context, context->Global(), argsVector.size(), argsVector.data());
        }
    };

    void EventEmitter::listeners(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<String> eventName = args[0]->ToString(context).ToLocalChecked();
        auto it = listenersMap.find(eventName);
        if (it != listenersMap.end())
        {
            Local<Array> listeners = Array::New(isolate, it->second.size());
            for (int i = 0; i < it->second.size(); i++)
            {
                listeners->Set(context, i, it->second[i].Get(isolate));
            }
            args.GetReturnValue().Set(listeners);
        }
    };

    void EventEmitter::listenerCount(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<String> eventName = args[0]->ToString(context).ToLocalChecked();
        auto it = listenersMap.find(eventName);
        if (it != listenersMap.end())
        {
            auto count = v8::Integer::New(isolate, it->second.size());
            args.GetReturnValue().Set(count);
        }
    };

    void EventEmitter::removeListener(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<String> eventName = args[0]->ToString(context).ToLocalChecked();
        Local<Function> listener = Local<Function>::Cast(args[0]);
        auto it = listenersMap.find(eventName);
        if (it != listenersMap.end())
        {
            for (int i = 0; i < it->second.size(); i++)
            {
                if (it->second[i].Get(isolate) == listener)
                {
                    it->second.erase(it->second.begin() + i);
                    break;
                }
            }
        }
    };

    void EventEmitter::removeAllListeners(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<String> eventName = args[0]->ToString(context).ToLocalChecked();
        auto it = listenersMap.find(eventName);
        if (it != listenersMap.end())
        {
            it->second.clear();
        }
    };

    void EventEmitter::once(V8_FUNCTION_ARGS){};

    void EventEmitter::prependListener(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<String> eventName = args[0]->ToString(context).ToLocalChecked();
        Local<Function> listener = Local<Function>::Cast(args[0]);
        const auto persistentListener = Persistent<Function>(isolate, listener);
        auto it = listenersMap.find(eventName);
        if (it == listenersMap.end())
        {
            std::vector<Persistent<Function>> listeners;
            listeners.push_back(persistentListener);
            listenersMap.insert(std::pair<Local<String>, std::vector<Persistent<Function>>>(eventName, listeners));
        }
        else
        {
            it->second.insert(it->second.begin(), persistentListener);
        }
    };

    void EventEmitter::prependOnceListener(V8_FUNCTION_ARGS){};

    void EventEmitter::eventNames(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<Array> eventNames = Array::New(isolate, listenersMap.size());
        int i = 0;
        for (auto &it : listenersMap)
        {
            eventNames->Set(context, i, it.first);
            i++;
        }
        args.GetReturnValue().Set(eventNames);
    };

    void EventEmitter::rawListeners(V8_FUNCTION_ARGS)
    {
        V8_ISOLATE_CONTEXT
        Local<String> eventName = args[0]->ToString(context).ToLocalChecked();
        auto it = listenersMap.find(eventName);
        if (it != listenersMap.end())
        {
            Local<Array> listeners = Array::New(isolate, it->second.size());
            for (int i = 0; i < it->second.size(); i++)
            {
                listeners->Set(context, i, it->second[i].Get(isolate));
            }
            args.GetReturnValue().Set(listeners);
        }
    };

    void EventEmitter::off(V8_FUNCTION_ARGS)
    {
        removeListener(args);
    };

    void EventEmitter::setMaxListeners(V8_FUNCTION_ARGS){};
}