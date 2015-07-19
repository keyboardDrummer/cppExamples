#include "stdafx.h"
#include "gtest/gtest.h"
#include <iostream>
#include "SevenSegmentDisplay.h"

TEST(SevenSegmentDisplay, first)
{
	SevenSegmentDisplay algorithm;
	string input = "1 1111111";
	auto stringSolution = algorithm.Run(istringstream(input));
	EXPECT_EQ("1110000", stringSolution);
}

TEST(SevenSegmentDisplay, second)
{
	SevenSegmentDisplay algorithm;
	string input = "2 0000000 0001010";
	auto stringSolution = algorithm.Run(istringstream(input));
	EXPECT_EQ("Error!", stringSolution);
}

TEST(SevenSegmentDisplay, third)
{

	SevenSegmentDisplay algorithm;
	string input = "3 0100000 0000111 0000011";
	auto stringSolution = algorithm.Run(istringstream(input));
	EXPECT_EQ("0100011", stringSolution);
}

TEST(SevenSegmentDisplay, fourth)
{
	SevenSegmentDisplay algorithm;
	string input = "5 1011011 1011111 1010000 1011111 1011011";
	auto stringSolution = algorithm.Run(istringstream(input));
	EXPECT_EQ("0010011", stringSolution);
}