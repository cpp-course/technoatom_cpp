//---------------------
//!	@file MyException.h
//! Class of exceptions for throw
//! @author Pasha2La
//---------------------


#include <exception>


class MyException : public std::exception
{
public:
	MyException(): code_(100500), mesg_("Smth went wrong"), file_("NULL"), line_(NULL) {};
	MyException(int code, char* mesg, char* file, int line) :code_(code), mesg_(mesg), file_(file), line_(line) {};
	~MyException() {};
	//! code of exception
	int code_;
	//! message to user
	char* mesg_;
	//! 
	char* file_;
	int line_;
};