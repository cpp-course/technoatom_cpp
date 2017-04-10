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

class MyCPU
{
public:
	MyCPU();
	void SetRegister(int data, int index);
	int GetRerister(int index);
	void SetLabel(int data, int index);
	int GetLabel(int index);
private:
	//! Registers for CPU
	int register_[100];
	//! Stack for CPU
	shared_ptr<Stack<int> > stack_;
	//! Vector of labels for jumps
	shared_ptr<Vector<int> > label_;
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
	label_ = new Vector<int>;
	callstack_ = new Stack<int>;
}

void MyCPU::SetRegister(int data, int index)
{
	if (index < 0 || index>99)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);		//так??
	register_[index] = data;
}

int MyCPU::GetRerister(int index)
{
	if (index < 0 || index>99)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);		//так??
	return register_[index];
}

void MyCPU::SetLabel(int data, int index)
{
	if (index < 0 || index>=label_->Size())
		throw MyException(1, "Bad index!", __FILE__, __LINE__);		//так??
	label_[index] = data;
}

int MyCPU::GetLabel(int index)
{
	if (index < 0 || index >= label_->Size())
		throw MyException(1, "Bad index!", __FILE__, __LINE__);		//так??
	return label_[index];
}