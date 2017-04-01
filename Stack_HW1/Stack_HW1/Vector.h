#define _SCL_SECURE_NO_WARNINGS
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file Vector.h
//! Implements an Vector class
//!
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#pragma once

#include "Header.h"
#define _CRT_SECURE_NO_WARNINGS

//----------------------------------
//! Vector class
//----------------------------------
template<typename value_type>
class Vector
{
public:
	//-------------------------------
	//! Iterator class for Vector
	//-------------------------------
	class Iterator : public std::iterator<std::random_access_iterator_tag, value_type>
	{
		value_type *ptr_;
		const Vector * vec_;
	public:
//		Iterator() : ptr_(nullptr), vec_(nullptr) {}
		Iterator(value_type *ptr, const Vector * vec) : ptr_(ptr), vec_(vec) {}
		Iterator(const Iterator &that) : ptr_(that.ptr_), vec_(that.vec_) {}
		Iterator(Iterator &&that) : ptr_(that.ptr_), vec_(that.vec_) {}
		value_type &operator*()
		{
			if (ptr_ && vec_)
				return *ptr_;
			throw std::exception("pointer to nullptr");
		}
		int operator-(const Iterator &right)
		{
			return ptr_ - right.ptr_;
		}
		Iterator operator-(int right)
		{
			return Iterator(ptr_ - right, vec_);
		}
		Iterator operator+(int right)
		{
			return Iterator(ptr_ + right, vec_);
		}
		bool operator<(const Iterator &right)
		{
			return ptr_ < right.ptr_;
		}
		/*
		bool operator<=(const Iterator &right)
		{
			return ptr_ <= right.ptr_ || ptr_ || !right.ptr_;
		}
		bool operator>(const Iterator &right)
		{
			return ptr_ > right.ptr_ || !ptr_ || right.ptr_;
		}
		bool operator>=(const Iterator &right)
		{
			return ptr_ >= right.ptr_ || !ptr_ || right.ptr_;
		}
		*/
		Iterator &operator++()
		{
			if (++ptr_ > vec_->data_ + vec_->size_)
				ptr_ = vec_->data_ + vec_->size_;
			return *this;
		}
		Iterator &operator--()
		{
			if (--ptr_ < vec_->data_)
				ptr_ = vec_->data_ + vec_->size_;
			return *this;
		}
		Iterator &operator++(int)
		{
			Iterator tmp(*this);
			++*this;
			return tmp;
		}
		Iterator &operator--(int)
		{
			Iterator tmp(*this);
			--*this
			return tmp;
		}
		bool operator==(const Iterator &that)
		{
			return ptr_ == that.ptr_;
		}
		bool operator!=(const Iterator &that)
		{
			return ptr_ != that.ptr_;
		}
		Iterator &operator=(const Iterator &that)
		{
			if (this != &that)
			{
				ptr_ = that.ptr_;
				vec_ = that.vec_;
			}
			return *this;
		}
		Iterator &operator=(Iterator &&that)
		{
			if (this != &that)
			{
				ptr_ = that.ptr_;
				vec_ = that.vec_;
			}
			return *this;
		}
		Iterator &operator+=(int right)
		{
			ptr_ = (ptr_ + right < vec_->data_ + vec_->size_) ? ptr_ + right : vec_->data_ + vec_->size_;
			return *this;
		}
		Iterator &operator-=(int right)
		{
			ptr = ptr_ - right >= vec_->data_ ? ptr_ - right : vec_->data_ + vec_->size_;
			return *this;
		}

	};

	//----------------------------------
	//! Overload of operator new
	//----------------------------------
	void *operator new(size_t size);

	//----------------------------------
	//! Overload of placement operator new
	//----------------------------------
	void *operator new(size_t size, void* ptr);


	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Default constructor
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-------------------------------
	Vector();

	//----------------------------------------------------------------
	//! Consturctor with parameter
	//!
	//! @param size Size of Vector data array
	//----------------------------------------------------------------
	Vector(size_t size);

