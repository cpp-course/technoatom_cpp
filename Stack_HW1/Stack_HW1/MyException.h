//---------------------
//!	@file MyException.h
//! Class of exceptions for throw
//! @author Pasha2La
//---------------------

class MyException
{
public:
	MyException(): code_(100500), mesg_("Smth went wrong"), file_("NULL"), line_("NULL") {};
	MyException(int code, char* mesg, char* file, char* line) :code_(code), mesg_(mesg), file_(file), line_(line) {};
	MyException(const MyException &E) = delete;	//запрещаем кк
	~MyException() {};
private:
	//! code of exception
	int code_;
	//! message to user
	char* mesg_;
	//! 
	char* file_;
	char* line_;
};