#pragma once
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

namespace Strings
{
	string Join(const vector<string>& elements, const char* const separator);
	vector<string> Split(const char splitter, const string &input);
};

