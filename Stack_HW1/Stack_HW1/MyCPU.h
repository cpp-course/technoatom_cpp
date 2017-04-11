//------------------------------
//! @file MyCPU.h
//! Works with bitecode
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//------------------------------

#include"Stack_HW1.h"
#include"Array.h"
#include"MyException.h"
#include"SmartPointers.h"
#include"Header.h"

class MyCPU
{
public:
	MyCPU();
	void SetRegister(int data, int index);
	int GetRerister(int index);
	void Execute(char *name);
private:
	//! Registers for CPU
	int register_[100];
	//! Stack for CPU
	shared_ptr<Stack<int> > stack_;
	//! Stack of calls
	shared_ptr<Stack<int> > callstack_;
};


MyCPU::MyCPU()
{
	for (int i = 0;i < 100;i++)
	{
		register_[i] = 0;
	}
	stack_ = new Stack<int>;
	callstack_ = new Stack<int>;
}

void MyCPU::SetRegister(int data, int index)
{
	if (index < 0 || index>99)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);
	register_[index] = data;
}

int MyCPU::GetRerister(int index)
{
	if (index < 0 || index>99)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);
	return register_[index];
}

void MyCPU::Execute(char *name)
{
	std::ifstream fin(name);
	if (!fin.is_open())
	{
		throw MyException(2, "Cannot open file", __FILE__, __LINE__);
	}
	std::string buff;
	while (!fin.eof())
	{
		std::getline(fin, buff);
		int index = atoi(buff.substr(1).c_str());
		switch (buff[0])
		{
		case '0':	//push for int
			stack_->Push(index);
			break;
		case '1':	//push for reg
			register_[index] = stack_->Top();
			stack_->Pop();
			break;
		case '2':	//pop for reg
			stack_->Push(register_[index]);
			break;
		case '3':	//add
			int a = stack_->Top();
			stack_->Pop();
			int b = stack_->Top();
			stack_->Pop();
			stack_->Push(a+b);
			break;
		case '4':	//sub
			int a = stack_->Top();
			stack_->Pop();
			int b = stack_->Top();
			stack_->Pop();
			stack_->Push(b - a);	//a-b or b-a?????????????
			break;
		case '5':

		case '6':

		case '7':

		case '8':

		case '9':

		case 'a':

		case 'b':

		case 'c':

		case 'd':

		case 'e':

		case 'f':

		default:
			break;
		}
	}

}