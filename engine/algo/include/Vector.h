#pragma once
#include "Defs.h"
#include "General.h"

template <class T>
class Vector : public Container_ns<T> {
 protected:
	T* data;
	int general_size;
	l_sts shift_r(int index) {
		int value = 0;
		for (int i = index; i < this->general_size + 1; i++) {
			T tmp_val = this->data[i];
			this->data[i] = value;
			value = tmp_val;
		}
		return SUCCESS;
	}
	l_sts shift_l(int index) {
		for (int i = index + 1; i < this->general_size; i++) {
			T tmp_val = this->data[i];
			this->data[i - 1] = tmp_val;
		}
		return SUCCESS;
	}
 public:
	Vector(int _general_size) {
		general_size = _general_size;
		data = new T[general_size];
		for (int i = 0; i < general_size; i++) {
			data[i] = 0;
		}
	}
	~Vector() {
		delete data;
	}
	int getSize() {
		return general_size;
	}
	virtual T operator[](int index) {
		if (index >= this->general_size || index < 0)
			throw;
		return this->data[index];
	}
	void print() {
		std::cout << "General size: " << this->general_size << std::endl;
		for (int i = 0; i < this->general_size; i++) {
			std::cout << this->data[i] << std::endl;
		}
	}

};

template <class T> 
class Vector_c : public Vector<T> {
 public:
	Vector_c(int _general_size) : Vector<T>(_general_size) {
	}
	~Vector_c() {
	}

	l_sts replace(int index, T value) {
		if (index > this->general_size)
			return BOUNDS;
		this->data[index] = value;
		return SUCCESS;
	}

	l_sts insert(T value, int index = 0) {
		if (index > this->general_size)
			return BOUNDS;
		if (this->general_size > 0)
			this->shift_r(index);
		this->general_size++;
		this->data[index] = value;
		return SUCCESS;
	}
	virtual l_sts remove(int index) {
		if (index >= this->general_size || index < 0)
			return BOUNDS;
		if (index < this->general_size - 1)
			Vector<T>::shift_l(index);
		this->data[this->general_size - 1] = 0;
		this->general_size--;
		return SUCCESS;
	}
	T minimum() {
		if (this->general_size == 0)
			throw;
		int min = this->data[0];
		for (int i = 1; i < this->general_size; i++) {
			if (this->data[i] < min)
				min = this->data[i];
		}
		return min;
	}
	
	T maximum() {
		if (this->general_size == 0)
			throw;
		int max = this->data[0];
		for (int i = 1; i < this->general_size; i++) {
			if (this->data[i] > max)
				max = this->data[i];
		}
		return max;
	}
};

template <class T>
class Vector_dns : public Vector<T> {
private:
	const int batch_size = 10;
	void reallocate_Vector(int to) {
		int new_general_size = (to % batch_size + 1)*batch_size;
		T* new_data = new T[new_general_size];
		std::copy(this->data[0], this->data[this->general_size - 1], new_data[0]);
		delete[] this->data;
		this->general_size = new_general_size;
		this->data = new_data;
	}
public:
	Vector_dns(int _general_size) : Vector<T>(_general_size) {
	}
	~Vector_dns() {
	}
	l_sts insert(T value, int index = 0) {
		if (index > this->general_size - 1) {
			reallocate_Vector(index);
		}
		else if (this->general_size == this->general_size) {
			reallocate_Vector(this->general_size + 1);
		}
		if (this->general_size > 0)
			this->shift_r(index);
		this->general_size++;
		this->data[index] = value;
		return SUCCESS;
	}

};
