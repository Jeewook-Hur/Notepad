//Stack.h
/*
* 파일명칭:Stack.h
* 기능:자료구조 Stack
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#ifndef _STACK_H
#define _STACK_H
#include "Array.h"
typedef signed long int Long;


template<typename T>
class Stack {
public:
	Stack(Long capacity = 1000);
	~Stack();
	void Push(T object);
	T Pop();
	T Peek();
	Long Init();
	void Search(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*));
	Long GetCapacity();
	Long GetLength();
	bool IsEmpty();
	T& operator[](Long index);
private:
	Array<T> objects;
	Long capacity;
	Long length;
};

template<typename T>
Stack<T>::Stack(Long capacity) {
	this->objects = Array<T>(capacity);
	this->capacity = capacity;
	this->length = 0;
}

template<typename T>
Stack<T>::~Stack() {
}

template<typename T>
void Stack<T>::Push(T object) {
	if (this->length < this->capacity) {
		this->objects.Store(this->length, object);
	}
	else {
		this->objects.AppendFromRear(object);
		this->capacity++;
	}
	this->length++;
}

template<typename T>
T Stack<T>::Pop() {
	T ret;
	ret = this->objects.GetAt(this->length - 1);
	this->objects.Delete(length - 1);
	this->length--;
	this->capacity--;
	return ret;
}

template<typename T>
T Stack<T>::Peek() {
	T ret;
	ret = this->objects.GetAt(this->length - 1);
	return ret;
}

template<typename T>
Long Stack<T>::Init() {
	Long ret = -1;
	this->objects = Array<T>(1000);
	this->length = 0;
	this->capacity = 0;
	return ret;
}

template<typename T>
void Stack<T>::Search(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*)) {
	this->objects.LinerSearchDuplicate(key, indexes, count, compare);
}

template<typename T>
T& Stack<T>::operator[](Long index) {
	T ret;
	ret = this->objects[index];
	return ret;
}


template<typename T>
Long Stack<T>::GetCapacity() {
	return this->capacity;
}

template<typename T>
Long Stack<T>::GetLength() {
	return this->length;
}

template<typename T>
bool Stack<T>::IsEmpty() {
	bool ret = false;
	if (this->length <= 0) {
		ret = true;
	}
	return ret;
}




#endif // !_STACK_H
