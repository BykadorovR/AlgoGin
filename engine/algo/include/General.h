#pragma once
#include "Defs.h"

//This is super class for all non-sorted containers
template <class T>
class Container_ns {
public:
	virtual T minimum() = 0;
	virtual T maximum() = 0;
	virtual l_sts remove(int index) = 0;
	virtual l_sts insert(T value, int index) = 0;
	virtual l_sts push_back(T value) = 0;
	virtual l_sts push_start(T value) = 0;
	virtual l_sts pop_back() = 0;
	virtual l_sts pop_start() = 0;
	virtual T& operator[](int index) = 0;
	virtual int getSize() = 0;
};

//This is super class for all sorted containers
template <class T>
class Container_s {
public:
	virtual T minimum() = 0;
	virtual T maximum() = 0;
	virtual l_sts remove(int index) = 0;
	virtual l_sts insert(T value) = 0;
	virtual l_sts pop_back() = 0;
	virtual l_sts pop_start() = 0;
	virtual T operator[](int index) = 0;
	virtual int getSize() = 0;
};