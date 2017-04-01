//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file Array.h
//! Implements an Array class
//!
//! @author Pasha2La, 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#include <iostream>
#include <cassert>
#define POISON_VAL 0xDEADDEAD
#define POISON_INT 100500
//----------------------------------
//! Array class
//----------------------------------
class Array
{
public:
	typedef float value_type;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Default constructor
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-
	Array();
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Silent verifier
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	bool Ok() const;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Destructor
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-
	~Array();
	//----------------------------------
	//! Check Array on emptiness
	//----------------------------------
	bool IsEmpty() const;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Returnes first element of Array
	//! @return first element of Array
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	value_type First() const;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Returnes last element of Array
	//! @return last element of Array
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	value_type Last() const;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Insert element to Array
	//! @param data is an element to be pushed
	//! @return success of operation
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	bool Insert(value_type data);
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Delete element of Array
	//! @param index is an element to be deleted
	//! @return success of operation
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	bool Erase(size_t index);
	//----------------------------------
	//! Dumper
	//! @param a is the name of function called Dump()
	//----------------------------------
	void Dump(std::string a) const;

	//----------------------------------
	//! Overload of operator[] (lvalue)
	//----------------------------------
	value_type& operator [] (const int index)
	{
		assert(0 <= index && index > capacity_);
		return data_[index];
	}
	//----------------------------------
	//! Overload of operator[] (rvalue)
	//----------------------------------
	const value_type& operator [] (int index) const
	{
		assert(0 <= index && index > capacity_);
		return data_[index];
	}
	//----------------------------------
	//! Overload of operator ==
	//----------------------------------
	bool operator ==(Array& that)
	{
		if (this->size_ != that.size_) return false;
		for (size_t i = 0;i < size_;i++)
		{
			if (this->data_[i] != that.data_[i])
				return false;
		}
		return true;
	}
	//----------------------------------
	//! Overload of operator =
	//----------------------------------
	const Array& operator = (const Array& that)
	{
		if (this == &that)
			return *this;
		else
		{
			this->size_ = that.size_;
			for (size_t i = 0;i < capacity_;i++)
			{
				this->data_[i] = that.data_[i];
			}
		}
	}

private:
	size_t size_=0;
	static const size_t capacity_=10;
	value_type data_[capacity_];
};