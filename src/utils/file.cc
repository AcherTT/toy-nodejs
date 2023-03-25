#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "utils.hpp"

using namespace std;
string Utils::File::readFileToString(const string &filename)
{
  ifstream file(filename);
  stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

string Utils::File::getPwd()
{
  char *cwd = (char *)malloc(sizeof(char) * PATH_MAX);
  if (cwd == NULL)
    throw runtime_error("malloc() error");

  if (getcwd(cwd, PATH_MAX) != NULL)
  {
    char *resolved_path = realpath(cwd, NULL);
    if (resolved_path == NULL)
      throw runtime_error("realpath() error");
    delete cwd;
    return string(resolved_path);
  }
  else
    throw runtime_error("getcwd() error");
}
