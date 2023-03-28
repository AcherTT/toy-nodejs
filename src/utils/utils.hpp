#pragma once
#include <string>
#include "v8.h"

namespace Utils
{
    class File
    {
    public:
        static std::string readFileToString(const std::string &filepath);
        static std::string getPwd();
    };

    class SetModule
    {
    public:
        static void setModuleFunction(v8::Isolate *isolate,
                                      v8::Local<v8::ObjectTemplate> &recv,
                                      const std::string name,
                                      v8::FunctionCallback callback);
        static void setModuleFunction(v8::Isolate *isolate,
                                      v8::Local<v8::Object> &recv,
                                      const std::string name,
                                      v8::FunctionCallback callback);

        static void setObjectValue(v8::Isolate *isolate,
                                   v8::Local<v8::Object> &recv,
                                   const std::string name,
                                   v8::Local<v8::ObjectTemplate> value);
        static void setObjectValue(v8::Isolate *isolate,
                                   v8::Local<v8::Object> &recv,
                                   const std::string name,
                                   v8::Local<v8::Object> value);
    };

}
