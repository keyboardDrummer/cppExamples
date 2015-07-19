#include "stdafx.h"
#include "Strings.h"

namespace Strings
{
	string Join(const vector<string>& elements, const char* const separator)
	{
		switch (elements.size())
		{
		case 0:
			return "";
		case 1:
			return elements[0];
		default:
			ostringstream os;
			copy(elements.begin(), elements.end() - 1, ostream_iterator<string>(os, separator));
			os << *elements.rbegin();
			return os.str();
		}
	}

	vector<string> Split(const char splitter, const string &input)
	{
		string::const_iterator current = input.begin();
		string::const_iterator wordStart = input.begin();
		vector<string> result;
		while (current < input.end())
		{
			if (*current == splitter)
			{
				result.insert(result.end(), string(wordStart, current));
				wordStart = ++current;
			}
			else
			{
				current++;
			}
		}
		result.insert(result.end(), string(wordStart, current));
		return result;
	}
}