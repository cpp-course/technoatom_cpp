//------------------------------
//! @file MyTranslator.h
//! Translates scripts to bitecode
//! @author Pasha2La
//! @author Kirill Shirokov
//! @data 2017
//------------------------------

#include<fstream>
#include<exception>
#include"MyException.h"

void SecondTranslation()
{
	std::ofstream scriptfile("script.txt");
	if (!scriptfile.is_open())
		throw;//????????????


}