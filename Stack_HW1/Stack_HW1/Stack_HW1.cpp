#define _CRT_SECURE_NO_WARNINGS

#include "Stack_HW1.h"

std::exception is_empty("Vector is empty!");

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack() : size_(0), data_(new data_type()) {}
	
//=======================================================
// new
// квадратные скобки -- для создания массива
// круглые скобки -- для вызова конструктора
// 
// если память не выделится, new выбросит исключение
//
// вызывается конструктор Vector<value_type>(size_t Size),
// и он делает все остальное
//=======================================================

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack(size_t capacity) : size_(0), data_(new data_type(capacity)) {}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack(const Stack<value_type> &that) : size_(that.size_), data_(new data_type(that.data_))
{
	ASSERT_OK;
}
//=======================================================================================
// вызывается конструктор копирования Vector<value_type>(const Vector<value_type> &that)
// и копирует все содержимое that.data_ в this->data_
//=======================================================================================

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
Stack<value_type>::Stack(Stack<value_type> &&that) : size_(that.size_), data_(that.data_)
{
	ASSERT_OK;
	that.data_ = nullptr;
//=======================================================================================
// здесь ничего не копируется, просто перемещается
// that.data_ = nullptr и теперь в деструкторе that нам уже нельзя удалять data_,
// поэтому надо проверять
//=======================================================================================
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
								// но это не точно
	}
	ASSERT_OK;
	return *this;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Stack<value_type>::Push(value_type value)
{
	ASSERT_OK;
	if (size_ == data_->capacity_)
		data_->Expand();
	data_[size_++] = value;
	ASSERT_OK;

}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Stack<value_type>::Pop()
{
	ASSERT_OK;
	if (IsEmpty())
		throw is_empty;
	//data_[--size_] = POISON_VAL;
	--size_;
	ASSERT_OK;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
value_type Stack<value_type>::Top() const
{
	ASSERT_OK;
	if (IsEmpty())
		throw is_empty;
	return data_[size_ - 1];
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
size_t Stack<value_type>::Size() const
{
	ASSERT_OK;
	return size_;
}


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//======================================
// возможно, это не нужно
//======================================
template<typename value_type>
size_t Stack<value_type>::Capacity() const
{
	ASSERT_OK;
	return data_->capacity_;
}



//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
bool Stack<value_type>::IsEmpty() const
{
	ASSERT_OK;
	return size_ == 0;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//======================================
// size_ беззнаковая переменная
// всегда >= 0
//======================================
template<typename value_type>
bool Stack<value_type>::Ok() const
{
	return size_ <= data_->capacity_
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
template<typename value_type>
void Stack<value_type>::Dump() const
{
	std::ofstream dumpfile("Dump.txt", std::ios_base::app);
	if (!dumpfile.is_open())
	{
		printf("Cannot open Dump.txt");
		return;
	}
	dumpfile << "--------------------------------------------------------------\nNew call of Dump()\n";
	std::time_t result = std::time(NULL);
	dumpfile << std::asctime(std::localtime(&result));
	dumpfile << "\n\n";
	dumpfile << "Stack " << " ok(" << Ok() << ")\n";
	dumpfile << "size_ = " << size_ << "\n";
	dumpfile << "capacity_ = " << capacity_ << "\n";
	dumpfile << "data [" << capacity_ << "]:";
	dumpfile << "{\n";
	for (size_t i = 0; i < capacity_; i++)
	{
		dumpfile << "[" << i << "] = " << data_[i] << "\n";
	}
	dumpfile << "}\n";
	dumpfile.close();
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