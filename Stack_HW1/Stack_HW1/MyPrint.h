#include <iostream>
//---------------------------------
//! @file MyPrint.h
//! MyPrint - analog of printf()
//! @author Pasha2La
//---------------------------------

void MyPrint(const char* str)
{
	while (*str) std::cout << *str++;
}

template <typename T, typename... Args>
void MyPrint(const char* str, T val, Args... args)
{
	while (*str)
	{
		if (*str != '#') std::cout << *str++;
		else
		{
			std::cout << val;
			MyPrint(str + 1, args...);
			break;
		}
	}
}
