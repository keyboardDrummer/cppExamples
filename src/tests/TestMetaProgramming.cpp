#include "stdafx.h"

#include "stdafx.h"
#include "gtest/gtest.h"
#include "Factorial.h"
#include "Fibonacci.h"

using namespace std;

TEST(TemplateProgramming, factorial)
{
	Factorial<5> factorial;
	int value = factorial.value;
	EXPECT_EQ(120, value);
}

TEST(TemplateProgramming, fibonacci)
{
	Fibonacci<5> factorial;
	int value = factorial.value;
	EXPECT_EQ(8, value);
}