	//----------------------------------------------------------------
	//! Consturctor with 2 parameters
	//!
	//! @param size Size of Vector data array
	//! 
	//! @param value Value of all the cells
	//----------------------------------------------------------------
	Vector(size_t size, const value_type& value);

	//----------------------------------------------------------------
	//! Consturctor with 2 parameters
	//!
	//! @param size Size of Vector data array
	//! 
	//! @param value Value of all the cells
	//----------------------------------------------------------------
	Vector(size_t size, value_type&& value);

	//----------------------------------------------------------------
	//! Copy constructor
	//!
	//! @param that const lvalue reference to the object
	//----------------------------------------------------------------
	Vector(const Vector &that);

	//----------------------------------------------------------------
	//! Move constructor
	//!
	//! @param that rvalue reference to the object
	//----------------------------------------------------------------
	Vector(Vector &&that);

	//----------------------------------------------------------------
	//! Destructor
	//----------------------------------------------------------------
	~Vector();

	//----------------------------------------------------------------
	//! Copy assignment
	//!
	//! @param another lvalue reference to the object
	//!
	//! @return lvalue reference to this object
	//----------------------------------------------------------------
	Vector &operator=(Vector &another);

	//----------------------------------------------------------------
	//! Move assignment
	//!
	//! @param another rvalue reference to the object
	//!
	//! @return lvalue reference to this object
	//----------------------------------------------------------------
	Vector &operator=(Vector &&another);

	//----------------------------------
	//! Overload of operator[]
	//----------------------------------
	value_type& operator[] (int index);

	void PushBack(const value_type &value);
	void PushBack(value_type &&value);
	void PopBack();

	Iterator Begin() const
	{
		return Iterator(data_, this);
	}

	Iterator End() const
	{
		return Iterator((value_type *)(data_ + size_), this);
	}

//	void Resize(size_t size);
//	void Reserve(size_t capacity);



	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Size of data block
	//!
	//! @return size of data block
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	size_t Size() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Capacity of data block
	//!
	//! @return capacity of data block
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	size_t Capacity() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Checks Vector for emptyness
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	bool IsEmpty() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Silent verifier
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	bool Ok() const;

	//----------------------------------------------------------------
	//! Dumper
	//----------------------------------------------------------------
	void Dump(std::string a) const;

	
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
	/*
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
	*/

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	//! Delete all Vector's Elements
	//! 
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
	void Clear();

	//----------------------------------
	//! Overload of operator ==
	//----------------------------------
	bool operator==(Vector& that)
	{
		if (size_ != that.size_)
			return false;
		for (size_t i = 0; i < size_; ++i)
			if (data_[i] != that.data_[i])
				return false;
		return true;
	}

private:
	size_t size_;
	size_t capacity_;
	value_type* data_;


	void Reserve();
};


template<typename value_type>
Vector<value_type>::Vector() :
	size_(0), capacity_(0), data_(nullptr) {}

template<typename value_type>
Vector<value_type>::Vector(size_t size) :
	size_(size), capacity_(size), data_(new value_type[size])
{
	memset(data_, 0, sizeof(value_type) * size_);
}

template<typename value_type>
Vector<value_type>::Vector(size_t size, const value_type &value) :
	size_(size), capacity_(size), data_(new value_type[size])
{
	for (int i = 0; i < size_; ++i)
		data_[i] = value;
}

template<typename value_type>
Vector<value_type>::Vector(size_t size, value_type &&value) :
	size_(size), capacity_(size), data_(new value_type[size]) 
{
	value_type lval = value;
	for (int i = 0; i < size_; ++i)
		data_[i] = lval;
}

template<typename value_type>
Vector<value_type>::Vector(const Vector<value_type> &that) :
	size_(that.size_), capacity_(that.capacity_), data_(new value_type[that.capacity_])
{
	ASSERT_OK;
	std::copy(that.Begin(), that.End(), Begin());
}

template<typename value_type>
Vector<value_type>::Vector(Vector<value_type> &&that) :
	size_(that.size_), capacity_(that.capacity_), data_(that.data_)
{
	ASSERT_OK;
	that.data_ = nullptr;
}

