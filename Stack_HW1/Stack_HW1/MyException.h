//---------------------
//!	@file MyException.h
//! Class of exceptions for throw
//! @author Pasha2La
//---------------------


#include <exception>


class MyException : public std::exception
{
public:
	// FIXME: почему в этом файле отступы стоят не так, как в предыдущих?
	// FIXME: Что такое 100500? "Smth went wrong". Что такое "NULL"?
	// Как предполагается доставать информацию из этого исключения, если все его метода приватны?
	MyException(): code_(100500), mesg_("Smth went wrong"), file_("NULL"), line_("NULL") {};
	MyException(int code, char* mesg, char* file, char* line) :code_(code), mesg_(mesg), file_(file), line_(line) {};
	// FIXME: А зачем запрещать конструктор копирования?
	MyException(const MyException &E) = delete;	//çàïðåùàåì êê
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
