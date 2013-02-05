#include "utils.h"

//Splits a string into its component substrings by the given delimeter
vector<string> splitString(string s, char delim)
{
	vector<string> ret;
	string temp = "";
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] != delim)
			temp += s[i];
		else if(temp != "")
		{
			ret.push_back(temp);
			temp = "";
		}
	}
	if(temp != "")
		ret.push_back(temp);
	return ret;
}

//returns true if the first t.length() characters of src equal t
bool startsWith(string src, string t)
{
	if(src.length() < t.length())
		return false;
	for(int i = 0; i < t.length(); i++)
	{
		if(t[i] != src[i])
			return false;
	}
	return true;
}

bool isEmptyOrWhitespace(string s)
{
	if(s == "")
		return true;
	bool ws = true;
	for(int i = 0; i < s.length(); i++)
		ws &= (s[i] == ' ' || s[i] == '\t');
	return ws;
}

void inline stripQuotes(string &s)
{
	s = s.substr(1, s.length() - 2);
}
