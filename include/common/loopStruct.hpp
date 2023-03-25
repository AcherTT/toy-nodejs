#pragma once
#include <iostream>
#include <v8.h>

class LoopData
{
public:
    uint64_t id;
    v8::Persistent<v8::Function> *function;
    LoopData(uint64_t id, v8::Persistent<v8::Function> *func) : id(id), function(func) {}
    ~LoopData() {}
};