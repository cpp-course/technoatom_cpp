#define _CRT_SECURE_NO_WARNINGS // FIXME: Зачем это NO_WARNINGS? Warning-и помогают находить ошибку. Не надо их отключать.
// FIXME: включение всех хедеров там. где это не нужно замедляет компиляцию. Не надо так делать.
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cassert>
#include <string>
#include <exception>
#include <cstdlib>

// FIXME: Не оставляй в проекте ненужный закомменченый код
//#define POISON_VAL 0xDEADDEAD
//#define POISON_INT 100500

// FIXME: уже много раз говорил при разборе кода после лекций.
// 1) представь себе код if(aaa) ASSERT_OK else bbb(); И вот вопрос, когда сработает else?
// 2) Если у тебя ASSERT_OK добавляет overhead всегда - это неправильно. Ассерт нужен, чтобы проверять те ошибки,
// которые можно отдебажить в дебаг режиме, а в релиз-режиме не тратиить на них время. Если ошибки нужно проверять всегда -
// для этого можно написать макрос CHECK, которы будет делать exit или же кидать иключения. Причем
// в дебаг режиме он будет завершать программу с ошибкой, а в релизе - просто ее игнорировать,
// вызывая дамп. 
// 3) Куча обсуждений этой проблемы тут http://stackoverflow.com/questions/1067226/c-multi-line-macro-do-while0-vs-scope-block
//----------------------------------------------------------------
//! Macro to test object integrity
//----------------------------------------------------------------
#define ASSERT_OK					\
	if (!Ok())						\
	{								\
		Dump("");						\
		assert(!"stack is ok");		\
	}
