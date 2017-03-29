#pragma once

#include "Vector.h"

template<typename value_type>
void swap(value_type &some1, value_type &some2)
{
	value_type some3 = some1;
	some1 = some2;
	some2 = some3;
}


template<typename value_type>
void sort(Vector<value_type> &some)
{
	size_t size = some.Size();
	for (size_t i = 0; i < size; ++i)
	{
		value_type tmp = some[i]; // here
		for (size_t j = i+1; j < size; ++j)
			if (some[j] < tmp)
			{
				swap(some[j], some[i]);
				tmp = some[i];		// and here
			}
	}
}
