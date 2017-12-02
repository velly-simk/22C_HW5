#include <iostream>

#include "GenericHeap.h"

#include <stdlib.h> // rand srand
#include <time.h> // time

#define ARR_SIZE 1000000

void buildArray(int* arr, int arrSize);

int intCompare(int & lhs, int & rhs);

void printArr(int * arr, int items);

IntegerPair selectionSort(int* arr);

using namespace std;
int main(int, char[]) {
	int *arr = new int[ARR_SIZE](),
		*arr2 = new int[ARR_SIZE]();
	IntegerPair heapSortCounts = IntegerPair(),
		selectionSortCounts = IntegerPair();

	buildArray(arr, ARR_SIZE);
	memcpy(arr2, arr, ARR_SIZE * sizeof(int));

	GenericHeap<int> maxheap = GenericHeap<int>(intCompare, arr, ARR_SIZE, ARR_SIZE);
	heapSortCounts += maxheap.rebuildHeap(0);
	heapSortCounts += maxheap.sortArray();
	cout << "Swaps: " << heapSortCounts.pair[0] << " | Comparisons: " << heapSortCounts.pair[1] << endl;
	selectionSortCounts = selectionSort(arr2);
	cout << "Swaps: " << selectionSortCounts.pair[0] << " | Comparisons: " << selectionSortCounts.pair[1] << endl;

	getchar();
}

IntegerPair selectionSort(int *arr) {
	int *x;
	int tmp;
	IntegerPair z = IntegerPair();
	for (int i = 0; i < ARR_SIZE; ++i) {
		++z.pair[1];
		x = &arr[i];
		for (int j = x - arr; j < ARR_SIZE; ++j) {
			if (arr[j] < *x) x = &arr[j];
			z.pair[1] += 2;
		}
		if (!(x - &arr[i])) {
			++z.pair[1];
			continue;
		}
		tmp = arr[i];
		arr[i] = *x;
		arr[x - arr] = tmp;
		++z.pair[0];
		++z.pair[1];
	}
	return z;

}

void buildArray(int* arr, int arraySize) {
	srand(time(NULL));

	for (int i = 0; i < arraySize; ++i) {
		arr[i] = rand() % 198 - 100;
	}
}

void printArr(int * arr, int items) {
	for (int x = 0; x < items; ++x) {
		cout << arr[x] << " ";
	}
	cout << endl;
}


int intCompare(int & lhs, int & rhs) {
	if (lhs > rhs) return 1;
	else if (rhs > lhs) return -1;
	else return 0;
}