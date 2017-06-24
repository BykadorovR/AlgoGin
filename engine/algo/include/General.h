#pragma once
#include "Defs.h"

template <class T>
class Container {
public:
	virtual T minimum() = 0;
	virtual T maximum() = 0;
	virtual l_sts insert(T value, int index) = 0;
	virtual l_sts remove(int index) = 0;
	virtual l_sts replace(int index, T value) = 0;
	virtual T operator[](int index) = 0;
	virtual int getSize() = 0;
};