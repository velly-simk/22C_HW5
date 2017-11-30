#include <iostream>

//#include "BinarySearchTree.h"
#include "BinarySearchTree2.h"


void toConsole(int*& input);

using namespace std;
int main(int, char[]) {
	BinarySearchTree<int> bst;
	/*
	BinarySearchTree<int*> bst;
	int a = 1, b = 2, c = 3;
	bst.insert(&b);
	bst.insert(&a);
	bst.insert(&c);
	cout << bst.Depth() << endl;

	a = 3;
	b = 2;
	c = 1;

	bst.inOrder(toConsole);
	*/
	getchar();
}

void toConsole(int*& input) {
	cout << *input << endl;
}