#include "utils.h"

vector<string> splitString(string s, char delim)
{
	DSTAT("splitting string");
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
	DSTAT("String Split");
	return ret;
}

bool startsWith(string src, string t)
{
	if(src.length() >= t.length())
	{
		for(int i = 0; i < t.length(); i++)
		{
			if(t[i] != src[i])
				return false;
		}
		return true;
	}
	return false;
}


