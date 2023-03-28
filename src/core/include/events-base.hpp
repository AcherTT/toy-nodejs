#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>
#include <any>

class EventEmitterBase
{
public:
    virtual void on(std::string eventName, std::function<void(std::vector<std::any>)> listener) = 0;
    virtual void emit(std::string eventName, std::vector<std::any> args) = 0;
    virtual void listeners(std::string eventName) = 0;
    virtual void listenerCount(std::string eventName) = 0;
    virtual void removeListener(std::string eventName, std::function<void(std::vector<std::any>)> listener) = 0;
    virtual void removeAllListeners(std::string eventName) = 0;
    virtual void once(std::string eventName, std::function<void(std::vector<std::any>)> listener) = 0;
    virtual void prependListener(std::string eventName, std::function<void(std::vector<std::any>)> listener) = 0;
    virtual void prependOnceListener(std::string eventName, std::function<void(std::vector<std::any>)> listener) = 0;
    virtual void eventNames() = 0;
    virtual void rawListeners(std::string eventName) = 0;
    virtual void off(std::string eventName, std::function<void(std::vector<std::any>)> listener) = 0;
    virtual void setMaxListeners(u_int32_t maxNumber) = 0;
};
