//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file main.cpp
//!
//! @author Pasha, 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#include "Vector.h"

#include "Stack_HW1.h"
/*
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! A unit‐test to Push() method of Stack
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_PUSH															\
		Stack* s1 = new Stack;												\
		s1->Push((Stack::value_type)1.1);									\
		if(s1->Top() == (Stack::value_type)1.1) printf("TEST_PUSH IS OK!"); \
		else																\
		{																	\
			s1->Dump();														\
			printf("TEST_PUSH FAILED!");									\
		}																	\

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! A unit‐test to Pop() method of Stack
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_POP									\
		Stack* s1 = new Stack;						\
		s1->Push((Stack::value_type)1.2);			\
		s1->Pop();									\
		if(s1->Empty()) printf("TEST_PUSH IS OK!"); \
		else										\
		{											\
			s1->Dump();								\
			printf("TEST_PUSH FAILED!");			\
		}											\

*/
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! main
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#include "MyPrint.h"
#include <algorithm>
#include <vector>

#define TEST(what, func)								\
	if (!what)											\
		std::cout << #func" is failed!" << std::endl;	\
	else												\
		std::cout << #func" is OK!" << std::endl




void check_stack() {
	Stack<int> mystack;
	TEST(mystack.IsEmpty(), IsEmpty());
	for (int i = 0; i < 100; ++i)
		mystack.Push(i);
	TEST(mystack.Size() == 100, Size());
	mystack.Pop();
	TEST(mystack.Top() == 98, Top());
}

void check_vector()
{
	Vector<int> myvector;
	TEST(myvector.IsEmpty(), IsEmpty());
	for (int i = 0; i < 100; i++)
		myvector.PushBack(i);
	TEST(myvector.Size() == 100, Size());
	myvector.PopBack();
	TEST(myvector.Last() == 99, Last());
	TEST(myvector.First() == 0, First());
}

void check_iterators()
{
	Vector<int> myvector(30);
	srand(time(0));
	for (auto it = myvector.Begin(); it != myvector.End(); ++it)
		*it = rand() % 129;
	std::cout << "Start sequence: ";
	for (auto it = myvector.Begin(); it != myvector.End(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	std::sort(myvector.Begin(), myvector.End());
	std::cout << "End sequence: ";
	for (auto it = myvector.Begin(); it != myvector.End(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

int main()
{
	try {
		check_stack();
		check_vector();
		check_iterators();
	}
	catch (std::exception exc) {
		std::cout << exc.what() << std::endl;
	}
	std::cin.ignore();
	return 0;
}