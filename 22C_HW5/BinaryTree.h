// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Velly Simeonov
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

#include <cmath> // for pow() can switch to bit shifting but I need to change maxDepth to an unsigned variable

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;	// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree) { rootPtr = copyTree(tree.rootPtr); }
	virtual ~BinaryTree() { clear(); }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void inOrderR(void visit(ItemType &, int)) const { _inorder_r(visit, rootPtr, 0); }
	void preOrder(Queue<ItemType> &itemQueue) const { _preorder(itemQueue, rootPtr); }
	void getLeftMost(ItemType &node) const { _getleftmost(node, rootPtr); }
	void getRightMost(ItemType &node) const { _getrightmost(node, rootPtr); }
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	void breadthOrder(Queue<ItemType> &itemQueue);

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   
	// deletes sub tree with provided root node, does nothing if node is not in tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _preorder(Queue<ItemType> &nodeQueue, BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder_r(void visit(ItemType &,int), BinaryNode<ItemType>* nodePtr, int x) const;
	void _getleftmost(ItemType &node, BinaryNode<ItemType>* nodePtr) const;
	void _getrightmost(ItemType &node, BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
   
}; 
/* Public FUnctions */

template<class ItemType>
void BinaryTree<ItemType>::breadthOrder(Queue<ItemType> &itemQueue) {
	Queue<BinaryNode<ItemType>*> nodeQueue;
	BinaryNode<ItemType>* mov;
	nodeQueue.enqueue(rootPtr);

	while(!nodeQueue.isEmpty()) {
		nodeQueue.dequeue(mov);

		if (mov) {
			nodeQueue.enqueue(mov->getLeftPtr());
			nodeQueue.enqueue(mov->getRightPtr());
			itemQueue.enqueue(mov->getItem());
		}

	}
}


//////////////////////////////////////////////////////////////////////////


/* Private Functions */
template<class ItemType>
BinaryNode<ItemType>*  BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType> *nNode = 0;
	if (nodePtr) {
		nNode = new BinaryNode<ItemType>(nodePtr->getItem(), 
			copyTree(nodePtr->getLeftPtr()), 
			copyTree(nodePtr->getRightPtr()));
	}
	return nNode;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr == NULL) return;

	BinaryNode<ItemType>* node = rootPtr, *prev = NULL;
	int level = 1;

	// Locate start
	while ((node != NULL) && (node->getItem() != nodePtr->getItem())) {
		prev = node;
		++level;
		if (nodePtr->getItem() < node->getItem()) {
			node = node->getLeftPtr();
		}
		else if (nodePtr->getItem() > node->getItem()) {
			node = node->getRightPtr();
		}
	}

	if (node == NULL) return;
	// end locate

	// start deleting
	Queue<BinaryNode<ItemType>*> nodeQ;

	do {
		if (node == NULL) {
			nodeQ.dequeue(node);
			continue;
		}

		nodeQ.enqueue(node->getLeftPtr());
		nodeQ.enqueue(node->getRightPtr());

		delete node;
		--count;

		nodeQ.dequeue(node);

	} while (!nodeQ.isEmpty());
	// end deleting
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(Queue<ItemType> &itemQueue, BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		itemQueue.enqueue(nodePtr->getItem());
		_preorder(itemQueue, nodePtr->getLeftPtr());
		_preorder(itemQueue, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  
template<class ItemType>
void BinaryTree<ItemType>::_inorder_r(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int x) const
{
	if (nodePtr != 0) {
		_inorder_r(visit, nodePtr->getRightPtr(), x+1);
		ItemType item = nodePtr->getItem();
		visit(item, x);
		_inorder_r(visit, nodePtr->getLeftPtr(), x+1);

	}
}


template<class ItemType>
void BinaryTree<ItemType>::_getleftmost(ItemType &node, BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		node = nodePtr->getItem();
		_getleftmost(node, nodePtr->getLeftPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_getrightmost(ItemType &node, BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		node = nodePtr->getItem();
		_getrightmost(node, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}  

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if (this != &sourceTree) {
		this->clear();

		BinaryNode<ItemType> *ptr;

		Queue<BinaryNode<ItemType>*> nodes;
		nodes.enqueue(sourceTree.rootPtr);

		count = sourceTree.count;
		
		while (!nodes.isEmpty()) {
			nodes.dequeue(ptr);
			while (ptr) {
				nodes.enqueue(ptr->getLeftPtr());
				nodes.enqueue(ptr->getRightPtr());
				this->insert(ptr->getItem());
				nodes.dequeue(ptr);
			}
		}
	}
	return *this;
}  


#endif

