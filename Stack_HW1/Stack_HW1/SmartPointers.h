#pragma once

#include "Header.h"

template<typename value_type>
class shared_ptr
{
	value_type *ptr_;
};

template<typename value_type>
class auto_ptr
{
	value_type *ptr_;
public:
	auto_ptr() : ptr_(nullptr) {}
	auto_ptr(value_type *ptr) : ptr_(ptr) {}
	auto_ptr(auto_ptr &that) : ptr_(that.ptr_)
	{
		that.ptr_ = nullptr;
	}
	~auto_ptr()
	{
		if (ptr_)
			delete ptr_;
	}
	value_type &operator*()
	{
		if (!ptr_)
			throw std::exception("auto_ptr is failed!");
		return *ptr_;
	}
	value_type *operator->()
	{
		if (!ptr_)
			throw std::exception("auto_ptr is failed!");
		return ptr_;
	}
	auto_ptr &operator=(value_type *ptr)
	{
		if (ptr_)
			delete ptr_;
		ptr_ = ptr;
		return *this;
	}
	auto_ptr &operator=(auto_ptr &that)
	{
		if (ptr_)
			delete ptr_;
		ptr_ = that.ptr_;
		that.ptr_ = nullptr;
		return *this;
	}
	bool operator<(const auto_ptr &right)
	{
		return ptr_ < right.ptr_;
	}
	operator int()
	{
		return (int)ptr_;
	}
};