// ConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "IAlgorithm.h"
#include "SevenSegmentDisplay.h"
#include <istream>
#include <fstream>     

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#elif
#include <unistd.h>
#endif

using namespace std;

void SkipBOM(std::ifstream &in)
{
	char test[20] = { 0 };
	in.read(test, 20);
	if ((unsigned char)test[0] == 0xEF &&
		(unsigned char)test[1] == 0xBB &&
		(unsigned char)test[2] == 0xBF)
	{
		return;
	}
	in.seekg(0);
}

void GetStreams(int argc, char* argv[], istream** in, ostream** out)
{
	if (argc > 1)
	{
		string& inputFileName = *new string(argv[1]);
		std::ifstream& ifs = *new ifstream(inputFileName, ios::in);
		
		if (!ifs.is_open())
		{
			throw "Could not open input file";
		}

		auto outputFileName = inputFileName.substr(0, inputFileName.size() - 2) + "out";
		SkipBOM(ifs);
		*in = &ifs;
		*out = new ofstream(outputFileName, ios::out);
	}
	else
	{
		*in = &cin;
		*out = &cout;
	}
}

int main(int argc, char* argv[])
{
	SevenSegmentDisplay algorithm;

	istream* inputStream;
	ostream* outputStream;
	GetStreams(argc, argv, &inputStream, &outputStream);

	string line;
	getline(*inputStream, line);
	int cases = atoi(line.c_str());

	for (int caseIndex = 0; caseIndex < cases; caseIndex++)
	{
		string output = algorithm.Run(*inputStream);
		*outputStream << "Case #" << (caseIndex + 1) << ": " << output << "\n";
	}

	return 0;
}
