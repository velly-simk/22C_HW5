#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H
#define _template template<class T>

_template
class BinaryTree {
protected:
	struct BinaryNode {
		BinaryNode* _left;
		BinaryNode* _right;
		T _data;
		BinaryNode(const T& data) { _data = data, _left = nullptr, _right = nullptr; }
		BinaryNode(const T& data, BinaryNode * left, BinaryNode * right) {
			_data = data;
			_left = left;
			_right = right;
		}
		bool isLeaf() { return (_left == nullptr) && (_right == nullptr); }
	};

	BinaryNode* _rootNode;
	int _count;

public:
	BinaryTree() { _rootNode = nullptr, count = 0; }
	bool isEmpty() { return _count == 0; }
	int count() { return _count; }
	void clear(); //todo

	virtual bool insert(const T& item) = 0;
	virtual bool remove(const T& item) = 0;
	virtual bool getEntry(const T& item, T& output) const = 0;

private:
	void _output(void visit(T&), BinaryNode* first, BinaryNode* second, BinaryNode* third);
	BinaryNode* copyTree(const BinaryNode* root);
	void _destroyTree(BinaryNode* root);
};


_template
void BinaryTree<T>::_output(void visit(T&), BinaryNode* first, BinaryNode* second, BinaryNode* third) {
	if (first != nullptr) {
	}
}

#endif // !BINARYTREE_H