template<typename value_type>
value_type& Vector<value_type>::operator[] (int index)
{
	ASSERT_OK;
	if (index < 0 || index >= size_)
		throw std::exception("Invalid index!");
	ASSERT_OK;
	return data_[index];
}

template<typename value_type>
Vector<value_type> &Vector<value_type>::operator=(Vector<value_type> &another)
{
	ASSERT_OK;
	if (this != &another)
	{
		size_ = another.size_;
		capacity_ = another.capacity_;
		data_ = new value_type[capacity_];
		std::copy(another.Begin(), another.End(), Begin());
	}
	ASSERT_OK;
	return *this;
}

template<typename value_type>
Vector<value_type> &Vector<value_type>::operator=(Vector<value_type> &&another)
{
	ASSERT_OK;
	if (this != &another)
	{
		size_ = another.size_;
		capacity_ = another.capacity_;
		data_ = another.data_;
	}
	ASSERT_OK;
	return *this;
}

template<typename value_type>
void Vector<value_type>::PushBack(const value_type &value)
{
	ASSERT_OK;
	if (size_ == capacity_)
		Reserve();
	data_[size_++] = value;
	ASSERT_OK;
}

template<typename value_type>
void Vector<value_type>::PushBack(value_type &&value)
{
	ASSERT_OK;
	if (size_ == capacity_)
		Reserve();
	data_[size_++] = value;
	ASSERT_OK;
}

template<typename value_type>
void Vector<value_type>::PopBack()
{
	ASSERT_OK;
	if (size_ == 0)
		throw std::exception("Vector is empty!");
	data_[--size_] = 0;
	ASSERT_OK;
}

template<typename value_type>
bool Vector<value_type>::Ok() const
{
	return size_ <= capacity_;
}

template<typename value_type>
Vector<value_type>::~Vector()
{
	if (data_)
		delete[] data_;
}

template<typename value_type>
bool Vector<value_type>::IsEmpty() const
{
	ASSERT_OK;
	return size_ == 0;
}

template<typename value_type>
size_t Vector<value_type>::Size() const
{
	ASSERT_OK;
	return size_;
}

template<typename value_type>
size_t Vector<value_type>::Capacity() const
{
	ASSERT_OK;
	return capacity_;
}

template<typename value_type>
void Vector<value_type>::Reserve()
{
	ASSERT_OK;
	size_t new_cap((size_t)(capacity_ * 1.618));
	if (new_cap == capacity_)
		++new_cap;
	value_type *tmp = new value_type[new_cap];
	capacity_ = new_cap;
	for (size_t i = 0; i < size_; ++i)
		tmp[i] = data_[i];
	memset(tmp + size_, 0, sizeof(value_type) * (capacity_ - size_));
	delete[] data_;
	data_ = tmp;
	ASSERT_OK;
}

/*
template<typename value_type>
void Vector<value_type>::Reserve(size_t capacity)
{
	//	ASSERT_OK;
	if (new_cap == capacity_)
		return;
	value_type *tmp = operator new(capacity);
	capacity_ = capacity;
	size_ = size_ > capacity_ ? capacity_ : size_;
	for (int i = 0; i < size_; ++i)
		tmp[i] = data_[i];
	operator delete(data_);
	data_ = tmp;
}
*/

template<typename value_type>
value_type Vector<value_type>::First() const		//ааааа, как это сделать
{
	ASSERT_OK;
	Dump("First()");
	if ((!IsEmpty()) && (Ok())) return data_[0];
	throw std::exception("Vector is Empty");
	ASSERT_OK;
}

template<typename value_type>
value_type Vector<value_type>::Last() const
{
	ASSERT_OK;
	Dump("Last()");
	if ((!IsEmpty()) && (Ok()))
	{
		return data_[size_ - 1];
		ASSERT_OK;
	}
	throw std::exception("Vector is Empty");
}

/*
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
}*/

