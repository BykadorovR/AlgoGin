#pragma once
#include "General.h"

template <class T>
class Vector_ns : public Container_ns<T> {
protected:
	const int batch_size = 10;
	T* data;
	int general_size;
	int size;

	void reallocate_vector(int index) {
		int new_general_size = (index / batch_size + 1)*batch_size;
		T* new_data = new T[new_general_size];
		memcpy(new_data, data, general_size*sizeof(T));
		delete[] data;
		general_size = new_general_size;
		data = new_data;
	}
	//for insertion
	l_sts shift_r(int index) {
		int value = 0;
		//have to reallocate memory in previous code
		for (int i = index; i < size + 1; i++) {
			T tmp_val = data[i];
			data[i] = value;
			value = tmp_val;
		}
		return SUCCESS;
	}
	//for remove
	l_sts shift_l(int index) {
		//if index == size - 1 so it's corner element and we don't need to do shift
		for (int i = index + 1; i < size; i++) {
			T tmp_val = data[i];
			data[i - 1] = tmp_val;
		}
		return SUCCESS;
	}
public:
	Vector_ns(int _general_size) {
		general_size = _general_size;
		size = general_size;
		data = new T[general_size];
		for (int i = 0; i < general_size; i++) {
			data[i] = 0;
		}
	}
	Vector_ns() {
		general_size = batch_size;
		size = 0;
		data = new T[general_size];
		for (int i = 0; i < general_size; i++) {
			data[i] = 0;
		}
	}
    ~Vector_ns() {
        delete[] data;
    }
    
	int getSize() {
		return size;
	}

	void print() {
		std::cout << "General size: " << this->general_size << std::endl;
		std::cout << "size: " << this->size << std::endl;
		for (int i = 0; i < size; i++) {
			std::cout << data[i] << std::endl;
		}
	}

	T minimum() {
		if (size == 0)
			throw;
		int min = data[0];
		for (int i = 1; i < size; i++) {
			if (data[i] < min)
				min = data[i];
		}
		return min;
	}

	T maximum() {
		if (size == 0)
			throw;
		int max = data[0];
		for (int i = 1; i < general_size; i++) {
			if (data[i] > max)
				max = data[i];
		}
		return max;
	}

	l_sts remove(int index) {
		if (index >= size || index < 0)
			return BOUNDS;
		shift_l(index);
		//Just shift all values to left and remove last element
		data[size - 1] = 0;
		size--;
		return SUCCESS;
	}

	l_sts insert(T value, int index) {
		//we can't insert to position that isn't initialized
		if (index > size || index < 0)
			return BOUNDS;
		if (size == general_size)
			reallocate_vector(index);
		shift_r(index);
		data[index] = value;
		size++;
		return SUCCESS;
	}

	l_sts push_back(T value) {
		return insert(value, size);
	}

	l_sts push_start(T value) {
		return insert(value, 0);
	}

	l_sts pop_back() {
		return remove(size - 1);
	}

	l_sts pop_start() {
		return remove(0);
	}

    T& operator[](int index) {
        if (index >= size || index < 0)
            throw;
        return data[index];
    }
};

