#pragma once
#include "Defs.h"
#include "General.h"

template <class T>
class Array : public Container<T> {
 protected:
	T* data;
	int general_size;
 public:
	int size;
	Array(int _general_size) {
		general_size = _general_size;
		data = new T[general_size];
		for (int i = 0; i < general_size; i++) {
			data[i] = 0;
		}
		size = 0;
	}
	~Array() {
		delete data;
	}
	int getSize() {
		return size;
	}
};
template <class T>
class Array_cs : public Array<T> {
protected:
	l_sts shift_r(int index) {
		int value = 0;
		for (int i = index; i < this->size + 1; i++) {
			T tmp_val = this->data[i];
			this->data[i] = value;
			value = tmp_val;
		}
		return SUCCESS;
	}
	l_sts shift_l(int index) {
		for (int i = index + 1; i < this->size; i++) {
			T tmp_val = this->data[i];
			this->data[i-1] = tmp_val;
		}
		return SUCCESS;
	}
public:
	void print() {
		std::cout << "Current size: " << this->size << std::endl;
		std::cout << "General size: " << this->general_size << std::endl;
		for (int i = 0; i < this->size; i++) {
			std::cout << this->data[i] << std::endl;
		}
	}

	Array_cs(int _general_size) : Array<T>(_general_size) {
	}

	~Array_cs() {
	}

	l_sts replace(int index, T value) {
		if (index > this->size)
			return BOUNDS;
		l_sts sts = remove(index);
		if (sts > SUCCESS)
			return sts;
		sts = insert(value);
		return sts;
	}

	l_sts insert(T value, int index = 0) {
		if (index > this->size)
			return BOUNDS;
		if (this->size == this->general_size)
			return BOUNDS;
		int m_index;
		for (m_index = 0; m_index < this->size; m_index++) {
			if (value < this->data[m_index])
				break;
		}
		if (this->size > 0)
			shift_r(m_index);
		this->size++;
		this->data[m_index] = value;
		return SUCCESS;
	}
	 
	virtual T minimum() {
		return this->data[0];
	}
	virtual T maximum() {
		return this->data[this->size-1];
	}
	virtual l_sts remove(int index) {
		if (index >= this->size || index < 0)
			return BOUNDS;
		if (index < this->size - 1)
			shift_l(index);
		this->data[this->size - 1] = 0;
		this->size--;
		return SUCCESS;
	}

	virtual T operator[](int index) {
		if (index >= this->size || index < 0)
			throw;
		return this->data[index];
	}
};

template <class T> 
class Array_cns : public Array_cs<T> {
 public:
	Array_cns(int _general_size) : Array_cs<T>(_general_size) {
	}
	~Array_cns() {
	}

	l_sts replace(int index, T value) {
		if (index > this->size)
			return BOUNDS;
		this->data[index] = value;
		return SUCCESS;
	}

	l_sts insert(T value, int index = 0) {
		if (index > this->size)
			return BOUNDS;
		if (this->size == this->general_size)
			return BOUNDS;
		if (this->size > 0)
			this->shift_r(index);
		this->size++;
		this->data[index] = value;
		return SUCCESS;
	}
	T minimum() {
		if (this->size == 0)
			throw;
		int min = this->data[0];
		for (int i = 1; i < this->size; i++) {
			if (this->data[i] < min)
				min = this->data[i];
		}
		return min;
	}
	
	T maximum() {
		if (this->size == 0)
			throw;
		int max = this->data[0];
		for (int i = 1; i < this->size; i++) {
			if (this->data[i] > max)
				max = this->data[i];
		}
		return max;
	}
};

template <class T>
class Array_ds : public Array<T> {

};