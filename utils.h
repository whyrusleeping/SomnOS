#ifndef SOMN_UTILS_H
#define SOMN_UTILS_H

#include "instrDefs.h"
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::vector;
using std::string;

vector<string> splitString(string s, char delim);
bool startsWith(string src, string t);

#endif
