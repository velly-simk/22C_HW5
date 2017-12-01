#pragma once
#ifndef MAXHEAP_H
#define MAXHEAP_H
#define _template template<class T>

#include "HeapInterface.h"

#include <iostream>

_template
class MaxHeap {
private:
	int _count, _height, _maxItems;
	bool _resolved;
	T* items;
	int (*compare)(T & lhs, T & rhs);

	int getLeftChildIndex(const int & nodeIndex) const;
	int getRightChildIndex(const int & nodeIndex) const;
	int getParentIndex(const int & nodeIndex) const ;
	bool isLeaf(const int & nodeIndex) const;

	void reheapUp(const int & nodeIndex);
	void reheapDown(const int & nodeIndex);
	void swap(const int & index1, const int & index2);

public:
	MaxHeap(int compareFunction(T& lhs, T& rhs)) { items = new T[8]; _maxItems = 8; _resolved = false; _count = 0; compare = compareFunction; } // minimum size 8
	virtual ~MaxHeap() { delete[] items; }

	bool isEmpty() const { return !_count; }
	int count() const { return _count; }
	T* peekTop() const { return &items[0]; }
	int height();

	bool insert(const T& item);
	bool remove(T & output);
	void clear();

	void resize(const int & newSize);

	void printHeap(void visit(T & in));
};

_template
void MaxHeap<T>::printHeap(void visit (T & in)) {
	for (int i = 0; i < _count; ++i) {
		visit(items[i]);
	}
	std::cout << std::endl;
}

/* Private Functions */
_template
int MaxHeap<T>::getLeftChildIndex(const int & nodeIndex) const {
	return nodeIndex * 2 + 1;

}

_template
int MaxHeap<T>::getRightChildIndex(const int & nodeIndex) const {
	return nodeIndex * 2 + 2;
}

_template
int MaxHeap<T>::getParentIndex(const int & nodeIndex) const {
	return ( (nodeIndex + 1) >> 1) - 1;
}

_template
bool MaxHeap<T>::isLeaf(const int & nodeIndex) const {
		if (getLeftIndex(nodeIndex) > _count - 1) return true;
}

_template
void MaxHeap<T>::reheapUp(const int & nodeIndex) { // improve with comparison function pointer
	int parentIndex = getParentIndex(nodeIndex);
	if ((parentIndex >= 0) && (compare(items[nodeIndex], items[parentIndex]) > 0)) {
		swap(nodeIndex, parentIndex);
		reheapUp(parentIndex);
	}
}

_template
void MaxHeap<T>::reheapDown(const int & nodeIndex) { // improve with comparison function pointer
	int left = getLeftChildIndex(nodeIndex),
		right = getRightChildIndex(nodeIndex);

	if (left >= _count) return;

	else if (right >= _count) {
		if (compare(items[left], items[nodeIndex]) > 0){
			swap(left, nodeIndex);
			reheapDown(left);
		}
	}
	else if (compare(items[left], items[right]) > 0) {
		if (compare(items[left], items[nodeIndex]) > 0) {
			swap(left, nodeIndex);
			reheapDown(left);
		}
	}
	else {
		if (compare(items[right], items[nodeIndex]) > 0) {
			swap(right, nodeIndex);
			reheapDown(right);
		}
	}
}

_template
void MaxHeap<T>::swap(const int & index1, const int & index2) {
	T tmp = items[index1];
	items[index1] = items[index2];
	items[index2] = tmp;
}

/* Public Functions */

_template
int MaxHeap<T>::height() {
	if (!_resolved) {
		int x = 0, count = _count;
		while (count != 1) {
			count >>= 1;
			++x;
		}
		_resolved = true;
		return _height = x;
	}
	return _height;
}

_template
bool MaxHeap<T>::insert(const T& item) {
	if (_count == _maxItems) {
		resize(_maxItems * 2);
	}

	items[_count] = item;
	reheapUp(_count);
	++_count;
	_resolved = false;
	return true;
}

_template
bool MaxHeap<T>::remove(T & output) {
	if (_count <= 0) return false;

	output = items[0];

	items[0] = items[_count-1];
	--_count;
	reheapDown(0);

	_resolved = false;

	return true;
}

_template
void MaxHeap<T>::clear() {
	memset(items, 0, _maxItems * sizeof(T*));
	_count = 0;
	_resolved = false;
}

_template
void MaxHeap<T>::resize(const int & newSize) {
	T* tmp = new T[newSize];
	memcpy(tmp, items, sizeof(T*) * _maxItems);
	memset(tmp, 0, (newSize - _maxItems) * sizeof(T*));

	delete[] items;
	items = tmp;

	_maxItems = newSize;
}

#endif // !MAXHEAP_H
