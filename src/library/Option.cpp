#include "Option.h"
#include "SevenSegmentDisplay.h"
#include <memory>

Option::Option(int number) : number(number)
{
}

bool Option::operator<(Option const& a2) const {
	Option const& a1 = *this;
	return a1.number < a2.number;
};

int Option::GetNextNumber(int number)
{
	return (number - 1 + 10) % 10;
}

bool Option::Progress(DisplayState display, const set<int>& workingDigits)
{
	if (ProcessDisplay(display, workingDigits))
	{
		number = Option::GetNextNumber(number);
		return true;	
	}
	return false;
}

bool Option::ProcessDisplay(DisplayState display, const set<int>& workingLeds)
{
	auto numberDisplay = SevenSegmentDisplay::statics.digitDisplays[number];
	for (size_t led = 0; led < display.size(); ++led)
	{
		bool ledWorks = workingLeds.find(led) != workingLeds.end();
		bool expectingDigit = numberDisplay[led];
		bool ledIsOn = display[led];
		if (expectingDigit && !ledIsOn)
		{
			if (ledWorks)
				return false;

			brokenLeds.insert(led);
		}

		if (!expectingDigit && ledIsOn)
			return false;
	}
	return true;
}

unique_ptr<DisplayState> Option::Print(const set<int>& workingLeds)
{
	int numberToShow = number;
	auto numberDisplay = SevenSegmentDisplay::statics.digitDisplays[numberToShow];
	unique_ptr<DisplayState> result(new DisplayState);
	for (size_t led = 0; led < numberDisplay.size(); ++led)
	{
		bool digitRequiresLed = numberDisplay[led];
		bool ledIsBroken = brokenLeds.find(led) != brokenLeds.end();
		bool ledIsWorking = workingLeds.find(led) != workingLeds.end();
		if (!digitRequiresLed)
			result->push_back(false);
		else if (ledIsBroken)
			result->push_back(false);
		else if (ledIsWorking)
			result->push_back(true);
		else
			return nullptr;
	}
	return result;
}
