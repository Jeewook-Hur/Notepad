//Array.h
/*
파일명칭:Array.h
기능:배열라이브러리의 헤더
작성자:허지욱
작성일자:2022/1/13
*/
//약 720줄 4시간정도 소요
#ifndef _ARRAY_H
#define _ARRAY_H
typedef signed long int Long;

template<typename T>
class Array {
public:
	Array(Long capacity = 256);
	~Array();
	Array(const Array& source); // 복사생성자
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinerSearchUnique(void* key, int(*compare)(void*, void*));
	void LinerSearchDuplicate(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void* key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void Merge(const Array& one, const Array& other, int(*compare)(void*, void*));
	T& GetAt(Long index);
	Array& operator=(const Array& source); //치환연산자.
	T& operator[](Long index);
	T* operator+(Long index);
	Long GetCapacity() const;
	Long GetLength() const;
private:
	T(*front);
	Long capacity;
	Long length;
};

template<typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}

template<typename T>
Array<T>::Array(const Array& source) {
	Long i = 0;
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

template<typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[] this->front;
	}
}

template<typename T>
Long Array<T>::Store(Long index, T object) {
	this->front[index] = object;
	this->length++;
	return index;
}

template<typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*temps) = 0;
	Long i = 0;
	Long j = 0;
	temps = new T[this->capacity + 1];
	while (j < index) {
		temps[i] = this->front[j];
		i++;
		j++;
	}
	i++;
	while (j < this->length) {
		temps[i] = this->front[j];
		i++;
		j++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temps;
	this->capacity++;
	this->front[index] = object;
	this->length++;
	return index;
}

template<typename T>
Long Array<T>::AppendFromFront(T object) {
	Long index = -1;
	T(*temps) = 0;
	Long i = 0;
	temps = new T[this->capacity + 1];
	while (i < this->capacity) {
		temps[i + 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temps;
	this->capacity++;
	index = 0;
	this->front[index] = object;
	this->length++;
	return index;
}

template<typename T>
Long Array<T>::AppendFromRear(T object) {
	Long index = -1;
	T(*temps) = 0;
	Long i = 0;
	temps = new T[this->capacity + 1];
	while (i < this->capacity) {
		temps[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temps;
	this->capacity++;
	index = this->capacity - 1;
	this->front[index] = object;
	this->length++;
	return index;
}

template<typename T>
Long Array<T>::Delete(Long index) {
	T(*temps) = 0;
	Long i = 0;
	Long j = 0;
	if (this->capacity > 1) {
		temps = new T[this->capacity - 1];
	}
	while (i < index) {
		temps[j] = this->front[i];
		j++;
		i++;
	}
	i++;
	while (i < this->capacity) {
		temps[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temps;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

template<typename T>
Long Array<T>::DeleteFromFront() {
	Long index;
	T(*temps) = 0;
	Long i = 1;
	if (this->capacity > 1) {
		temps = new T[this->capacity - 1];
	}
	while (i < this->length) {
		temps[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temps;
	}
	this->capacity--;
	this->length--;
	index = -1;
	return index;
}

template<typename T>
Long Array<T>::DeleteFromRear() {
	Long index;
	T(*temps) = 0;
	Long i = 0;
	if (this->capacity > 1) {
		temps = new T[this->capacity - 1];
	}
	while (i < this->capacity - 1) {
		temps[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temps;
	}
	this->capacity--;
	this->length--;
	index = -1;
	return index;
}

template<typename T>
void Array<T>::Clear(){
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	this->length = 0;
	this->capacity = 0;
}

template<typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;
	return index;
}

template<typename T>
Long Array<T>::LinerSearchUnique(void* key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;
	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	if (i < this->length) {
		index = i;
	}
	return index;
}

template<typename T>
void Array<T>::LinerSearchDuplicate(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	*count = 0;
	*indexes = new Long[this->capacity];
	while (i < this->length) {
		if (compare(this->front + i, key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}

template<typename T>
Long Array<T>::BinarySearchUnique(void* key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long front = 0;
	Long middle;
	Long end = this->length - 1;
	middle = (front + end) / 2;
	while (front <= end && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) > 0) {
			end = middle - 1;
		}
		else {
			front = middle + 1;
		}
		middle = (front + end) / 2;
	}
	if (front <= end) {
		index = middle;
	}
	return index;
}

template<typename T>
void Array<T>::BinarySearchDuplicate(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*)) {
	Long front = 0;
	Long middle;
	Long end;
	Long i = 0;
	(*count) = 0;
	end = this->length - 1;
	middle = (front + end) / 2;
	while (front <= end && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) > 0) {
			end = middle - 1;
		}
		else {
			front = middle + 1;
		}
		middle = (front + end) / 2;
	}
	middle--;
	while (middle >= 0 && compare(this->front + middle, key) == 0) {
		middle--;
	}
	*indexes = new Long[this->length];
	middle++;
	while (middle < this->length && compare(this->front + middle, key) == 0) {
		(*indexes)[i] = middle;
		i++;
		(*count)++;
		middle++;
	}
}

template<typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	Long minimum;
	T temp;
	while (i < this->length - 1) {
		minimum = i;
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + minimum, this->front + j) > 0) {
				minimum = j;
			}
			j++;
		}
		temp = this->front[minimum];
		this->front[minimum] = this->front[i];
		this->front[i] = temp;
		i++;
	}
}

template<typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 0;
	Long j;
	Long flag = 1;
	while (i < this->length - 1 && flag == 1) {
		flag = 0;
		j = this->length - 1;
		while (j > i) {
			if (compare(this->front + j, this->front + (j - 1)) < 0) {
				temp = this->front[j];
				this->front[j] = this->front[j - 1];
				this->front[j - 1] = temp;
				flag = 1;
			}
			j--;
		}
		i++;
	}
}

template<typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 1;
	Long j;
	while (i < this->length) { //2022/2/10 오류 발견으로 수정
		temp = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, &temp) > 0) {
			this->front[j + 1] = this->front[j];
			j--;
		}
		this->front[j + 1] = temp;
		i++;
	}
}

template<typename T>
void Array<T>::Merge(const Array& one, const Array& other, int(*compare)(void*, void*)) {
	Long capacity;
	Long i = 0;
	Long j = 0;
	Long k = 0;
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	capacity = one.length + other.length;
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j) <= 0) {
			this->front[k] = one.front[i];
			k++;
			i++;
		}
		else {
			this->front[k] = other.front[j];
			k++;
			j++;
		}
	}
	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		i++;
	}
	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}
	this->length = capacity;
}

template<typename T>
T& Array<T>::GetAt(Long index) {
	return this->front[index];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& source) {
	Long i = 0;
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}

template<typename T>
T& Array<T>::operator[](Long index) {
	return this->front[index];
}

template<typename T>
T* Array<T>::operator+(Long index) {
	return this->front + index;
}


template<typename T>
inline Long Array<T>::GetCapacity() const {
	return this->capacity;
}

template<typename T>
inline Long Array<T>::GetLength() const {
	return this->length;
}

#endif // _ARRAY_H