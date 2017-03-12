//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file Vector.h
//! Implements an Vector class
//!
//! @author Pasha2La, 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#include <iostream>
#include <cassert>
#define POISON_VAL 0xDEADDEAD
#define POISON_INT 100500
//----------------------------------
//! Vector class
//----------------------------------
template<typename value_type>
class Vector
{
public:
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Default constructor
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-
	Vector();
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Constructor with defined capacity
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-
	Vector(size_t capacity);
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Copying constructor
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-
	Vector(const Vector& that);						//сделать!!!!!!!!!!!!!!!!!!!!!!!!!!
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Silent verifier
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	bool Ok() const;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Destructor
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-
	~Vector();
	//----------------------------------
	//! Check Vector on emptiness
	//----------------------------------
	bool IsEmpty() const;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Returnes first element of Vector
	//! @return first element of Vector
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	value_type First() const;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Returnes last element of Vector
	//! @return last element of Vector
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	value_type Last() const;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Insert element to Vector
	//! @param data is an element to be pushed
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	void Insert(Vector<value_type> data);
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Delete element of Vector
	//! @param index is a number of element to be deleted
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	void Erase(size_t index);
	//----------------------------------
	//! Dumper
	//! @param a is the name of function called Dump()
	//----------------------------------
	void Dump(std::string a) const;

private:
	size_t size_;
	size_t capacity_;
	value_type* data_;
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Expands Vector on 10 elements
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	void Expand()
	{
		value_type* a;
		value_type* vect = new value_type[capacity_ + 10];
		for (size_t i = 0;i < capacity_;i++)
		{
			vect[i] = data_[i];
		}
		for (size_t i = capacity_;i < capacity_+10;i++)
		{
			vect[i] = POISON_VAL;
		}
		a = vect;
		vect = data_;
		data_ = a;
		delete[capacity_] vect;
		capacity_ += 10;
	}
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
	bool operator ==(Vector& that)
	{
		if (this->size_ != that.size_) return false;
		for (size_t i = 0;i < size_;i++)
		{
			if (this->data_[i] != that.data_[i])
				return false;
		}
		return true;
	}
};