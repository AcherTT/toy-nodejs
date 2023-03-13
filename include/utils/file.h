#ifndef FILE_H
#define FILE_H

#include <string>

namespace Utils
{
    namespace File
    {
        // 读取文件
        std::string readFileToString(const std::string &filename);
    }
}

#endif