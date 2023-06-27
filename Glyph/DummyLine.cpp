 //DummyLine.cpp
/*
* 함수명칭:DummyLine.cpp
* 기능:더미 라인
* 작성자:허지욱
* 작성일자:20220919
*/
#include "DummyLine.h"
#include "Visitor.h"

/*
* 함수명칭:DummyLine
* 기능:생성자
*/
DummyLine::DummyLine(Long capacity) :Line(capacity) {
}
DummyLine::DummyLine(const DummyLine& source) : Line(source) {
}

/*
* 함수명칭:~DummyLine
* 기능:소멸자
*/
DummyLine::~DummyLine() {
}

/*
* 함수명칭:Accept
* 기능:Element로서 Visitor의 Visit를 허용한다.
*/
void DummyLine::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* 함수명칭:Clone
* 기능:프로토타입 글자형으로 복제한다
*/
Glyph* DummyLine::Clone() {
	return new DummyLine(*this);
}