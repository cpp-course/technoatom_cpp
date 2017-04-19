//------------------------------
//! @file MyCPU.h
//! Works with bitecode
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//------------------------------

#pragma once

#include"Stack_HW1.h"
#include"Array.h"
#include"MyException.h"
#include"SmartPointers.h"
#include"Header.h"

class MyCPU
{
public:
	MyCPU();
	~MyCPU();
	void SetRegister(int data, int index);
	int GetRegister(int index);
	//! Executes translated scripts
	void Execute(char *name);
	//! void to make array of code for CPU
	void Mkarr(char *name, Vector<int> &vect);
private:
	//! Registers for CPU
	int register_[100];
	//! Stack for CPU
	Stack<int> *stack_;
	//! Stack of calls
	Stack<int> *callstack_;
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

MyCPU::~MyCPU()
{
	delete stack_;
	delete callstack_;
}

void MyCPU::SetRegister(int data, int index)
{
	if (index < 0 || index>99)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);
	register_[index] = data;
}

int MyCPU::GetRegister(int index)
{
	if (index < 0 || index>99)
		throw MyException(1, "Bad index!", __FILE__, __LINE__);
	return register_[index];
}

void MyCPU::Mkarr(char *name, Vector<int> &vect)
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
		//кидаем код команды в массив
		if (buff == "")
			return;
		switch (buff[0])
		{
		case 'a':
			vect.PushBack(10);
			break;
		case 'b':
			vect.PushBack(11);
			break;
		case 'c':
			vect.PushBack(12);
			break;
		case 'd':
			vect.PushBack(13);
			break;
		case 'e':
			vect.PushBack(14);
			break;
		case 'f':
			vect.PushBack(15);
			break;
		default:
			//для обычных индексов - просто кидаем так
			vect.PushBack(atoi(buff.substr(0, 1).c_str()));
			break;
		}
		//если команда без аргументов(add, sub, div, mul, ret), то просто пропускаем
		if (!(buff[0] == '3' || buff[0] == '4' || buff[0] == '5' || buff[0] == '6' || buff[0] == '8'))
			vect.PushBack(atoi(buff.substr(1).c_str()));
	}
	fin.close();
}

void MyCPU::Execute(char *name)
{
	int buff;
	Vector<int> source;
	//
	Mkarr(name, source);
	int a, b;
	for (int i = 0; i < source.Size();i++)
	{
		buff = source[i];
		switch (buff)
		{
		case 0:	//push for int
			i++;
			stack_->Push(source[i]);
			break;
		case 1:	//push for reg
			i++;
			stack_->Push(register_[source[i]]);
			break;
		case 2:	//pop for reg
			i++;
			register_[source[i]] = stack_->Top();
			stack_->Pop();
			break;
		case 3:	//add
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			stack_->Push(a+b);
			break;
		case 4:	//sub
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			stack_->Push(b - a);
			break;
		case 5:	//mul
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			stack_->Push(a*b);
			break;
		case 6:	//div
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			stack_->Push(b/a);
		case 7:	//call
			callstack_->Push(i + 2);
			i = source[++i] - 1;
			break;
		case 8:	//ret
			i = callstack_->Top() - 1;
			callstack_->Pop();
			break;
		case 9:	//jmp
			i = source[++i] - 1;
			break;
		case 10:	//je
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			if (a == b) i = source[++i] - 1;
			else i++;
			break;
		case 11:	//ja
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			i++;
			if (a > b) i = source[i]-1;
			break;
		case 12:	//jb
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			i++;
			if (a < b) i = source[i]-1;
			break;
		case 13:	//jae
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			i++;
			if (a >= b) i = source[i]-1;
			break;
		case 14:	//jbe
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			i++;
			if (a <= b) i = source[i]-1;
			break;
		case 15:	//jne
			a = stack_->Top();
			stack_->Pop();
			b = stack_->Top();
			stack_->Pop();
			i++;
			if (a != b) i = source[i]-1;
			break;
		default:
			throw MyException(4, "Execution error", __FILE__, __LINE__);
			break;
		}
	}

}

// { 'add', ARGS_COUNT, CALLBACK, COMMAND_CODE}