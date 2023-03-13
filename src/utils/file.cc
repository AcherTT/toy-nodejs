#include <fstream>
#include <sstream>
#include <string>
#include "../../include/utils/file.h"

std::string Utils::File::readFileToString(const std::string &filename)
{
  std::ifstream file(filename);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}