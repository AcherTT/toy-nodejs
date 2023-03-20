#pragma once
#include "v8.h"
#include "macroDefinition.h"

namespace ToyNode
{

    class MyNode
    {
    public:
        static void init(int argc, char *argv[], COMMON_INIT_ARGS);
        static void initConsole(COMMON_INIT_ARGS);
        static void initTimeUtils(COMMON_INIT_ARGS);
        static void initBuffer(COMMON_INIT_ARGS);
        static void initCommonJs(COMMON_INIT_ARGS);
        static void initProcess(int argc, char *argv[], COMMON_INIT_ARGS);
    };
}