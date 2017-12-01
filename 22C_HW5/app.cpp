#include <iostream>

#include "MaxHeap.h"

void toConsole(int*& input);
int intPtrCompare(const int * & lhs, const int * &rhs);

using namespace std;
int main(int, char[]) {

	MaxHeap<int*> heap;

	int a = 1,
		b = 2,
		c = 3;

	heap.insert(&a);
	heap.insert(&b);
	heap.insert(&c);

	heap.printHeap(toConsole);

	getchar();
}

void toConsole(int*& input) {
	cout << *input << " ";
}

int intPtrCompare(const int * & lhs, const int * & rhs) {
	if (*lhs > *rhs) return 1;
	else if (*rhs > *lhs) return -1;
	else return 0;
}