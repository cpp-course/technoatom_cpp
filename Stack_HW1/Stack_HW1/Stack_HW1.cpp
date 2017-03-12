#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Stack_HW1.h"
#include <fstream>
#include <ctime>
#include <iomanip>

#define ASSERT_OK \
	if(!this->Ok()) \
	{ \
		this->Dump(); \
		printf("Stack is damaged!\n"); \
	}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack() : size_(0)
{
	capacity_ = 10;
	data_ = new Vector<value_type>[capacity_];	//что, если память не выделится?
	size_ = 0;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::~Stack()
{
	size_ = POISON_VAL;
	capacity_ = POISON_VAL;
	delete data_;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Stack<value_type>::Push(value_type value)
{
	ASSERT_OK;
	data_->Insert(value);
	if (size_ == capacity_) capacity_ += 10;	//внутри Insert'a вектор сам расширится
	size++;
	//old non-template version 
	/*	
	if (size_ >= capacity_)
	{
		ASSERT_OK;
		return false;
	}
	data_[size_] = value;
	size_++;
	ASSERT_OK;
	return true;
	*/
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Stack<value_type>::Pop()
{
	ASSERT_OK;
	if (size_ > 0)
	{
		data_[size_] = POISON_VAL;
		size_--;
	}
	else
	{
		//????????????????
	}
	ASSERT_OK;
	return;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
value_type Stack<value_type>::Top() const
{
	ASSERT_OK;
	if (size_ > 0)
	{
		return data_[size_-1];
	}
	else
	{
		return (value_type)POISON_VAL;	//норм ли?
	}
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
size_t Stack<value_type>::Size() const
{
	ASSERT_OK;
	return size_;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
size_t Stack<value_type>::Capacity() const
{
	ASSERT_OK;
	return capacity_;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Stack<value_type>::Empty() const
{
	ASSERT_OK;
	if (size_ == 0) return true;
	else return false;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Stack<value_type>::Ok() const
{
	if ((size_ <= capacity_) && (size_ >= 0)) return true;
	else return false;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Stack<value_type>::Dump() const
{
	std::ofstream dumpfile("Dump.txt", std::ios_base::app);
	if (!dumpfile.is_open())
	{
		printf("Cannot open Dump.txt");
		return;
	}
	dumpfile << "--------------------------------------------------------------\nNew call of Dump()\n";
	std::time_t result = std::time(NULL);
	dumpfile << std::asctime(std::localtime(&result));
	dumpfile << "\n\n";
	dumpfile << "Stack " << " ok(" << Ok() << ")\n";
	dumpfile << "size_ = " << size_ << "\n";
	dumpfile << "capacity_ = " << capacity_ << "\n";
	dumpfile << "data [" << capacity_ << "]:";
	dumpfile << "{\n";
	for (size_t i = 0; i < capacity_; i++)
	{
		dumpfile << "[" << i << "] = " << data_[i] << "\n";
	}
	dumpfile << "}\n";
	dumpfile.close();
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