#pragma once

#include <string>
#include <vector>
#include <istream>
#include <memory>

using namespace std;

template<class Problem, class Solution>
class IAlgorithm
{
public:

	virtual Problem Parse(istream& stream) = 0;

	virtual Solution Solve(const Problem& input) = 0;

	virtual string Print(const Solution& output) = 0;

	string Run(istream& stream) {
		auto problem = Parse(stream);
		auto solution = Solve(problem);
		return Print(solution);
	}
};

