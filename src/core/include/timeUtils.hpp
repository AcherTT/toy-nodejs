#include <ev.h>
#include <iostream>
#include "v8.h"
#include <map>

namespace InternalModule
{
    class TimeUtils
    {
    public:
        // 用于保存定时器的指针
        static std::map<uint64_t, ev_timer *> internalPtrMap;
        static std::map<uint64_t, ev_timer *> timeoutPtrMap;

    public:
        static void setTimeoutCallback(EV_P_ ev_timer *watcher, int revents);
        static void setTimeout(const v8::FunctionCallbackInfo<v8::Value> &args);
        static void clearTimeout(const v8::FunctionCallbackInfo<v8::Value> &args);

        static void setIntervalCallback(EV_P_ ev_timer *watcher, int revents);
        static void setInterval(const v8::FunctionCallbackInfo<v8::Value> &args);
        static void clearInterval(const v8::FunctionCallbackInfo<v8::Value> &args);
    };
};
