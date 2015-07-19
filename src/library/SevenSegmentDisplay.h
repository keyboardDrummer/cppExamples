#pragma once
#include <vector>
#include "IAlgorithm.h"
#include <set>

using DisplayState = vector<bool>;
using Problem = vector<DisplayState>;

class SevenSegmentDisplayStatics //Using a separate class to do some static (one-time only) initialization of SevenSegmentDisplay.
{
public:
	vector<DisplayState> digitDisplays;

	SevenSegmentDisplayStatics()
	{
		digitDisplays.push_back({ true, true, true, true, true, true, false });
		digitDisplays.push_back(vector<bool>({ false, true, true, false, false, false, false }));
		digitDisplays.push_back(vector<bool>({ true, true, false, true, true, false, true }));
		digitDisplays.push_back(vector<bool>({ true, true, true, true, false, false, true }));
		digitDisplays.push_back(vector<bool>({ false, true, true, false, false, true, true }));
		digitDisplays.push_back(vector<bool>({ true, false, true, true, false, true, true }));
		digitDisplays.push_back(vector<bool>({ true, false, true, true, true, true, true }));
		digitDisplays.push_back(vector<bool>({ true, true, true, false, false, false, false }));
		digitDisplays.push_back(vector<bool>({ true, true, true, true, true, true, true }));
		digitDisplays.push_back(vector<bool>({ true, true, true, true, false, true, true }));
	}
};

//Solves the puzzle at https://code.google.com/codejam/contest/3214486/dashboard#s=p0
class SevenSegmentDisplay : public IAlgorithm<Problem, unique_ptr<DisplayState>>
{
	bool SevenSegmentDisplay::StillOkay(int number, DisplayState display, set<int>& workingDigits, set<int>& brokenDigits);

public:
	static SevenSegmentDisplayStatics statics;

	Problem Parse(istream& stream) override;
	unique_ptr<DisplayState> Solve(const Problem& input) override; //according to the problem some times no solution can be found, which we encode with a nullptr.
	string Print(const unique_ptr<DisplayState>& output) override;
};
