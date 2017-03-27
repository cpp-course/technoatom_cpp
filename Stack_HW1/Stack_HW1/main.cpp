//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file main.cpp
//!
//! @author Pasha, 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#include "Vector.h"

//#include "Stack_HW1.h"
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
int main()
{
	Vector<int> v;
	for (int i = 0; i < 15; ++i)
		v.PushBack(i);
	Vector<int>::Iterator it = v.Begin();
	for (; it != v.End(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	try {
		*it;
	}
	catch (std::exception ex) {
		std::cout << ex.what();
	}
	std::cout << std::endl;
	MyPrint("x = #, y = #, z = #####", 1, 2, 3, 4);
	std::cin.ignore();
	return 0;
}