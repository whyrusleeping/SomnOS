#ifndef SOMN_UTILS_H
#define SOMN_UTILS_H

#include <vector>
#include <string>
#include <iostream>

#ifdef DEBUG
	#define DSTAT(VAR) cout << VAR  << "\n";
#else
	#define DSTAT(VAR) 
#endif

using std::cout;
using std::vector;
using std::string;

vector<string> splitString(string s, char delim);
bool startsWith(string src, string t);

#endif
