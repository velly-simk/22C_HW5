#pragma once
#ifndef HEAPINTERFACE_H
#define HEAPINTERFACE_H
#define _template template<class T>

_template
class HeapInterface {
public:
	virtual bool isEmpty() const = 0;
	virtual int count() const = 0;
	virtual int height() = 0;
	virtual T* peekTop() const = 0;

	virtual bool insert(const T&) = 0;
	virtual bool remove(T& output) = 0;
	virtual void clear() = 0;
	virtual ~HeapInterface() {}
};




#endif