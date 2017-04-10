//------------------------------
//! @file MyTranslator.h
//! Translates scripts to bitecode
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//------------------------------

#include<fstream>
#include<exception>
#include<fstream>
#include"MyException.h"
#include<string>


enum ComCode
{
	PUSH, PUSH1,
	POP,
	ADD, SUB,
	MUL, DIV,
	CALL, RET,
	JMP, JE, JA, JB, JAE, JBE, JNE
};


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
	const char *StrToComCode(std::string);
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
	char *str;
	int index;
	while (!fin.eof())
	{
		fin >> str;
		if (*str == ':')
			if (0 <= (index = atoi(str + 1)) && index < max_label_)
				label_[index] = counter;
			else
				throw MyException(3, "Wrong label", __FILE__, __LINE__);
		else
			++counter;
	}
	fin.close();
}

const char *Translator::StrToComCode(std::string buff)
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
				return ((std::string)"9" + itoa(label_[index], tmp, 10) + '\n').c_str();
			throw MyException(3, "Wrong label", __FILE__, __LINE__);
		}
		if (sub == "je ")
		{
			index = atoi(buff.substr(3).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"A" + itoa(label_[index], tmp, 10) + '\n').c_str();
			throw MyException(3, "Wrong label", __FILE__, __LINE__);
		}
		if (sub == "ja ")
		{
			index = atoi(buff.substr(3).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"B" + itoa(label_[index], tmp, 10) + '\n').c_str();
			throw MyException(3, "Wrong label", __FILE__, __LINE__);
		}
		if (sub == "jb ")
		{
			index = atoi(buff.substr(3).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"C" + itoa(label_[index], tmp, 10) + '\n').c_str();
			throw MyException(3, "Wrong label", __FILE__, __LINE__);
		}
		if (sub == "jae")
		{
			index = atoi(buff.substr(4).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"D" + itoa(label_[index], tmp, 10) + '\n').c_str();
			throw MyException(3, "Wrong label", __FILE__, __LINE__);
		}
		if (sub == "jbe")
		{
			index = atoi(buff.substr(4).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"E" + itoa(label_[index], tmp, 10) + '\n').c_str();
			throw MyException(3, "Wrong label", __FILE__, __LINE__);
		}
		if (sub == "jne")
		{
			index = atoi(buff.substr(4).c_str());
			if (0 <= index && index < max_label_ && label_[index] != -1)
				return ((std::string)"F" + itoa(label_[index], tmp, 10) + '\n').c_str();
			throw MyException(3, "Wrong label", __FILE__, __LINE__);
		}
		throw MyException(4, "Wrong command", __FILE__, __LINE__);
	}
	if (buff.substr(0, 4) == "push")
	{
		if ()
	}
}


//------------------------------
//! void to translate commands from scripts
//------------------------------
void Translator::SecondIter()
{
	char *buff;
	std::ifstream fin(input_);
	std::ofstream fout(output_);
	if (!fin.is_open() || !fout.is_open())
		throw MyException(2, "Cannot open file", __FILE__, __LINE__);
	while (!fin.eof())
	{
		fin >> buff;
		StrToComCode(buff);
		
	}

}