#include <ev.h>
#include <iostream>
#include <v8.h>
#include "include/timeUtils.h"

using namespace v8;

namespace InternalModule
{
    std::map<uint32_t, ev_timer *> TimeUtils::internalPtrMap;
    std::map<uint32_t, ev_timer *> TimeUtils::timeoutPtrMap;

    void TimeUtils::setTimeoutCallback(EV_P_ ev_timer *watcher, int revents)
    {
        Isolate *isolate = Isolate::GetCurrent();
        Local<Context> context = isolate->GetCurrentContext();
        HandleScope handle_scope(isolate);
        // 获取参数，即传入的回调函数
        Local<Function> callback =
            Local<Function>::New(isolate, *(reinterpret_cast<Persistent<Function> *>(watcher->data)));
        const MaybeLocal<v8::Value> callResult = callback->Call(context, Null(isolate), 0, nullptr);

        callback.Clear();
        ev_timer_stop(EV_A_ watcher);
    }

    void TimeUtils::setTimeout(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        HandleScope handle_scope(isolate);
        Local<Context> context = isolate->GetCurrentContext();

        // 获取参数
        Local<Function> callback = Local<Function>::Cast(args[0]);
        double timeout = args[1]->NumberValue(context).FromJust();

        // 创建定时器
        ev_timer *watcher = new ev_timer();
        watcher->data = new Persistent<Function>(isolate, callback);
        ev_timer_init(watcher, setTimeoutCallback, timeout / 1000, 0);

        // 保存定时器指针
        const uint32_t id = TimeUtils::timeoutPtrMap.size() + 1;
        TimeUtils::timeoutPtrMap[id] = watcher;

        ev_timer_start(EV_DEFAULT_ watcher);

        Local<Number> jsValue = Number::New(Isolate::GetCurrent(), static_cast<double>(id));
        args.GetReturnValue().Set(jsValue);
    }

    void TimeUtils::clearTimeout(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        HandleScope handle_scope(isolate);
        Local<Context> context = isolate->GetCurrentContext();

        if (args.Length() == 0)
        {
            for (auto it = TimeUtils::timeoutPtrMap.begin(); it != TimeUtils::timeoutPtrMap.end(); it++)
                ev_timer_stop(EV_DEFAULT_ it->second);
            TimeUtils::timeoutPtrMap.clear();
            return;
        }

        uint32_t id = args[0]->NumberValue(context).FromJust();
        ev_timer *watcher = TimeUtils::timeoutPtrMap[id];
        ev_timer_stop(EV_DEFAULT_ watcher);
        TimeUtils::timeoutPtrMap.erase(id);
        delete watcher;
    }

    void TimeUtils::setIntervalCallback(EV_P_ ev_timer *watcher, int revents)
    {
        Isolate *isolate = Isolate::GetCurrent();
        Local<Context> context = isolate->GetCurrentContext();
        HandleScope handle_scope(isolate);
        Local<Function> callback =
            Local<Function>::New(isolate, *(reinterpret_cast<Persistent<Function> *>(watcher->data)));
        const MaybeLocal<v8::Value> callResult = callback->Call(context, Null(isolate), 0, nullptr);
    }

    void TimeUtils::setInterval(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        HandleScope handle_scope(isolate);
        Local<Context> context = isolate->GetCurrentContext();

        Local<Function> callback = Local<Function>::Cast(args[0]);
        double timeout = args[1]->NumberValue(context).FromJust();

        ev_timer *watcher = new ev_timer();
        watcher->data = new Persistent<Function>(isolate, callback);
        ev_timer_init(watcher, setIntervalCallback, timeout / 1000, timeout / 1000);

        const uint32_t id = TimeUtils::internalPtrMap.size() + 1;
        TimeUtils::internalPtrMap[id] = watcher;

        ev_timer_start(EV_DEFAULT_ watcher);

        Local<Number> jsValue = Number::New(Isolate::GetCurrent(), static_cast<double>(id));
        args.GetReturnValue().Set(jsValue);
    }

    void TimeUtils::clearInterval(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        HandleScope handle_scope(isolate);
        Local<Context> context = isolate->GetCurrentContext();

        if (args.Length() == 0)
        {
            for (auto it = TimeUtils::internalPtrMap.begin(); it != TimeUtils::internalPtrMap.end(); it++)
                ev_timer_stop(EV_DEFAULT_ it->second);
            TimeUtils::internalPtrMap.clear();
            return;
        }
        uint32_t id = args[0]->NumberValue(context).FromJust();
        ev_timer *watcher = TimeUtils::internalPtrMap[id];
        ev_timer_stop(EV_DEFAULT_ watcher);
        TimeUtils::internalPtrMap.erase(id);
        delete watcher;
    }
}
