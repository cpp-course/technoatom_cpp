//---------------------
//!	@file MyException.h
//! Class of exceptions for throw
//! @author Pasha2La
//---------------------
#pragma once

#include <exception>

char *myitoa(int i)
{
	int digs = 0, x = i;
	bool fl = false;
	if (i < 0)
	{
		digs++;
		i = -i;
		fl = true;
	}
	while (x != 0)
	{
		digs++;
		x /= 10;
	}
	char *a = new char[digs + 1];
	char *b = a + digs;
	*b-- = '\0';
	while (i != 0)
	{
		x = i % 10;
		i /= 10;
		*b-- = x + '0';
	}
	return a;
}


class MyException : public std::exception
{
public:
	MyException() : code_(100500), mesg_("Smth went wrong"), file_("NULL"), line_(NULL) {};
	MyException(int code, char* mesg, char* file, int line) :code_(code), mesg_(mesg), file_(file), line_(line) {};
	~MyException() {};
	//! code of exception
	int code_;
	//! message to user
	char* mesg_;
	//! 
	char* file_;
	int line_;
	const char *what() const;
};

const char *MyException::what() const
{
	std::string str = mesg_;
	str += " File: ";
	str += file_;
	str += ". Line: ";
	str += myitoa(line_);
	return str.c_str();
}