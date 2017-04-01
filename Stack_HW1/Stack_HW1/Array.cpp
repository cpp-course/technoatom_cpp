#define _CRT_SECURE_NO_WARNINGS
#include "Array.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

// FIXME: Используй кодировку utf-8, а не что-то странное, что не поддерживается гитхабом.

Array::Array()
{
	size_ = 0;
	// FIXME: data_[i] имеет тип float, а ты инициализируешь его POISON_INT. Да еще и не видишь варнингов на этот счет,
	// так как написал CTR_SECURE_NO_WARNINGS.
	for (size_t i = 0;i < capacity_; i++) data_[i] = POISON_INT;
}

bool Array::Ok() const
{
	// FYI: функция должна вернуть что-то в любом случае. Здесь это так, но лучше не прятать хотя бы один return под
	// условный оператор.
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
	// FIXME: почему ты не пользуешься своим макросом ASSERT_OK? Зачем ты пишешь имя функции явно, если можно написать
	// PRETTY_FUNCTION. А еще полезно __LINE__ и __FILE__
	Dump("First()");
	if ((!IsEmpty()) && (Ok())) return data_[0];
	else return POISON_VAL;		//åñëè value_type íå float, òî ïîëîìàåòñÿ
	// FIXME: Очень странная мысль - возвращать яд. А если нормальное число, Лежащшее в массиве равно яду?
	// А может лучше вообще проверить ошибку ассертом или же кинуть исключение?
}

Array::value_type Array::Last() const
{
	Dump("Last()");
	if ((!IsEmpty()) && (Ok())) return data_[size_-1];
	else return POISON_VAL;		//åñëè value_type íå float, òî ïîëîìàåòñÿ
}

bool Array::Insert(Array::value_type data)
{
	// FIXME: хочется читать функцию и видеть неоступленным основное тело функцииЮ, а отступленным код,
	// обрабатывающий ошибки. Ну, типа, if (error) { ... return false; }
	// А дальше - тело функции.
	Dump("Insert()");
	if (size_ < capacity_)
	{
		data_[size_] = data;
		size_++;
		return true;
	}
	else
	{
		// FIXME: При каждом вызове функции открывать файл - дорого. А еще, что будет, если файл не откроется? 
		// такое бывает и это надо проверять. А вдруг твоя программа запущена где-то, где нету жесткого диска?
		// В памяти видеокарты напирмер? Чтобы написать более общий код, обычно пишуть библиотеку с функцией LOG_PRINT
		// или что-то типа того. Либо макрос LOG_PRINT. И используют для вывода сообщений только этот макрос. Тогда
		// при необходимости придется изменять только одно место, а не перелопачивать всю программу.
		std::ofstream dumpfile("dump.txt", std::ios_base::app);
		dumpfile << "ARRAY IS FULL!!!\nCan not Insert element!\n";
		dumpfile.close();
		return false;
	}
}

bool Array::Erase(size_t index)
{
	// FIXME: для пустого массива эта функция отработает некорректно. size_ - 1 всегда будет больше, чем index, ибо -1 - самое большое положительное число.
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
