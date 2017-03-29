#pragma once

#include "Header.h"

template<typename value_type>
class shared_ptr
{
	class Proxy
	{
		value_type *ptr_;
		size_t counter_;
	public:
		Proxy(value_type *ptr) : ptr_(ptr), counter_(1) {}
		~Proxy()
		{
			if (ptr_)
				delete ptr_;
		}
		value_type *GetPtr()
		{
			return ptr_;
		}
		size_t &GetAmmount()
		{
			return counter_;
		}
	};
	Proxy *proxy_ptr_;
public:
	shared_ptr() : proxy_ptr_(nullptr) {}
	shared_ptr(value_type *ptr) : proxy_ptr_(new Proxy(ptr)) {}
	shared_ptr(const shared_ptr &that) : proxy_ptr_(that.proxy_ptr_)
	{
		++proxy_ptr_->GetAmmount();
	}
	~shared_ptr()
	{
		if (proxy_ptr_ && --proxy_ptr_->GetAmmount() == 0)
			delete proxy_ptr_;
	}
	value_type &operator*() const
	{
		if (!proxy_ptr_ || !proxy_ptr_->GetPtr())
			throw std::exception("shared_ptr is failed in operator*!");
		return *proxy_ptr_->GetPtr();
	}
	value_type *operator->()
	{
		if (!proxy_ptr_ || !proxy_ptr_->GetPtr())
			throw std::exception("shared_ptr is failed in operator->!");
		return proxy_ptr_->GetPtr();
	}
	shared_ptr &operator=(value_type *ptr)
	{
		if (proxy_ptr_ && --proxy_ptr_->GetAmmount() == 0)
			delete proxy_ptr_;
		proxy_ptr_ = new Proxy(ptr);
		return *this;
	}
	shared_ptr &operator=(const shared_ptr &that)
	{
		if (proxy_ptr_ && --proxy_ptr_->GetAmmount() == 0)
			delete proxy_ptr_;
		++(proxy_ptr_ = that.proxy_ptr_)->GetAmmount();
		return *this;
	}
	bool operator<(const shared_ptr &right)
	{
		return **this < *right;
	}
	operator int()
	{
		return (int)proxy_ptr_->GetPtr();
	}
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
			throw std::exception("auto_ptr is failed in operator*!");
		return *ptr_;
	}
	value_type *operator->()
	{
		if (!ptr_)
			throw std::exception("auto_ptr is failed in operator->!");
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