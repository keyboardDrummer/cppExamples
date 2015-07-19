#include "stdafx.h"
#include "SevenSegmentDisplay.h"
#include <memory>

class Option
{
private:
	int number;
	set<int> brokenLeds;

	int GetNextNumber(int number);
public:
	Option(int number);

	bool operator<(Option const& a2) const;

	bool Progress(DisplayState display, const set<int>& workingDigits);

	bool ProcessDisplay(DisplayState display, const set<int>& workingLeds);

	unique_ptr<DisplayState> Print(const set<int>& workingLeds);
};
