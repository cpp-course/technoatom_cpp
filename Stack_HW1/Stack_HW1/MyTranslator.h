//------------------------------
//! @file MyTranslator.h
//! Translates scripts to bitecode
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//------------------------------

#include<fstream>
#include<exception>
#include<iostream>
#include"MyException.h"
#include<string>

//------------------------------
//! void to translate commands from scripts
//------------------------------
void SecondTranslation()
{
	std::string buff;
	std::ifstream scriptfile("script.txt");
	std::ofstream bitecode("bitecode.txt");
	if (!scriptfile.is_open())
		throw;//????????????
	if (!bitecode.is_open())
		throw;//????????????
	while (!scriptfile.eof())
	{
		scriptfile >> buff;
		
	}

}