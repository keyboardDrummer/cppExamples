
#include "stdafx.h"
#include "gtest/gtest.h"
#include "MyVector.h"
#include <memory>
#include <vector>

using namespace std;

TEST(MyVector, copyConstructor)
{
	MyVector<int> vector;
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	EXPECT_EQ(3, vector.at(1));
	MyVector<int> copy = vector;
	EXPECT_EQ(2, copy.at(0));
	EXPECT_EQ(3, copy.at(1));
	EXPECT_EQ(4, copy.at(2));
}

TEST(MyVector, at)
{
	MyVector<int> vector;
	vector.push_back(2);
	EXPECT_EQ(2, vector.at(0));
}

TEST(MyVector, assignmentOperator)
{
	MyVector<int> vector;
	vector.push_back(2);
	vector[0] = 3;
	EXPECT_EQ(3, vector.at(0));
}

TEST(MyVector, insert)
{
	MyVector<int> vector;
	vector.push_back(0);
	vector.push_back(2);
	vector.push_back(3);
	vector.insert(vector.begin()+1,1);
	EXPECT_EQ(0, vector.at(0));
	EXPECT_EQ(1, vector.at(1));
	EXPECT_EQ(2, vector.at(2));
	EXPECT_EQ(3, vector.at(3));
}

TEST(MyVector, erase)
{
	MyVector<int> vector;
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	auto begin = vector.begin();
	vector.erase(begin + 1);
	EXPECT_EQ(2, vector.at(0));
	EXPECT_EQ(4, vector.at(1));
}

TEST(MyVector, moveSemanticsReference)
{
	int* a = new int(2);
	int* b = new int(3);
	int* c = new int(4);
	vector<unique_ptr<int>> vector;
	vector.push_back(unique_ptr < int > {a});
	vector.push_back(unique_ptr<int>(b));
	vector[0] = unique_ptr<int>(c);
	EXPECT_EQ(4, *vector.at(0));
	EXPECT_EQ(3, *vector.at(1));
}

TEST(MyVector, moveSemantics)
{
	int* a = new int(2);
	int* b = new int(3);
	MyVector<unique_ptr<int>> vector;
	vector.push_back(unique_ptr < int > {a});
	vector.push_back(unique_ptr<int>(b));
	EXPECT_EQ(2, *vector.at(0));
	EXPECT_EQ(3, *vector.at(1));
}

TEST(MyVector, sharedPtr)
{
	int* a = new int(2);
	int* b = new int(3);
	MyVector<shared_ptr<int>> vector;
	auto sharedA = shared_ptr<int> {a};
	auto sharedB = shared_ptr<int> {b};
	vector.push_back(sharedA);
	vector.push_back(std::move(sharedA)); //give up ownership of a
	vector.push_back(std::move(sharedB)); //give up ownership of b.
	EXPECT_EQ(2, *vector.at(0));
	EXPECT_EQ(2, *vector.at(1));
	EXPECT_EQ(3, *vector.at(2));
	vector.erase(vector.begin() + 1); //erase one copy of sharedA.
	EXPECT_EQ(2, *vector.at(0));
	EXPECT_EQ(3, *vector.at(1));
	vector.erase(vector.begin()); //erase the other and last copy of sharedA.
	EXPECT_NE(2, *a); //a should have been destructed so it's not 2 anymore, instead it'll be some garbage.
}