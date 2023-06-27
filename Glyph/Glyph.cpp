//Glyph.cpp
/*
* 파일명칭:Glyph.cpp
* 기능:추상클래스 글자
* 작성자:허지욱
* 작성일자:2022/7/11
*/
#include "Glyph.h"
#include "Visitor.h"
/*
* 함수명칭:Glyph
* 기능:생성자
*/
Glyph::Glyph() {
}

/*
* 함수명칭:~Glyph
* 기능:소멸자
*/
Glyph::~Glyph() {
}

/*
* 함수명칭:Add
* 기능:기재하다의 가상함수
*/
Long Glyph::Add(Glyph* glyph) {
	return -1;
}
Long Glyph::Add(Long order, Glyph* glyph) {
	return -1;
}
Long Glyph::Add(Glyph* other, Long orderToAdd) {
	return -1;
}
Long Glyph::Add(Glyph* paperToAdd, Long lineOrder, Long charIndex) {
	return - 1;
}


/*
* 함수명칭:GetAt
* 기능:가져오다의 가상함수
*/
Glyph* Glyph::GetAt(Long order) {
	return 0;
}

/*
* 함수명칭:Remove
* 기능:지우다의 가상함수
*/
Long Glyph::Remove(Long order) {
	return -1;
}
Long Glyph::Remove(Long startOrder, Long endOrder) {
	return -1;
}
Long Glyph::Remove(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex) {
	return -1;
}


/*
* 함수명칭:SplitDummyLine
* 기능:더미줄로 나누다의 가상함수
*/
Long Glyph::SplitDummyLine(Long lineOrder, Long characterIndex) {
	return -1;
}

/*
* 함수명칭:MergeAllDummyLines
* 기능:더미줄을 기존줄에 다 합치는 함수의 가상함수
*/
void Glyph::MergeAllDummyLines() {
}

/*
* 함수명칭:MergeDummyLines
* 기능:더미줄을 기존줄에 다 합치는 함수의 가상함수
*/
Long Glyph::MergeDummyLines(Long startlineOrder) {
	return -1;
}

/*
* 함수명칭:FindChar
* 기능:입력한 글자의 위치를 찾는다. 
*/
void Glyph::FindChar(Glyph* characterToFind, Long*(*lineOrders), Long*(*charOrders), Long* count) {
}
void Glyph::FindCharUpperLower(Glyph* characterToFind, Long* (*lineOrders), Long* (*charOrders), Long* count) {
}

/*
* 함수명칭:FindPaper
* 기능:입력한 종이와 일치하는 내용이 있는 위치를 찾는다. 
*/
void Glyph::FindPaper(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count) {
}
void Glyph::FindPaperUpperLower(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count) {
}




/*
* 함수명칭:Move
* 기능:입력된 위치로 이동한다.
*/
Long Glyph::Move(Long index) {
	return -2;
}

/*
* 함수명칭:First
* 기능:처음위치로 이동한다.
*/
Long Glyph::First() {
	return -2;
}

/*
* 함수명칭:Previous
* 기능:다음위치로 이동한다.
*/
Long Glyph::Previous() {
	return -2;
}

/*
* 함수명칭:Next
* 기능:이전 위치로 이동한다.
*/
Long Glyph::Next() {
	return -2;
}

/*
* 함수명칭:Last
* 기능:마지막 위치로 이동한다.
*/
Long Glyph::Last() {
	return -2;
}

/*
* 함수명칭:PreviousWord
* 기능:이전 단어로 이동한다.
*/
Long Glyph::PreviousWord() {
	return -2;
}

/*
* 함수명칭:NextWord
* 기능:다음 단어로 이동한다
*/
Long Glyph::NextWord() {
	return -2;
}

/*
* 함수명칭:GetLocation
* 기능:절대 위치를 구한다.
*/
void Glyph::GetLocation(Long lineOrder, Long charIndex, Long* lineLocation, Long* charLocation) {
}

/*
* 함수명칭:MoveToLocation
* 기능:절대 위치로 이동한다.
*/
void Glyph::MoveToLocation(Long lineLocation, Long charLocation, Long* lineOrder, Long* charIndex) {
}

/*
* 함수명칭:GetLength
* 기능:길이를 가져오다의 가상함수
*/
Long Glyph::GetLength() const {
	return -1;
}

/*
* 함수명칭:GetCapacity
* 기능:할당량을 가져오다의 가상함수
*/
Long Glyph::GetCapacity() const {
	return -1;
}

/*
* 함수명칭:GetCurrent
* 기능:현재 위치를 가져오다의 가상함수
*/
Long Glyph::GetCurrent() const {
	return -1;
}

/*
* 함수명칭:GetByte
* 기능:글자일경우 바이트수를 반환한다
*/
Long Glyph::GetByte() const {
	return 0;
}

/*
* 함수명칭:Clone
* 기능:입력된 범위의 복사본을 만들어 반환한다.
*/
Glyph* Glyph::Clone(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex) {
	return 0;
}

/*
* 함수명칭:Accept
* 기능:Element로서 Visitor의 Visit를 허용한다. 
*/
void Glyph::Accept(Visitor* visitor) {
}

/*
* 함수명칭:IsEqual
* 기능:입력값이 같은지 비교하는 가상함수
*/
BOOL Glyph::IsEqual(Long previousLineOrder, Long previousCharIndex) {
	return 0;
}
BOOL Glyph::IsEqual(Glyph* other) {
	return 0;
}
BOOL Glyph::IsEqualUpperLower(Glyph* other) {
	return 0;
}


/*
* 함수명칭:IsNotEqual
* 기능:입력값이 다른지 비교하는 가상함수
*/
BOOL Glyph::IsNotEqual(Long previousLineOrder, Long previousCharIndex) {
	return 0;
}

/*
* 함수명칭:GetCharNumber
* 기능:종이에 속하는 총 글자수를 계산하는 함수
*/
Long Glyph::GetCharNumber() {
	return -1;
}
