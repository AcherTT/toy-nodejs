#include <v8.h>
#include <cstring>
#include <iostream>
#include "macroDefinition.hpp"
#include "include/buffer.hpp"

using namespace v8;

namespace InternalModule
{

    Buffer::Buffer(const char *data, size_t size) : data_(new char[size]), size_(size)
    {
        std::memcpy(data_, data, size);
    }
    Buffer::~Buffer() { delete[] data_; }

    // TODO 未实现编码转换
    void Buffer::toString(Buffer *buffer, const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();
        Local<String> str = String::NewFromUtf8(
                                isolate,
                                buffer->data(),
                                NewStringType::kNormal,
                                buffer->size())
                                .ToLocalChecked();
        args.GetReturnValue().Set(str);
    }

    void Buffer::from(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();

        if (args.Length() < 1 || !args[0]->IsString())
        {
            isolate->ThrowException(Exception::TypeError(TO_STRING(isolate, "参数错误")));
            return;
        }

        String::Utf8Value str(isolate, args[0]);
        std::string data = *str;
        Buffer *buffer = new Buffer(data.c_str(), data.size());

        Local<ObjectTemplate> buffer_template = ObjectTemplate::New(isolate);
        buffer_template->SetInternalFieldCount(2);
        buffer_template->SetAccessor(TO_STRING(isolate, "length"),
                                     [](Local<String> property, const PropertyCallbackInfo<Value> &info)
                                     {
                                         Isolate *isolate = info.GetIsolate();
                                         Buffer *buffer = static_cast<Buffer *>(info.Holder()->GetAlignedPointerFromInternalField(0));
                                         info.GetReturnValue().Set(static_cast<int32_t>(buffer->size()));
                                     });

        // TODO 可以封装下面函数，太麻烦了。。。
        buffer_template->Set(TO_STRING(isolate, "toString"),
                             FunctionTemplate::New(isolate,
                                                   [](const FunctionCallbackInfo<Value> &args)
                                                   {
                                                       Buffer *buffer = static_cast<Buffer *>(args.Holder()->GetAlignedPointerFromInternalField(0));
                                                       Buffer::toString(buffer, args);
                                                   }));

        buffer_template->Set(TO_STRING(isolate, "clean"),
                             FunctionTemplate::New(isolate,
                                                   [](const FunctionCallbackInfo<Value> &args)
                                                   {
                                                       Buffer::clean(args);
                                                   }));

        Local<Object> buffer_object = buffer_template->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();

        buffer_object->SetAlignedPointerInInternalField(0, buffer);
        buffer_object->SetAlignedPointerInInternalField(1, buffer);

        args.GetReturnValue().Set(buffer_object);
    }

    void Buffer::clean(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();

        if (args.Length() < 1 || !args[0]->IsObject())
        {
            isolate->ThrowException(Exception::TypeError(TO_STRING(isolate, "Invalid arguments")));
            return;
        }

        Local<Object> buffer_object = args[0].As<Object>();
        void *buffer_ptr = buffer_object->GetAlignedPointerFromInternalField(0);
        Buffer *buffer = static_cast<Buffer *>(buffer_ptr);
        delete buffer;
    }
}
