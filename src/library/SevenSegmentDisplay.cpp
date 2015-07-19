#include "stdafx.h"
#include "SevenSegmentDisplay.h"
#include "Strings.h"
#include "Option.h"
#include <algorithm>
#include <set>

SevenSegmentDisplayStatics SevenSegmentDisplay::statics;

DisplayState& ObservationToDisplayState(string observation)
{
	if (observation.size() != 7)
		throw invalid_argument("Should be 7 digits");

	auto result = new DisplayState(observation.size());
	auto charToBool = [](char _char) { return _char == '1'; };
	std::transform(observation.begin(), observation.end(), result->begin(), charToBool);
	return *result;
}

Problem SevenSegmentDisplay::Parse(istream& stream)
{
	string line;
	getline(stream, line);

	auto words = Strings::Split(' ', line);
	words.erase(words.begin());
	Problem result(words.size());
	std::transform(words.begin(), words.end(), result.begin(), ObservationToDisplayState);
	return result;
}


set<int> GetWorkingDigits(Problem input)
{
	set<int> workingDigits{};
	
	for(DisplayState observation : input)
	{
		for (size_t digit = 0; digit < observation.size(); digit++)
		{
			if (observation.at(digit)) {
				workingDigits.insert(digit);
			}
		}
	};
	
	return workingDigits;
}

unique_ptr<DisplayState> SevenSegmentDisplay::Solve(const Problem& input)
{
	auto workingDigits = GetWorkingDigits(input);
	auto options = set<Option>();
	for (int i = 0; i < 10; i++)
		options.insert(Option(i));

	for(auto observation : input)
	{
		auto newOptions = set<Option>();
		if (options.size() > 0)
		{
			for(auto option : options) 
			{
				bool stillGood = option.Progress(observation, workingDigits);
				if (stillGood) {
					newOptions.insert(option);
				}
			}
		}
		options = move(newOptions); //Move is faster than copying, and we don't need newOptions any more.
	};

	if (options.size() == 1)
	{
		Option option = *(options.begin());
		return option.Print(workingDigits);
	}
	return nullptr;
}

string SevenSegmentDisplay::Print(const unique_ptr<DisplayState>& output)
{
	if (output == nullptr)
		return "Error!";

	vector<string> states;
	std::transform(output->begin(), output->end(), back_inserter(states), [](bool state)
	{
		return state ? "1" : "0";
	});

	return Strings::Join(states, "");
}