/* Generic Heap Class
	Takes in function pointer which determines what kind of heap it is.
	Function must return an int and take in two items of the same type.
		Returns > 0 when first parameter meets the condition over the second one.
	Example: max heap function
		int function(item1, item2) {if (item1 > item2) return 1; else 0;}

	Heap can start with an exisiting array, but needs a rebuildHeap() call to treat array as a heap.
	
	*/

#pragma once
#ifndef MAXHEAP_H
#define MAXHEAP_H
#define _template template<class T>

struct IntegerPair {
	int pair[2];
	IntegerPair() { pair[0] = 0, pair[1] = 0; }
	IntegerPair(const IntegerPair &x) { pair[0] = x.pair[0], pair[1] = x.pair[1]; }
	IntegerPair(int x, int y) { pair[0] = x, pair[1] = y; }

	IntegerPair operator+(const IntegerPair& x) {
		IntegerPair y = IntegerPair();
		y.pair[0] = this->pair[0] + x.pair[0];
		y.pair[1] = this->pair[1] + x.pair[1];
		return y;
	}

	IntegerPair& operator+=(const IntegerPair& x) {
		this->pair[0] += x.pair[0];
		this->pair[1] += x.pair[1];
		return *this;
	}
};


_template
class GenericHeap {
private:
	int _count, _height, _maxItems;
	/* used to skip height calculations if they have already been done once */
	bool _resolved, _isHeap;
	T* items;
	/* used to compare two items in heap
	example: max heap,
	compare will return > 0 for lhs > rhs */
	int (*compare)(T & lhs, T & rhs);

	/* helper functions */
	int getLeftChildIndex(const int & nodeIndex) const;
	int getRightChildIndex(const int & nodeIndex) const;
	int getParentIndex(const int & nodeIndex) const ;
	bool isLeaf(const int & nodeIndex) const;

	/* heep maintenance functions*/
	void reheapUp(const int & nodeIndex);
	IntegerPair reheapDown(const int & nodeIndex);
	void swap(const int & index1, const int & index2);

public:
	/* Constructor will start with am array of size 8 
		also object will need to know how to compare its items to be created. */
	GenericHeap(int compareFunction(T& lhs, T& rhs)) { items = new T[8]; _maxItems = 8; _resolved = false; _count = 0; compare = compareFunction; _isHeap = true; } // minimum size 8
	
	/* Start a heap object from an existing array
		array must be a complete binary tree, need to call rebuildHeap(0) manually to insert/remove/sort */
	GenericHeap(int compareFunction(T& lhs, T& rhs), T* itemArray, int arraySize, int itemCount) {
		compare = compareFunction;
		items = itemArray;
		_maxItems = arraySize;
		_resolved = false;
		if (itemCount >= 0 )_count = itemCount;
		else _count = 0;
		_isHeap = false;
	}

	/* Destroying Object will dealocate current array in object,
	allocate and swapArray() to save array from getting deleted */
	virtual ~GenericHeap() { delete[] items; }

	bool isEmpty() const { return !_count; }
	/* returns count of items in array*/
	int count() const { return _count; }
	/* Returns a pointer to current top item of heap. */
	T* peekTop() const { return &items[0]; } 
	/* returns height of tree formed by array */
	int height();

	/* requires current array to be a heap */
	bool insert(const T& item);
	/* requires current array to be a heap
	returns swaps made to reheap new heap, output is set to item taken out
	returns -1 if current array is not a heap*/
	IntegerPair remove(T & output);
	/* empties current array */
	void clear();

	/* allocates new array of size desired, copies current array and replaces with new one, old array is deleted*/
	void resize(const int & newSize);
	/* transforms current array into heap starting from index, assuming it was not a heap,
	returns swaps made to accomplish this task
	for the whole array to become a heap, start has to be index 0 */
	IntegerPair rebuildHeap(const int& index = 0);
	/* swaps current array with new desired array, returns pointer to old array,
	old needs to be deleted manually
	object needs to rebuildHeap(0) to treat new array as a heap */
	T* swapArray(T* newArray, int newArraySize, int newArrayItemCount);
	/* breaks heap by sorting it, array needs to be a heap returns -1 if it is not
	example: max heap will turn into array sorted ascending, min heap will be descending */
	IntegerPair sortArray();
};

/* Private Functions */
_template
int GenericHeap<T>::getLeftChildIndex(const int & nodeIndex) const {
	return nodeIndex * 2 + 1;

}

_template
int GenericHeap<T>::getRightChildIndex(const int & nodeIndex) const {
	return nodeIndex * 2 + 2;
}

