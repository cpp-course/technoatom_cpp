//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file main.cpp
//!
//! @author Pasha, 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#include "Vector.h"

#include "Stack_HW1.h"
/*
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! A unit‐test to Push() method of Stack
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// FIXME: Вот эти переносы строк, которые все с разными отступами где-то за границей экрана очень убого выглядят.

// FIXME: "Дефайны с тестами" означает не засунуть каждый тест в дефайн. В этом нету смысла. Имелось ввиду, что нужно сделать
// макрос типа ASSERT_EQ(a, b), который проверяет, что a == b и, если нет, пишет об этом. А тесты - это просто обычные функции.
// Посмотри, как принято писать тесты в документации к Google Test (gtest).

// Еще тестами обынчо покрывают все функции, которые есть в программе. Иначе можно упустить проблему.
// А еще часто тестят то, как функции обрабатывают ошибки. К примеру, если функциякидает исключения при ошибке - надо бы это
// проверить и проверить, что функция кинет именно то исключение, которое ты ожидаешь.

#define TEST_PUSH															\
		Stack* s1 = new Stack;												\
		s1->Push((Stack::value_type)1.1);									\
		if(s1->Top() == (Stack::value_type)1.1) printf("TEST_PUSH IS OK!"); \
		else																\
		{																	\
			s1->Dump();														\
			printf("TEST_PUSH FAILED!");									\
		}																	\

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! A unit‐test to Pop() method of Stack
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_POP									\
		Stack* s1 = new Stack;						\
		s1->Push((Stack::value_type)1.2);			\
		s1->Pop();									\
		if(s1->Empty()) printf("TEST_PUSH IS OK!"); \
		else										\
		{											\
			s1->Dump();								\
			printf("TEST_PUSH FAILED!");			\
		}											\

*/
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! main
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#include "MyPrint.h"
#include "SmartPointers.h"
#include "Sort.h"
#include <algorithm>
#include <vector>

#define TEST(what, func)								\
	if (!what)											\
		std::cout << #func" is failed!" << std::endl;	\
	else												\
		std::cout << #func" is OK!" << std::endl




void check_stack() {
	std::cout << "For Stack:\n";
	Stack<int> mystack;
	TEST(mystack.IsEmpty(), IsEmpty());
	for (int i = 0; i < 100; ++i)
		mystack.Push(i);
	TEST(mystack.Size() == 100, Size());
	mystack.Pop();
	TEST(mystack.Top() == 98, Top());
	std::cout << std::endl;
}

void check_vector()
{
	std::cout << "For Vector:\n";
	Vector<int> myvector;
	TEST(myvector.IsEmpty(), IsEmpty());
	for (int i = 0; i < 100; i++)
		myvector.PushBack(i);
	TEST(myvector.Size() == 100, Size());
	myvector.PopBack();
	TEST(myvector.Last() == 99, Last());
	TEST(myvector.First() == 0, First());
	std::cout << std::endl;
}

// FIXME: В тестах не нужно ничего выводить на экран, кроме названия теста. Напротив, надо все проверить автоматически.
void check_iterators()
{
	std::cout << "For Iterators:\n";
	Vector<int> myvector(20);
	srand(time(0));
	for (auto it = myvector.Begin(); it != myvector.End(); ++it)
		*it = rand() % 129;
	std::cout << "\nsort with std::sort\n";
	std::cout << "Before sort : ";
	for (auto it = myvector.Begin(); it != myvector.End(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	std::sort(myvector.Begin(), myvector.End());
	std::cout << "After sort : ";
	for (auto it = myvector.Begin(); it != myvector.End(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
	Vector<int> v2 = myvector; // copy constructor use iterators
	std::cout << "Copy : ";
	for (auto it = v2.Begin(); it != v2.End(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}

void check_shared_ptr()
{
	std::cout << "For shared_ptr:\n";

	std::cout << "\nsort for shared_ptr<int>\n";
	Vector<shared_ptr<int> > ptrVec(20);
	for (auto it = ptrVec.Begin(); it != ptrVec.End(); ++it)
		*it = new int(rand() % 129);

	std::cout << "Before sort : ";
	for (auto it = ptrVec.Begin(); it != ptrVec.End(); ++it)
		std::cout << **it << ' ';
	std::cout << std::endl;

	// try to sort
	sort(ptrVec);
	// try to print
	std::cout << "After sort : ";
	for (auto it = ptrVec.Begin(); it != ptrVec.End(); ++it)
		std::cout << **it << ' ';
	std::cout << std::endl;
	std::cout << "shared_ptr is OK!!!\n";
}

// FIXME: мне не кажется, что код ниже проверяет работоспособность auto_ptr. Надо проверить, что он передает владение и что объект
// действительно удаляется. Самый простой способ сделать это - переопределить оператор new, который будет записывать куда-нибудь,
// что выделилось, а что удалилось. А так - ты проверяешь не то, что умный указатель работает, а то, что что-то пошло не так.
void check_auto_ptr()
{
	std::cout << "For auto_ptr:\n";
	std::cout << "\nsort for int\n";
	Vector<int> v2(20);
	for (auto it = v2.Begin(); it != v2.End(); ++it)
		*it = rand() % 129;

	std::cout << "Before sort : ";
	for (auto it = v2.Begin(); it != v2.End(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	sort(v2);

	std::cout << "After sort : ";
	for (auto it = v2.Begin(); it != v2.End(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	std::cout << "\nsort for auto_ptr<int>\n";
	Vector<auto_ptr<int> > very_bad_thing(20);
	for (auto it = very_bad_thing.Begin(); it != very_bad_thing.End(); ++it)
		*it = new int(rand() % 129);

	std::cout << "Before sort : ";
	for (auto it = very_bad_thing.Begin(); it != very_bad_thing.End(); ++it)
		std::cout << **it << ' ';
	std::cout << std::endl;

	// try to sort
	sort(very_bad_thing);
	// here is it
	// try to print
	std::cout << "After sort : ";
	for (auto it = very_bad_thing.Begin(); it != very_bad_thing.End(); ++it)
		std::cout << **it << ' ';
	std::cout << std::endl;
	std::cout << "auto_ptr is OK!!!\n";
}

int main()
{
	try {
		check_stack();
		check_vector();
		check_iterators();
		check_shared_ptr();
		check_auto_ptr();
	}
	catch (std::exception exc) {
		std::cout << exc.what() << std::endl;
	}
	std::cin.ignore();
	return 0;
}
