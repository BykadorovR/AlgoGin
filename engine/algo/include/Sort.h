#pragma once
#include "Defs.h"
#include "General.h"

class CSort {
	public:
	template <class T>
	void sort(Container_ns<T>& list) {

	}
	template <class T>
	void swap(int id1, int id2, Container_ns<T>& l) {
		T temp;
		temp = l[id1];
		l.replace(id1, l[id2]);
		l.replace(id2, temp);
	}
};

class Bubble : public CSort {
 public:
	Bubble() {

	}
	
	template <class T>
	void sort(Container_ns<T>& list) {
		//we don't use i here!!! just repeat 
		//we pushed to end the greatest element with every iteration
		//so we need n - 1 iteration
		for (int i = 0; i < list.getSize() - 1; i++) {
			for (int j = 0; j < list.getSize() - 1; j++) {
				if (list[j + 1] < list[j]) {
					swap(j, j + 1, list);
				}
			}
		}
	}
};