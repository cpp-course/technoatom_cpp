
#define _CRT_SECURE_NO_WARNINGS
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file Stack_HW1.h
//! Implements a stack class
//!
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐


#include "Vector.h"


//----------------------------------
//! Stack class
//----------------------------------
template <typename value_type>
class Stack
{
public:

	typedef Vector<value_type> data_type;	//!< Type of data block	

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Default constructor
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐-------------------------------
	Stack();

	//----------------------------------------------------------------
	//! Consturctor with parameter
	//!
	//! @param capacity Size of stack data array
	//----------------------------------------------------------------
	Stack(size_t capacity);

	//----------------------------------------------------------------
	//! Copy constructor
	//!
	//! @param that const lvalue reference to the object
	//----------------------------------------------------------------
	Stack(const Stack &that);

	//----------------------------------------------------------------
	//! Move constructor
	//!
	//! @param that rvalue reference to the object
	//----------------------------------------------------------------
	Stack(Stack &&that);

	//----------------------------------------------------------------
	//! Destructor
	//----------------------------------------------------------------
	~Stack();

	//----------------------------------------------------------------
	//! Copy assignment
	//!
	//! @param another lvalue reference to the object
	//!
	//! @return lvalue reference to this object
	//----------------------------------------------------------------
	Stack &operator=(Stack &another);

	//----------------------------------------------------------------
	//! Move assignment
	//!
	//! @param another rvalue reference to the object
	//!
	//! @return lvalue reference to this object
	//----------------------------------------------------------------
	Stack &operator=(Stack &&another);

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Pushes a value to the stack
	//!
	//! @param value is an element to be pushed
	//!
	//! @return success of operation
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	void Push(value_type value);

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Deletes top value from the stack
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	void Pop();

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Top element of the stack
	//!
	//! @return top element
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	value_type Top() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Size of the stack
	//!
	//! @return ammount of elements in stack
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	size_t Size() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Capacity of data block
	//!
	//! @return capacity of data block
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------

	//size_t Capacity() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Checks Stack for emptyness
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	bool IsEmpty() const;

	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	//! Silent verifier
	//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐------------------------------
	bool Ok() const;

	//----------------------------------------------------------------
	//! Dumper
	//----------------------------------------------------------------
	void Dump(const char*) const;

private:
	data_type* data_;				//!< Data block
	size_t size_;					//!< Ammount of elements in stack
};

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack() : size_(0), data_(new data_type()) {}


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack(size_t capacity) : size_(0), data_(new data_type(capacity)) {}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack(const Stack<value_type> &that) : size_(that.size_), data_(new data_type(that.data_))
{
	ASSERT_OK;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack(Stack<value_type> &&that) : size_(that.size_), data_(that.data_)
{
	ASSERT_OK;
	that.data_ = nullptr;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::~Stack()
{
	if (data_)
		delete data_;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type> &Stack<value_type>::operator=(Stack<value_type> &another)
{
	ASSERT_OK;
	if (this != &another)
	{
		size_ = another.size_;
		*data_ = *another.data_; // присваивание копии (Vector::operator=(Vector &another))
	}
	ASSERT_OK;
	return *this;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type> &Stack<value_type>::operator=(Stack<value_type> &&another)
{
	ASSERT_OK;
	if (this != &another)
	{
		size_ = another.size_;
		*data_ = *another.data_; // присваивание перемещения (Vector::operator=(Vector &&another))
	}
	ASSERT_OK;
	return *this;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Stack<value_type>::Push(value_type value)
{
	ASSERT_OK;
	data_->PushBack(value);
	++size_;
	ASSERT_OK;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Stack<value_type>::Pop()
{
	ASSERT_OK;
	if (IsEmpty())
		throw std::exception("Stack is empty!");
	data_->PopBack();
	--size_;
	ASSERT_OK;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
value_type Stack<value_type>::Top() const
{
	ASSERT_OK;
	if (IsEmpty())
		throw std::exception("Stack is empty!");
	return (*data_)[size_ - 1];
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
bool Stack<value_type>::IsEmpty() const
{
	ASSERT_OK;
	return size_ == 0;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Stack<value_type>::Ok() const
{
	return size_ <= data_->Capacity();
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Stack<value_type>::Dump(const char* qwe) const
{
	std::ofstream dumpfile("Dump.txt", std::ios_base::app);
	if (!dumpfile.is_open())
	{
		printf("Cannot open Dump.txt");
		return;
	}
	dumpfile << "--------------------------------------------------------------\nNew call of Dump()\n";
	//std::time_t result = std::time(NULL);
	//dumpfile << std::asctime(std::localtime(&result));
	dumpfile << "\n";
	dumpfile << "Stack " << " ok(" << Ok() << ")\n";
	dumpfile << "size_ = " << size_ << "\n";
	dumpfile << "capacity_ = " << data_->Capacity() << "\n";
	dumpfile << "data [" << data_->Capacity() << "]:";
	dumpfile << "{\n";
	for (size_t i = 0; i < size_; i++)
	{
		dumpfile << "[" << i << "] = " << (*data_)[i] << "\n";
	}
	dumpfile << "}\n";
	dumpfile.close();
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
