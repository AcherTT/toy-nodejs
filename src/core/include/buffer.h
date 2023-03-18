#pragma once
#include "v8.h"

using namespace v8;

namespace InternalModule
{
    class Buffer
    {
    private:
        char *data_;
        size_t size_;

    public:
        Buffer(const char *data, size_t size);
        ~Buffer();

        const char *data() const { return data_; }
        size_t size() const { return size_; }

        static void toString(Buffer *buffer, const FunctionCallbackInfo<Value> &args);
        static void from(const FunctionCallbackInfo<Value> &args);
        static void clean(const FunctionCallbackInfo<Value> &args);
    };
}