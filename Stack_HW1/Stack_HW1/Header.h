#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cassert>
#include <string>
#include <exception>
#include <cstdlib>

//----------------------------------------------------------------
//! Macro to test object integrity
//----------------------------------------------------------------
#define ASSERT_OK					\
	if (!Ok())						\
	{								\
		Dump("");					\
		assert(!"stack is ok");		\
	}

