#include <iostream>

#include "GenericHeap.h"

#include <stdlib.h> // rand srand
#include <time.h> // time

#define MAX_ARR_SIZE 100000

void buildArray(int* arr, int arrSize);

int intCompare(int & lhs, int & rhs);

void printArr(int * arr, int items);

IntegerPair selectionSort(int* arr, int arrSize);

using namespace std;
int main(int, char[]) {
	int arrSize = 1;
	int * arr = new int[0](),
		* arr2 = new int[0]();
	IntegerPair heapSortCounts = IntegerPair(),
		selectionSortCounts = IntegerPair();

	while (arrSize < MAX_ARR_SIZE) {
		arrSize *= 10;
		cout << "Array Size : " << arrSize << endl;
		delete[] arr;
		delete[] arr2;

		heapSortCounts = IntegerPair();
		selectionSortCounts = IntegerPair();

		arr = new int[arrSize]();
		arr2 = new int[arrSize]();

		buildArray(arr, arrSize);
		memcpy(arr2, arr, arrSize * sizeof(int));

		if (arrSize < 1000) printArr(arr, arrSize);

		cout << "Heap Sort Array : " << endl;
		GenericHeap<int> maxheap = GenericHeap<int>(intCompare, arr, arrSize, arrSize);
		heapSortCounts += maxheap.rebuildHeap(0);
		heapSortCounts += maxheap.sortArray();
		if (arrSize < 1000) printArr(arr, arrSize);
		cout << "\tSwaps: " << heapSortCounts.pair[0] << " | Comparisons: " << heapSortCounts.pair[1] << endl;
		cout << "Selection Sort Array : " << endl;
		selectionSortCounts = selectionSort(arr2, arrSize);
		if (arrSize < 1000) printArr(arr2, arrSize);
		cout << "\tSwaps: " << selectionSortCounts.pair[0] << " | Comparisons: " << selectionSortCounts.pair[1] << endl << endl;
		
		maxheap.swapArray(new int[0](), 0, 0);

	}

	getchar();
}

IntegerPair selectionSort(int *arr, int arrSize) {
	int *x;
	int tmp;
	IntegerPair z = IntegerPair();
	for (int i = 0; i < arrSize; ++i) {
		++z.pair[1];
		x = &arr[i];
		for (int j = x - arr; j < arrSize; ++j) {
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