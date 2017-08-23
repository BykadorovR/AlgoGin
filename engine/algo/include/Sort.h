#pragma once
#include "Defs.h"
#include "General.h"

template <class T>
void swap(int id1, int id2, Container_ns<T>& l) {
	T temp;
	temp = l[id1];
	l[id1] = l[id2];
	l[id2] = temp;
}

//O(n^2)
class Bubble {
public:
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

//O(n^2)
class Selection {
public:
	template <class T>
	void sort(Container_ns<T>& list) {
		//find the smallest one on every iteration
		for (int i = 0; i < list.getSize() - 1; i++) {
			T min = list[i];
			for (int j = i + 1; j < list.getSize(); j++) {
				if (list[j] < min) {
					min = list[j];
					swap(i, j, list);
				}
			}
		}
	}
};

//O(n^2)
class Insertion {
public:
	template <class T>
	void sort(Container_ns<T>& list) {
		//on every iteration shift element to it position
		//so move to left every element until it on own place or start of container
		//5 3 2 4 1 (1)-> 5 3 2 4 1 (2)-> 3 5 2 4 1 (3)-> 3 2 5 4 1 -> 2 3 5 4 1 (4)-> 2 3 4 5 1 (5)-> 2 3 4 1 5 -> 2 3 1 4 5 -> 2 1 3 4 5 -> 1 2 3 4 5
		for (int i = 1; i < list.getSize(); i++) {
			int j = i;
			while (j > 0 && list[j] < list[j - 1]) {
				swap(j, j - 1, list);
				j--;
			}
		}
	}
};