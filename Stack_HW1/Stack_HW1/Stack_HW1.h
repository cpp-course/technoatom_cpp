//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file Stack_HW1.h
//! Implements a stack class
//!
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#pragma once

#include "Vector.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <assert.h>
#include <exception>

//----------------------------------------------------------------
//! Macro to test object integrity
//----------------------------------------------------------------
#define ASSERT_OK					\
	if (!Ok())						\
	{								\
		Dump();						\
		assert(!"stack is ok");		\
	}


//=================================================
//#define POISON_VAL 0xDEADDEAD  // Не очень хорошо
//=================================================


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
	bool Push(value_type value);

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
	size_t Capacity() const;

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
	void Dump() const;

private:
	data_type* data_;				//!< Data block
	size_t size_;					//!< Ammount of elements in stack
};
