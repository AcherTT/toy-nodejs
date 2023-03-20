#pragma once
#include "v8.h"
#include <string>
#include <vector>
#include "macroDefinition.h"

namespace InternalModule
{
    using namespace std;
    using namespace v8;

    class Process
    {
    private:
        vector<string> argv;
        int argc;

    public:
        Process(int argc, char *argv[]) : argc(argc)
        {
            for (int i = 0; i < argc; i++)
            {
                this->argv.push_back(argv[i]);
            }
        };

        ~Process(){};

        Local<Object> init(COMMON_INIT_ARGS);
    };
}
