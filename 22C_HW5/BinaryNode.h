// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by
 
#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{   
private:
	ItemType              item;         // Data portion
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child
	int _depthFactor, _depth;

public:
	int depth() { return _depth; };
	void depth(int newDepth) {_depth = newDepth; }
	int depthFactor() { return _depthFactor; }
	void depthFactor(int newFactor) { _depthFactor = newFactor };

	// constructors
	BinaryNode(const ItemType & anItem) { item = anItem; leftPtr = 0; rightPtr = 0; _depth = 0; _depthFactor = 0; }
	BinaryNode(const ItemType & anItem, BinaryNode<ItemType>* left, BinaryNode<ItemType>* right) {
		item = anItem; leftPtr = left; rightPtr = right;
		_depth = (left._depth > right._depth ? left._depth : right._depth) + 1;
		_depthFactor = left._depth - right._depth;
	}
	// accessors
	void setItem(const ItemType & anItem) {item = anItem;}
	void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}
	// mutators
	ItemType getItem() const	 {return item;}
	BinaryNode<ItemType>* getLeftPtr() const {return leftPtr;}
	BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}

	bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
}; 

#endif 
