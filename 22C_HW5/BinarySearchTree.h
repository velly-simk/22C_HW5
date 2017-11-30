// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Velly Simeonov
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* &nodePtr, BinaryNode<ItemType>* &newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
   
public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
 
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	int tmp = this->count;

	_insert(this->rootPtr, newNodePtr);

	// depth resolution
	this->maxDepth = this->rootPtr->depth();

	return this->count != tmp ;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType & anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType>* tmp;

	tmp = findNode(this->rootPtr, anEntry);

	if (!tmp) return false;
	returnedItem = tmp->getItem();

	return true;
}  



//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* &nodePtr,
                                                          BinaryNode<ItemType>* &newNodePtr)
{
	BinaryNode<ItemType>* ptr;

	if (!nodePtr) {
		++this->count;
		return nodePtr = newNodePtr;
	}

	if (newNodePtr->getItem() < nodePtr->getItem()) {
		ptr = nodePtr->getLeftPtr();
		if (_insert(ptr, newNodePtr) == newNodePtr) {
			nodePtr->setLeftPtr(newNodePtr);
			++this->count;
		}
		// depth resolution
		if (nodePtr->depth() == nodePtr->getLeftPtr()->depth())
			nodePtr->depth(nodePtr->depth()+ 1);
	}
	if (newNodePtr->getItem() > nodePtr->getItem()) {
		ptr = nodePtr->getRightPtr();
		if (_insert(ptr, newNodePtr) == newNodePtr) {
			nodePtr->setRightPtr(newNodePtr);
			++this->count;
		}
		// depth resolution
		if (nodePtr->depth() == nodePtr->getRightPtr()->depth())
			nodePtr->depth(nodePtr->depth() + 1);
	}

	return nodePtr;
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const 
{
	if (!nodePtr) return NULL;

	if (target < nodePtr->getItem()) {
		return findNode(nodePtr->getLeftPtr(), target);
	}
	else if (target > nodePtr->getItem()) {
		return findNode(nodePtr->getRightPtr(), target);
	}
	else {
		return nodePtr;
	}
}  


#endif
