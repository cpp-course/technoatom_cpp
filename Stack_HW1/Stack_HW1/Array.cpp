#define _CRT_SECURE_NO_WARNINGS
#include "Array.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

Array::Array()
{
	size_ = 0;
	for (size_t i = 0;i < capacity_; i++) data_[i] = POISON_INT;
}

bool Array::Ok() const
{
	if (size_ <= capacity_) return true;
	else return false;
}

Array::~Array()
{
	//???
}

bool Array::IsEmpty() const
{
	if (size_ == 0) return true;
	else return false;
}

Array::value_type Array::First() const
{
	Dump("First()");
	if ((!IsEmpty()) && (Ok())) return data_[0];
	else return POISON_VAL;		//если value_type не float, то поломается
}

Array::value_type Array::Last() const
{
	Dump("Last()");
	if ((!IsEmpty()) && (Ok())) return data_[size_-1];
	else return POISON_VAL;		//если value_type не float, то поломается
}

bool Array::Insert(Array::value_type data)
{
	Dump("Insert()");
	if (size_ < capacity_)
	{
		data_[size_] = data;
		size_++;
		return true;
	}
	else
	{
		std::ofstream dumpfile("dump.txt", std::ios_base::app);
		dumpfile << "ARRAY IS FULL!!!\nCan not Insert element!\n";
		dumpfile.close();
		return false;
	}
}

bool Array::Erase(size_t index)
{
	Dump("Erase()");
	if ((size_ - 1>= index) && (Ok()))
	{
		data_[index] = POISON_VAL;
		for (size_t i = index;i < size_ - 1;i++)
		{
			data_[i] = data_[i + 1];
		}
		size_--;
		return true;
	}
	else
	{
		std::ofstream dumpfile("dump.txt", std::ios_base::app);
		dumpfile << "ERROR! Can not delete element by index " << index << "!\n";
		dumpfile.close();
		return false;
	}
}

void Array::Dump(std::string a) const
{
	std::ofstream dumpfile("dump.txt", std::ios_base::app);
	if (!dumpfile.is_open())
	{
		printf("Can not open Dump.txt");
		return;
	}
	dumpfile << "--------------------------------------------------------------\nDump() for class Array\n";
	dumpfile << "Function " << a << "\n";
	std::time_t result = std::time(NULL);
	dumpfile << std::asctime(std::localtime(&result));
	dumpfile << "\n\n";
	dumpfile << "Array " << " ok(" << Ok() << ")\n";
	dumpfile << "size_ = " << size_ << "\n";
	dumpfile << "capacity_ = " << capacity_ << "\n";
	for (size_t i = 0; i < capacity_; i++)
	{
		dumpfile << "\tdata_[" << i << "] = " << data_[i] << "\n";
	}
	dumpfile.close();
}