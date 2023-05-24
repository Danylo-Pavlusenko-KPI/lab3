#pragma once
#include <iostream>

using namespace std;


template<class T>
class Queue {

	struct Element {
		T data;
		Element* next = NULL;
	};

	int size = 0;
	Element* first = NULL;
	Element* last = NULL;

public:
	~Queue() {
		Clear();
	}
	void Enqueu(T to_append) {
		Element* element = new Element();
		element->data = to_append;
		if (first == NULL) {
			first = last = element;
		}
		else last = last->next = element;
		size++;
	}
	T Dequeu() {
		if (!first) {
			//throw "Queue is empty";
			exit(3);
		}
		T to_return = first->data;
		Element* element = first;
		first = first->next;
		delete element;
		size--;
		return to_return;
	}
	int Size() {
		return size;
	}

	void Clear() {
		while (first) {
			Element* element = first;
			first = first->next;
			delete element;
		}
		size = 0;
	}

	bool IsEmpty() {
		return size == 0; 
	}
};








