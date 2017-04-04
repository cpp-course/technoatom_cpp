//------------------------------
//! @file MyCPU.h
//! Works with scripts
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//------------------------------

#include"Stack_HW1.h"
#include"Array.h"
#include"MyException.h"

template <typename value_type>
class MyCPU
{
public:
	MyCPU();
	void SetRegister(value_type data, int index);
	value_type GetRerister(int index);
	void SetLabel(int data, int index);
	value_type GetLabel(int index);
	~MyCPU();
private:
	//! Registers for CPU
	value_type register_[100];
	//! Stack for CPU
	Stack<value_type> stack_;
	//! Vector of labels for jumps
	Vector<int> label_;
	//! Stack of calls
	Stack<int> callstack_;
};

template <typename value_type>
MyCPU<value_type>::MyCPU()
{
	for (int i = 0;i < 100;i++)
	{
		register_[i] = NAN;
	}
	stack_ = new Stack<value_type>;
	label_ = new Vector<value_type>;
	callstack_ = new Stack<int>;
}
template <typename value_type>
void MyCPU<value_type>::SetRegister(value_type data, int index)
{
	if (index < 0 || index>99)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);		//так??
	register_[index] = data;
}
template <typename value_type>
value_type MyCPU<value_type>::GetRerister(int index)
{
	if (index < 0 || index>99)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);		//так??
	return register_[index];
}
template <typename value_type>
void MyCPU<value_type>::SetLabel(int data, int index)
{
	if (index < 0 || index>=label_.size_)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);		//так??
	label_[index] = data;
}
template <typename value_type>
value_type MyCPU<value_type>::GetLabel(int index)
{
	if (index < 0 || index >= label_.size_)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);		//так??
	return label_[index];
}
template <typename value_type>
MyCPU<value_type>::~MyCPU()
{
	delete stack_;
	delete label_;
	delete callstack_;
}