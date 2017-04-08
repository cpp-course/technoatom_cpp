#pragma once

// FIXME: а еще, не выносить реализации функций в отдельный файл - это плохо. Загромождает header и мешает читать документацию.

#include "Header.h"
// FIXME: про то, что перечислять все хедеры в Header.h - это не лучшая идея - уже писал в другом файле. Здесь ты не используешь
// ничего из Header.h вообще
// Кстати, надо явно задокументировать, что твой указатель не поддерживает массивы в отличии от стандартных умных указателей.
// Ну или поддержать масивы.
// А еще хочется константных умных указателей.
// FIXME: И не надо использовать std::exception. Есть специализированые кастомные исключения. А лучше вообще сделать несколько своих.
template<typename value_type>
class shared_ptr
{
	// FIXME: лучше сначала писать публичную часть интерфейса. И документировать ее. Так будет понятнее, что к чему.
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
	// FIXME: я уже где-то объяснял, почему не надо использовать new в списке инициализации.
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
	// FIXME: Ты сделал этот метод const, но он возвращает неконстантную ссылку. Это логическая ошибка наподобии тех, о
	// которых я говорил после лекции.
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
		// FIXME: что такое **this? Не роняет программу случайно? Если нет - тебе просто повезло, что ptr лежит вначале объекта.
		// но это не всегда так.
		return **this < *right;
	}
	// FIXME: я бы побоялся делать такой оператор. Во-первых, sizeof(int) < sizeof(void*). Это исправляется использованием size_t
	// А во-вторых, этот оператор может быть вызван неявно, к примеру, при передаче в функцию, которая ожидает число.
	// Поэтому обязательно надо делать такие операторы explicit. Скорее всего ты сделал этот оператор с целью вычитать
	// указатели друг-из-друга. Но в таком случае лучше определить оператор -.
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
