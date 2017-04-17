//------------------------------
//! @file MyTranslator.h
//! Translates scripts to bitecode
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//------------------------------
#pragma once

#include "Header.h"
#include"MyException.h"


class Translator
{
public:
	Translator(const char *in, const char *out) : input_(in), output_(out)
	{
		memset(label_, -1, max_label_ * sizeof(int));
	}
	//------------------------------
	//! void to make translation
	//------------------------------
	void Make() { FirstIter(); SecondIter(); }

private:
	static const int max_label_ = 100;
	const char* input_;
	const char* output_;
	int label_[max_label_];
	std::string StrToComCode(std::string);
	//------------------------------
	//! makes first translation and fills array of labels
	//------------------------------
	inline void FirstIter();
	//------------------------------
	//! makes second translation creates file with script to CPU
	//------------------------------
	inline void SecondIter();
};



void Translator::FirstIter()
{
	std::ifstream fin(input_);
	if (!fin.is_open())
		throw MyException(2, "Cannot open file", __FILE__, __LINE__);
	size_t counter = 0;
	std::string str;
	int index;
	while (!fin.eof())
	{
		fin >> str;
		if (str[0] == ':')
			if (0 <= (index = atoi(str.c_str() + 1)) && index < max_label_)
				label_[index] = counter;
			else
				throw MyException(3, "Wrong argument", __FILE__, __LINE__);
		else
			++counter;
	}
	fin.close();
}

std::string Translator::StrToComCode(std::string buff)
{
	size_t len = buff.length();
	if (len <= 3)
	{
		if (buff == "add")
			return "3\n";
		if (buff == "sub")
			return "4\n";
		if (buff == "mul")
			return "5\n";
		if (buff == "div")
			return "6\n";
		if (buff == "ret")
			return "8\n";
		throw MyException(4, "Wrong command", __FILE__, __LINE__);
	}
	if (buff[0] == 'j')
	{
		int index;
		char *tmp;
		std::string sub = buff.substr(0, 3);
		if (sub == "jmp")
		{
			index = atoi(buff.substr(4).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"9" + myitoa(label_[index]) + '\n');
			throw MyException(3, "Wrong argument", __FILE__, __LINE__);
		}
		if (sub == "je ")
		{
			index = atoi(buff.substr(3).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"a" + myitoa(label_[index]) + '\n');
			throw MyException(3, "Wrong argument", __FILE__, __LINE__);
		}
		if (sub == "ja ")
		{
			index = atoi(buff.substr(3).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"b" + myitoa(label_[index]) + '\n');
			throw MyException(3, "Wrong argument", __FILE__, __LINE__);
		}
		if (sub == "jb ")
		{
			index = atoi(buff.substr(3).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"c" + myitoa(label_[index]) + '\n');
			throw MyException(3, "Wrong argument", __FILE__, __LINE__);
		}
		if (sub == "jae")
		{
			index = atoi(buff.substr(4).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"d" + myitoa(label_[index]) + '\n');
			throw MyException(3, "Wrong argument", __FILE__, __LINE__);
		}
		if (sub == "jbe")
		{
			index = atoi(buff.substr(4).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"e" + myitoa(label_[index]) + '\n');
			throw MyException(3, "Wrong argument", __FILE__, __LINE__);
		}
		if (sub == "jne")
		{
			index = atoi(buff.substr(4).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"f" + myitoa(label_[index]) + '\n');
			throw MyException(3, "Wrong argument", __FILE__, __LINE__);
		}
		throw MyException(4, "Wrong command", __FILE__, __LINE__);
	}
	if (buff.substr(0, 4) == "call")
	{
		char *tmp;
		int index = atoi(buff.substr(5).c_str());
		if (0 <= index && index < max_label_ && label_[index] != -1)
			return ((std::string)"7" + myitoa(label_[index]) + '\n');
		throw MyException(3, "Wrong argument", __FILE__, __LINE__);
	}
	if (buff.substr(0, 3) == "pop")
	{
		//корректность номера регистра остается на совести автора скрипта
		//потому что мы не знаем, сколько их в процессоре
		return ((std::string)"2" + buff.substr(5) + '\n');
	}
	if (buff.substr(0, 4) == "push")
	{
		if (buff.substr(5, 1) == "x")
			//корректность номера регистра остается на совести автора скрипта
			//потому что мы не знаем, сколько их в процессоре
			return ((std::string)"1" + buff.substr(6) + '\n');
		else
		{
			return ((std::string)"0" + buff.substr(5) + '\n');
		}
		throw MyException(3, "Wrong argument", __FILE__, __LINE__);
	}
	throw MyException(4, "Wrong command", __FILE__, __LINE__);
}


void Translator::SecondIter()
{
	std::string buff;
	std::ifstream fin(input_);
	std::ofstream fout(output_);
	if (!fin.is_open() || !fout.is_open())
		throw MyException(2, "Cannot open file", __FILE__, __LINE__);
	std::string lstr;
	while (!fin.eof())
	{
		std::getline(fin, buff);
		if (buff[0] != ':') {
			lstr = StrToComCode(buff);
			fout << lstr;
		}
	}
	fin.close();
	fout.close();
}