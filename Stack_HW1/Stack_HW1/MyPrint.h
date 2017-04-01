#include <iostream>
//---------------------------------
//! @file MyPrint.h
//! MyPrint - analog of printf()
//! @author Pasha2La
//---------------------------------


// FIXME: если функция принимает указатель - нужно обязательно проверить, не ноль ли это.
void MyPrint(const char* str)
{
	// А вообще, это выглядит как очень странный код. Зачем посимвольно выводить строчку, если можно вывести ее целиком?
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
