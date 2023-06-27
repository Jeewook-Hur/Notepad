//Composite.cpp
/*
* 파일명칭:Composite.cpp
* 기능:추상클래스 합성
* 작성자:허지욱
* 작성일자:2022/7/11
*/
#include "Composite.h"

/*
* 함수명칭:Composite
* 기능:생성자
*/
Composite::Composite(Long capacity) :glyphes(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}
Composite::Composite(const Composite& source) : glyphes(source.glyphes) {
	Long i = 0;
	Glyph* glyph = 0;
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
	
	while (i < this->length) {
		glyph = this->glyphes[i]->Clone();
		this->glyphes.Modify(i, glyph);
		i++;
	}
}

/*
* 함수명칭:~Composite
* 기능:소멸자
*/
Composite::~Composite() {
	Long i = 0;
	while (i < this->length) {
		delete this->glyphes[i];
		i++;
	}
}

/*
* 함수명칭:Add
* 기능:기재하다
*/
Long Composite::Add(Glyph* glyph) {
	Long order = -1;
	if (this->current < this->length - 1) { //현재 위치가 맨뒤가 아니면 
		order = this->glyphes.Insert(this->current + 1, glyph);
		this->capacity++;
	}
	else { //현재 위치가 맨 뒤일때 
		if (this->length < this->capacity) {
			order = this->glyphes.Store(this->length, glyph);
		}
		else if (this->length >= this->capacity) {
			order = this->glyphes.AppendFromRear(glyph);
			this->capacity++;
		}
	}
	this->length++;
	this->current++;
	return order;
}
Long Composite::Add(Long order, Glyph* glyph) { //order는 순서 
	Long index = -2; //위치
	order = this->glyphes.Insert(order, glyph);
	this->length++;
	this->capacity++;
	index = order;
	this->current = index;
	return index;
}
Long Composite::Add(Glyph* other, Long orderToAdd) { //같은 자료형의 Glyph를 합칠때 
	Glyph* branch = 0;
	Glyph* clone = 0;
	Long length = other->GetLength();
	Long order = orderToAdd;
	Long index = -2;
	Long i = 0;
	Long thisLength = this->GetLength();

	if (orderToAdd <= thisLength - 1) {
		while (i < length) {
			branch = other->GetAt(i);
			clone = branch->Clone();
			this->Add(order, clone);
			order++;
			i++;
		}
	}
	else {
		while (i < length) {
			branch = other->GetAt(i);
			this->Last();
			this->Add(branch->Clone());
			order++;
			i++;
		}
	}
	index = order - 1; 
	index = this->Move(index);
	return index;
}

/*
* 함수명칭:GetAt
* 기능:가져오다
*/
Glyph* Composite::GetAt(Long order) {
	return this->glyphes.GetAt(order);
}

/*
* 함수명칭:Remove
* 기능:지우다
*/
Long Composite::Remove(Long order) { //지울 순서을 입력받는다.
	Long index = -2;
	//순서에 있는 글리피의 힙 할당 영역을 지운다.
	delete this->glyphes[order];
	//배열에서 순서의 주소를 지운다. 
	this->glyphes.Delete(order);
	this->capacity--;
	this->length--;
	//위치를 갱신한다.
	index = order - 1;
	this->current = index;
	//변경된 위치를 반환하다. 
	return index;
}
/*
* 함수명칭:Remove
* 기능:입력받은 범위(시작위치부터 끝위치까지)의 내용을 제거한다.
* 입력:시작위치(중요), 끝위치
* 출력:현재위치
*/
Long Composite::Remove(Long startOrder, Long endOrder) { //윈칙적으로 순서보다 위치의 자료를 빼는것이 맞기에 위치를 기준으로 했다. 
	Long length = endOrder - startOrder + 1;
	Long index = 0;
	Long i = 0;

	while (i < length) {
		index = this->Remove(startOrder);
		i++;
	}
	return index;
}


/*
* 함수명칭:Move
* 기능:입력된 위치로 이동한다.
*/
Long Composite::Move(Long index) {
	this->current = index;
	return this->current;
}

/*
* 함수명칭:First
* 기능:처음위치로 이동한다.
*/
Long Composite::First() {
	this->current = -1;
	return this->current;
}

/*
* 함수명칭:Previous
* 기능:다음위치로 이동한다.
*/
Long Composite::Previous() {
	this->current--;
	if (this->current < -1) {
		this->current = -1;
	}
	return this->current;
}

/*
* 함수명칭:Next
* 기능:이전 위치로 이동한다.
*/
Long Composite::Next() {
	this->current++;
	if (this->current >= this->length) {
		this->current = this->length - 1;
	}
	return this->current;
}

/*
* 함수명칭:Last
* 기능:마지막 위치로 이동한다.
*/
Long Composite::Last() {
	this->current = this->length - 1;
	return this->current;

}

/*
* 함수명칭:operator=
* 기능:치환연산자
*/
Composite& Composite::operator=(const Composite& source) {
	Long i = 0;
	Glyph* glyph = 0;

	this->glyphes = source.glyphes;
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	while (i < this->length) {
		glyph = this->glyphes[i]->Clone();
		this->glyphes.Modify(i, glyph);
		i++;
	}
	return *this;
}

/*
* 함수명칭:operator[]
* 기능:첨자연산자
*/
Glyph* Composite::operator[](Long order) {
	return this->glyphes[order];
}
