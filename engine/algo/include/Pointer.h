#pragma once
#include <iostream>

//TODO: implement [] if real
template <class T>
class Unique_ptr {
private:
	
public:
	T* data;

	friend void swap(Unique_ptr<T>& first, Unique_ptr<T>& second) // nothrow
	{
		using std::swap;
		swap(first.data, second.data);
	}

	Unique_ptr() {
		data = new T();
	}
	
	Unique_ptr(Unique_ptr<T>&& right) {
		//just lets assign nullptr to rvalues not 0xCCCCCC and something like that
		data = nullptr;
		swap(*this, right);
	}

	~Unique_ptr() {
		delete data;
		data = nullptr;
	}
	Unique_ptr<T>& operator=(Unique_ptr<T> right) {
		swap(*this, right);
		return *this;
	}
	
	T* operator->() {
		//we want to return adress of data so in case of T - complex type with for example foo() method
		//we can use for our Unique_ptr<T> d; next code d->foo();
		return data;
	}

	T& operator*() {
		return *data;
	}
};