template<typename value_type>
void Vector<value_type>::Clear()
{
	ASSERT_OK;
	if (!IsEmpty())
	{
		for (Vector<value_type>::Iterator it = Begin(); it != End();it++)
		{
			data_[it] = NULL;		//???????????????????
		}
		data_ = nullptr;
		size_ = 0;
		//capacity_ оставляем без изменений

	}
	else
	{
		throw std::exception("Vector is Empty");
	}
	
}

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
	//std::time_t result = std::time(NULL);
	//dumpfile << std::asctime(std::localtime(&result));
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

template<typename value_type>
void *Vector<value_type>::operator new(size_t size)
{
	return ::operator new(size);
}

template<typename value_type>
void* Vector<value_type>::operator new(size_t size, void* ptr)
{

	return ptr;
}

/*


class BitVal
{
	size_t num;
	size_t *val;
public:
	operator bool()
	{
		return *val & (1 << num);
	}
	BitVal(size_t &v, size_t n)
	{
		val = &v;
		num = n;
	}
	bool operator=(const bool fl)
	{
		if (fl)
			*val |= 1 << num;
		else
			*val &= ~(1 << num);
	}
};




template<>
class Vector<bool>
{
public:


	void *operator new(size_t size);
	void *operator new(size_t size, void* ptr);


	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Default constructor
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-------------------------------
	Vector();

	//----------------------------------------------------------------
	//! Consturctor with parameter
	//!
	//! @param size Size of Vector data array
	//----------------------------------------------------------------
	Vector(size_t size);

	//----------------------------------------------------------------
	//! Consturctor with 2 parameters
	//!
	//! @param size Size of Vector data array
	//! 
	//! @param value Value of all the cells
	//----------------------------------------------------------------
	Vector(size_t size, const bool value);

	//----------------------------------------------------------------
	//! Copy constructor
	//!
	//! @param that const lvalue reference to the object
	//----------------------------------------------------------------
	Vector(const Vector &that);

	//----------------------------------------------------------------
	//! Move constructor
	//!
	//! @param that rvalue reference to the object
	//----------------------------------------------------------------
	Vector(Vector &&that);

	//----------------------------------------------------------------
	//! Destructor
	//----------------------------------------------------------------
	~Vector();

	//----------------------------------------------------------------
	//! Copy assignment
	//!
	//! @param another lvalue reference to the object
	//!
	//! @return lvalue reference to this object
	//----------------------------------------------------------------
	Vector &operator=(Vector &another);

	//----------------------------------------------------------------
	//! Move assignment
	//!
	//! @param another rvalue reference to the object
	//!
	//! @return lvalue reference to this object
	//----------------------------------------------------------------
	Vector &operator=(Vector &&another);

	//----------------------------------
	//! Overload of operator[]
	//----------------------------------
	BitVal& operator[] (int index);


	void PushBack(const bool value);
	void PopBack();

	//	void Resize(size_t size);
	//	void Reserve(size_t capacity);



	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Size of data block
	//!
	//! @return size of data block
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	size_t Size() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Capacity of data block
	//!
	//! @return capacity of data block
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	size_t Capacity() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Checks Vector for emptyness
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	bool IsEmpty() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Silent verifier
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	bool Ok() const;

	//----------------------------------------------------------------
	//! Dumper
	//----------------------------------------------------------------
	void Dump(std::string a) const;

	/*
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
	//! Overload of operator ==
	//----------------------------------
	bool operator==(Vector& that)
	{
		if (size_ != that.size_)
			return false;
		for (size_t i = 0; i < size_; ++i)
			if (data_[i] != that.data_[i])
				return false;
		return true;
	}
	
private:
	size_t size_;
	size_t capacity_;
	size_t* data_;

	const size_t bit_ammount = 8 * sizeof(size_t);

	void Reserve();
};


Vector<bool>::Vector() :
	size_(0), capacity_(0), data_(nullptr) {}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

Vector<bool>::Vector(size_t size) :
	size_(size), capacity_(size), data_(new size_t[(size - 1) / bit_ammount + 1])
{
	memset(data_, 0, sizeof(size_t) * (size - 1) / bit_ammount + 1);
}


Vector<bool>::Vector(size_t size, const bool value) :
	size_(size), capacity_(size), data_(new size_t[(size - 1) / bit_ammount + 1])
{
	int count = (size - 1) / bit_ammount + 1;
	for (int i = 0; i < count; ++i)
		data_[i] = value;
}


Vector<bool>::Vector(const Vector<bool> &that) :
	size_(that.size_), capacity_(that.capacity_), data_(new size_t[(that.capacity_ - 1) / bit_ammount + 1])
{
	ASSERT_OK;
	int count = (size_ - 1) / bit_ammount + 1;
	for (int i = 0; i < count; ++i)
		data_[i] = that.data_[i];
}


Vector<bool>::Vector(Vector<bool> &&that) :
	size_(that.size_), capacity_(that.capacity_), data_(that.data_)
{
	ASSERT_OK;
	that.data_ = nullptr;
}


BitVal& Vector<bool>::operator[] (int index)
{
	ASSERT_OK;
	if (index < 0 || index >= size_)
		throw std::exception("Invalid index!");
	return BitVal(data_[index / bit_ammount], index%bit_ammount);
}


Vector<bool> &Vector<bool>::operator=(Vector<bool> &another)
{
	ASSERT_OK;
	if (this != &another)
	{
		size_ = another.size_;
		capacity_ = another.capacity_;
		size_t count = (capacity_ - 1) / bit_ammount + 1;
		data_ = new size_t[count];
		for (int i = 0; i < count; ++i)
			data_[i] = another.data_[i];
	}
	ASSERT_OK;
	return *this;
}


Vector<bool> &Vector<bool>::operator=(Vector<bool> &&another)
{
	ASSERT_OK;
	if (this != &another)
	{
		size_ = another.size_;
		capacity_ = another.capacity_;
		data_ = another.data_;
		another.data_ = nullptr;
	}
	ASSERT_OK;
	return *this;
}


void Vector<bool>::PushBack(const bool value)
{
	ASSERT_OK;
	if (size_ == capacity_)
		Reserve();
	if (value)
		data_[(size_) / bit_ammount] |= 1 << (size_%bit_ammount);
	else
		data_[(size_) / bit_ammount] &= ~(1 << (size_%bit_ammount));
	++size_;
	ASSERT_OK;
}

template<typename value_type>
void Vector<value_type>::PopBack()
{
	ASSERT_OK;
	if (size_ == 0)
		throw std::exception("Vector is empty!");
	--size;
	data_[(size_) / bit_ammount] &= ~(1 << (size_%bit_ammount));
	ASSERT_OK;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Vector<value_type>::Ok() const
{
	return size_ <= capacity_;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Vector<value_type>::~Vector()
{
	if (data_)
		delete[] data_;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Vector<value_type>::IsEmpty() const
{
	ASSERT_OK;
	return size_ == 0;
}

template<typename value_type>
size_t Vector<value_type>::Size() const
{
	ASSERT_OK;
	return size_;
}

template<typename value_type>
size_t Vector<value_type>::Capacity() const
{
	ASSERT_OK;
	return capacity_;
}

template<typename value_type>
void Vector<value_type>::Reserve()
{
	ASSERT_OK;
	size_t new_cap((size_t)(capacity_ * 1.618));
	if (new_cap == capacity_)
		++new_cap;
	value_type *tmp = new value_type[new_cap];
	capacity_ = new_cap;
	for (size_t i = 0; i < size_; ++i)
		tmp[i] = data_[i];
	memset(tmp + size_, 0, sizeof(value_type) * (capacity_ - size_));
	delete[] data_;
	data_ = tmp;
	ASSERT_OK;
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
	//dumpfile << std::asctime(std::localtime(&result));
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

template<typename value_type>
void *Vector<value_type>::operator new(size_t size)
{
	return ::operator new(size);
}

template<typename value_type>
void* Vector<value_type>::operator new(size_t size, void* ptr)
{

	return ptr;
}*/