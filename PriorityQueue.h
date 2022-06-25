#pragma once

#include "BinaryTree.h"

template <typename T>
class PriorityQueue {
private:
	BinaryTree<T>* items = nullptr;
public:
	PriorityQueue();
	PriorityQueue(T* arr, int size);
	PriorityQueue(std::initializer_list<T> list);
	PriorityQueue(const PriorityQueue<T>& pq);
	~PriorityQueue();

	int Size();

	bool operator==(PriorityQueue<T>& pq);

	T Top();

	void Push(T value);
	void Pop();

	bool Find(T value);
	bool IfSubqueue(PriorityQueue<T>& pqueue);

	PriorityQueue<T>* Map(T(*func)(T));
	PriorityQueue<T>* Where(bool(*func)(T));
	T Reduce(T(*func)(T, T), const T value);

	PriorityQueue<T>* GetSubqueue(int start, int end);
	PriorityQueue<T>* Merge(PriorityQueue<T>& pqueue);

	void Print();
};

template <typename T> PriorityQueue<T>::PriorityQueue() {
	items = new BinaryTree<T>;
}

template <typename T> PriorityQueue<T>::PriorityQueue(T* arr, int size) {
	items = new BinaryTree<T>(arr, size);
}

template <typename T> PriorityQueue<T>::PriorityQueue(std::initializer_list<T> list) {
	items = new BinaryTree<T>(list);
}

template <typename T> PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& pq) {
	items = new BinaryTree<T>(pq.items);
}

template <typename T> PriorityQueue<T>::~PriorityQueue() {
	delete items;
}

template <typename T> int PriorityQueue<T>::Size() {
	return items->GetQuantity();
}

template <typename T> bool PriorityQueue<T>::operator==(PriorityQueue<T>& pq) {
	int size = Size();
	if (size != pq.Size()) {
		return false;
	}
	T* array1 = items->SaveToArray();
	T* array2 = pq.items->SaveToArray();
	for (int i = 0; i < size; ++i) {
		if (array1[i] != array2[i]) {
			delete[] array1;
			delete[] array2;
			return false;
		}
	}
	delete[] array1;
	delete[] array2;
	return true;
}

template <typename T> T PriorityQueue<T>::Top() {
	return items->FindMax();
}

template <typename T> void PriorityQueue<T>::Push(T value) {
	items->Insert(value);
}

template <typename T> void PriorityQueue<T>::Pop() {
	T max = Top();
	items->DeleteByValue(max);
}

template <typename T> bool PriorityQueue<T>::Find(T value) {
	return items->Find(value);
}

template <typename T> PriorityQueue<T>* PriorityQueue<T>::Map(T(*func)(T)) {
	PriorityQueue<T>* result = new PriorityQueue<T>;
	result->items = items->Map(func);
	return result;
}

template <typename T> PriorityQueue<T>* PriorityQueue<T>::Where(bool(*func)(T)) {
	PriorityQueue<T>* result = new PriorityQueue<T>;
	result->items = items->Where(func);
	return result;
}

template <typename T> T PriorityQueue<T>::Reduce(T(*func)(T, T), const T value) {
	T result = items->Reduce(func, value);
	return result;
}

template <typename T> PriorityQueue<T>* PriorityQueue<T>::GetSubqueue(int start, int end) {
	T* array = items->SaveToArray();
	int size = end - start + 1;
	PriorityQueue<T>* result = new PriorityQueue<T>(array + start, size);
	delete[] array;
	return result;
}

template <typename T> PriorityQueue<T>* PriorityQueue<T>::Merge(PriorityQueue<T>& pqueue) {
	PriorityQueue<T>* result = new PriorityQueue<T>;
	result->items = items->Merge(*pqueue.items);
	return result;
}

template <typename T> void PriorityQueue<T>::Print() {
	items->PrintWithTraversal("LNR");
	std::cout << '\n';
}

template <typename T> bool PriorityQueue<T>::IfSubqueue(PriorityQueue<T>& pqueue) {
	T* array1 = items->SaveToArray();
	T* array2 = pqueue.items->SaveToArray();
	int size1 = Size();
	int size2 = pqueue.Size();
	if (size2 > size1) {
		delete[] array1;
		delete[] array2;
		return false;
	}
	int i = 0;
	while (i < size1) {
		if (array2[0] == array1[i]) {
			break;
		}
		i++;
	}
	for (int j = 0; j < size2; ++j) {
		if (array2[j] != array1[i] || i >= size1) {
			delete[] array1;
			delete[] array2;
			return false;
		}
		i++;
	}
	delete[] array1;
	delete[] array2;
	return true;
}













