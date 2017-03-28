#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cassert>
#include <string>
#include <exception>
#include <cstdlib>


//#define POISON_VAL 0xDEADDEAD
//#define POISON_INT 100500

//----------------------------------------------------------------
//! Macro to test object integrity
//----------------------------------------------------------------
#define ASSERT_OK					\
	if (!Ok())						\
	{								\
		Dump("");						\
		assert(!"stack is ok");		\
	}