_template
int GenericHeap<T>::getParentIndex(const int & nodeIndex) const {
	return ( (nodeIndex + 1) >> 1) - 1;
}

_template
bool GenericHeap<T>::isLeaf(const int & nodeIndex) const {
		if (getLeftChildIndex(nodeIndex) >= _count) return true;
		return false;
}

_template
void GenericHeap<T>::reheapUp(const int & nodeIndex) {
	int parentIndex = getParentIndex(nodeIndex);
	if ((parentIndex >= 0) && (compare(items[nodeIndex], items[parentIndex]) > 0)) {
		swap(nodeIndex, parentIndex);
		reheapUp(parentIndex);
	}
}

_template
IntegerPair GenericHeap<T>::reheapDown(const int & nodeIndex) {
	IntegerPair x = IntegerPair();
	int left = getLeftChildIndex(nodeIndex),
		right = getRightChildIndex(nodeIndex);

	if (left >= _count) { // if no children
		x.pair[1] += 1;
		return x;
	}
	else if (right >= _count) { // if there is no right child
		if (compare(items[left], items[nodeIndex]) > 0){ // compare left and node
			swap(left, nodeIndex); // left meets condition so swap
			++x.pair[0];
			x += reheapDown(left); // check left
		}
		x.pair[1] += 3;
		return x;
	}
	else if (compare(items[left], items[right]) > 0) { // both exist, compare left and right
		if (compare(items[left], items[nodeIndex]) > 0) { // left is meets condition, compare with node
			swap(left, nodeIndex); // left meets condition swap
			++x.pair[0];
			x += reheapDown(left); // check new left
		}
		x.pair[1] += 4;
		return x;
	}
	else {
		if (compare(items[right], items[nodeIndex]) > 0) { // right is equal to left or meets condition, compare with node
			swap(right, nodeIndex); // right meets condition, swap nodes
			++x.pair[0];
			x += reheapDown(right); // check new right
		}
		x.pair[1] += 4;
		return x; // no swap made
	}

}

_template
void GenericHeap<T>::swap(const int & index1, const int & index2) {
	T tmp = items[index1];
	items[index1] = items[index2];
	items[index2] = tmp;
}

/* Public Functions */

_template
int GenericHeap<T>::height() {
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
bool GenericHeap<T>::insert(const T& item) {
	if (!_isHeap) return false;
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
IntegerPair GenericHeap<T>::remove(T & output) {
	if (!_isHeap) return IntegerPair(-1,-1);
	IntegerPair x = IntegerPair();
	if (_count <= 0) return x;

	output = items[0];

	items[0] = items[_count-1];
	--_count;
	x = reheapDown(0);

	_resolved = false;

	return x;
}

_template
void GenericHeap<T>::clear() {
	memset(items, 0, _maxItems * sizeof(T*));
	_count = 0;
	_resolved = false;
}

_template
void GenericHeap<T>::resize(const int & newSize) {
	T* tmp = new T[newSize];
	memcpy(tmp, items, sizeof(T*) * _maxItems);
	memset(tmp, 0, (newSize - _maxItems) * sizeof(T*));

	delete[] items;
	items = tmp;

	_maxItems = newSize;
}

_template
IntegerPair GenericHeap<T>::rebuildHeap(const int& index) {
	if (_isHeap) return IntegerPair(); // save computation if we are already a heap
	IntegerPair x = IntegerPair();
	if (isLeaf(index)) return x;
	x += rebuildHeap(getLeftChildIndex(index));
	x += rebuildHeap(getRightChildIndex(index));
	if (index == 0) _isHeap = true; // full array becomes a heap only if rebuildHeap is started from index 0;
	x += reheapDown(index);
	return x;
}

_template
T* GenericHeap<T>::swapArray(T* newArray, int newArraySize, int newArrayItemCount) {
	T* tmp = items;
	items = newArray;
	_count = newArrayItemCount;
	_maxItems = newArraySize;
	_resolved = false;
	_isHeap = false;
	return tmp;
}

_template
IntegerPair GenericHeap<T>::sortArray() {
	if (!_isHeap) return IntegerPair(-1,-1);
	int originalCount = _count;
	IntegerPair x = IntegerPair();
	T tmp;

	while (_count) {
		x += remove(tmp);
		items[_count] = tmp;
		++x.pair[0]; // swapping top and last is not accounted in remove
	}
	_count = originalCount;
	_isHeap = false;

	return x;
}

#endif // !MAXHEAP_H
