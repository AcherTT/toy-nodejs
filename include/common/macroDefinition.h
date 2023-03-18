#pragma once

// 定义一个宏，用于将一个字符串转换为一个v8::String
#define TO_STRING(isolate, str) v8::String::NewFromUtf8(isolate, str, v8::NewStringType::kNormal).ToLocalChecked()
