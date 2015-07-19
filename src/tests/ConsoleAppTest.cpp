
#include "stdafx.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	cout << "Please any key to exit";
	cin.get();
	return 0;
}

