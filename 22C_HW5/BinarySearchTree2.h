#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#define _template template<class T>

#include "BinaryTree2.h"

_template
class BinarySearchTree : public BinaryTree<T> {
private:
	void _insert();
	void _removeNode();
	void _deleteNode();
	void _removeLeftMostNode();
	void _findNode();
public:
	bool insert(const T& item);
	bool remove(const T& item);
	bool getEntry(const T& item, T& output)const ;
};


#endif // !BINARYSEARCHTREE_H
