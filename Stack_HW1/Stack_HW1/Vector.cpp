#define _CRT_SECURE_NO_WARNINGS
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

template<typename value_type>
Vector<value_type>::Vector(): size_(0), capacity_(10)
{
	data_ = new value_type[capacity_];
	for (size_t i = 0; i < capacity_;i++)
		data_[i] = POISON_VAL;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Vector<value_type>::Vector(size_t capacity): size_(0), capacity_(capacity)
{
	data_ = new value_type[capacity_];
	for (size_t i = 0; i < capacity_;i++)
		data_[i] = POISON_VAL;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Vector<value_type>::Ok() const
{
	if (size_ <= capacity_) return true;
	else return false;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Vector<value_type>::~Vector()
{
	delete data_;	//норм?
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Vector<value_type>::IsEmpty() const
{
	if (size_ == 0) return true;
	else return false;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
value_type Vector<value_type>::First() const		//ааааа, как это сделать
{
	Dump("First()");
	if ((!IsEmpty()) && (Ok())) return data_[0];
	else return POISON_VAL;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
value_type Vector<value_type>::Last() const
{
	Dump("Last()");
	if ((!IsEmpty()) && (Ok())) return data_[size_-1];
	else return POISON_VAL;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Vector<value_type>::Insert(Vector<value_type> data)
{
	Dump("Insert()");
	if (!Ok())
	{
		return;
	}
	if (size_ == capacity_) Expand();
	data_[size_] = data;
	size_++;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Vector<value_type>::Erase(size_t index)
{
	Dump("Erase()");
	if ((size_ - 1 >= index) && (Ok()))
	{
		data_[index] = POISON_VAL;
		for (size_t i = index;i < size_ - 1;i++)
		{
			data_[i] = data_[i + 1];
		}
		size_--;
	}
	else
	{
		std::ofstream dumpfile("dump.txt", std::ios_base::app);
		dumpfile << "ERROR! Can not delete element by index " << index << "!\n";
		dumpfile.close();
	}
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Vector<value_type>::Dump(std::string a) const
{
	std::ofstream dumpfile("dump.txt", std::ios_base::app);
	if (!dumpfile.is_open())
	{
		printf("Can not open Dump.txt");
		return;
	}
	dumpfile << "--------------------------------------------------------------\nDump() for class Vector\n";
	dumpfile << "Function " << a << "\n";
	std::time_t result = std::time(NULL);
	dumpfile << std::asctime(std::localtime(&result));
	dumpfile << "\n\n";
	dumpfile << "Vector " << " ok(" << Ok() << ")\n";
	dumpfile << "size_ = " << size_ << "\n";
	dumpfile << "capacity_ = " << capacity_ << "\n";
	for (size_t i = 0; i < capacity_; i++)
	{
		dumpfile << "\tdata_[" << i << "] = " << data_[i] << "\n";
	}
	dumpfile.close();
}
