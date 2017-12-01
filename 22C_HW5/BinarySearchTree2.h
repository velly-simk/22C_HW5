#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#define _template template<class T>

#include "BinaryTree2.h"

_template
class BinarySearchTree : public BinaryTree<T> {
private:
	/* insert node into tree */
	BinaryNode* _insert(BinaryNode & root, BinaryNode & newNode);

	/* locate and delete node from tree */
	BinaryNode* _removeNode(BinaryNode * root, const T & target, bool & success);

	/* delete node called by remove*/
	BinaryNode* _deleteNode(BinaryNode * targetNode);

	/* remove left most node of tree from root */
	BinaryNode* _removeLeftMostNode(BinaryNode & root, T & successor);

	/* locate node with target as data*/
	BinaryNode* _findNode(BinaryNode & root, const T & target);
public:
	bool insert(const T& item);
	bool remove(const T& item);
	bool getEntry(const T& item, T& output)const ;
};


#endif // !BINARYSEARCHTREE_H
