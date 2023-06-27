//Line.cpp
/*
* 파일명칭:Line.cpp
* 기능:줄
* 작성자:허지욱
* 작성일자:2022/7/11
*/
#include "Line.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "GlyphCreater.h"
#include "Visitor.h"
#include<string>
using namespace std;

/*
* 함수명칭:Line
* 기능:생성자
*/
Line::Line(Long capacity) :Composite(capacity) {
}
Line::Line(const Line& source) : Composite(source) {
}

/*
* 함수명칭:~Line
* 기능:소멸자
*/
Line::~Line() {
}

/*
* 함수명칭:PreviousWord
* 기능:이전 단어로 이동한다.
*/
Long Line::PreviousWord() {
	Long length;
	Glyph* character = 0;
	string stringCharacter;
	Long index = -2; //반환 위치
	Long order = -1;

	length = Composite::GetLength();
	if (length > 0) { //글자가 적혀있으면
		//현재 위치를 확인한다.
		index = Composite::GetCurrent();
		//현재 순서의 글자를 가져온다.
		order = index;
		if (order > -1) {//글자가 존재하면
			character = Composite::GetAt(order);
			stringCharacter = character->GetString();
		}
		//탭에도 적용가능하게 한다. 
		//현재위치가 맨 앞이 아니고 글자가 특수문자면
		if (index > -1 &&
			(!(stringCharacter >= "0" && stringCharacter <= "9") && !(stringCharacter >= "A" && stringCharacter <= "Z") && !(stringCharacter >= "a" && stringCharacter <= "z") && stringCharacter <= "~")) {
			//이전위치로 이동한다.
			index = Composite::Previous();
			//이전 글자로 이동한다.
			order = index;
			if (order > -1) {//앞글자가 존재하면
				character = Composite::GetAt(order);
				stringCharacter = character->GetString();
			}
		}
		//현재위치가 맨 앞이 아니고 글자가 특수문자가 아니면
		while (index > -1 && 
			((stringCharacter >= "0" && stringCharacter <= "9") || (stringCharacter >= "A" && stringCharacter <= "Z") || (stringCharacter >= "a" && stringCharacter <= "z") || stringCharacter > "~")) {
			//이전위치로 이동한다.
			index = Composite::Previous();
			//이전 글자로 이동한다.
			order = index;
			if (order > -1) {//앞글자가 존재하면
				character = Composite::GetAt(order);
				stringCharacter = character->GetString();
			}
		}
	}
	else { //글자가 없으면 위치는 맨 앞이다. 
		index = -1;
	}
	//위치를 출력한다. 
	return index;
}

/*
* 함수명칭:NextWord
* 기능:다음 단어로 이동한다
*/
Long Line::NextWord() {
	Long length;
	Glyph* character = 0;
	string stringCharacter;
	Long index = -2; //반환 위치
	Long order = -1;

	length = Composite::GetLength();
	if (length > 0) { //글자가 적혀있으면
		//현재 위치를 확인한다.
		index = Composite::GetCurrent();
		//현재 순서의 다음의 글자를 가져온다.
		order = index +1 ;
		if (order < length - 1) {//글자가 존재하면
			character = Composite::GetAt(order);
			stringCharacter = character->GetString();
		}
		//stringCharacter == "\t"
		//현재위치가 맨 뒤가 아니고 글자가 특수문자가 아니면
		while (index < length - 1 && 
			((stringCharacter >= "0" && stringCharacter <= "9") || (stringCharacter >= "A" && stringCharacter <= "Z") || (stringCharacter >= "a" && stringCharacter <= "z") || stringCharacter > "~")) {
			//다음위치로 이동한다.
			index = Composite::Next();
			//다음 글자로 이동한다.
			order = index + 1;
			if (order < length - 1) {//뒤글자가 존재하면
				//뒤에 있는 글자를 가져온다.
				character = Composite::GetAt(order);
				stringCharacter = character->GetString();
			}
		}
		//현재위치가 맨 뒤가 아니고 글자가 특수문자면
		if (index < length - 1 &&
			(!(stringCharacter >= "0" && stringCharacter <= "9") && !(stringCharacter >= "A" && stringCharacter <= "Z") && !(stringCharacter >= "a" && stringCharacter <= "z") && stringCharacter <= "~")) {
			//다음위치로 이동한다.
			index = Composite::Next();
			//다음 글자로 이동한다.
			order = index + 1;
			if (order < length) {//뒤글자가 존재하면
				character = Composite::GetAt(order);
				stringCharacter = character->GetString();
			}
		}
	}
	else { //글자가 없으면 위치는 맨 앞이다. 
		index = -1;
	}
	//위치를 출력한다. 
	return index;
}


/*
* 함수명칭:Clone
* 기능:프로토타입 글자형으로 복제한다
*/
Glyph* Line::Clone() {
	return new Line(*this);
}

/*
* 함수명칭:GetString
* 기능:줄의 문자를 가져온다.
*/
string Line::GetString() {
	Glyph* glyph = 0;
	string ret = "";
	string addRear;
	Long i = 0;
	Long length; 
	length = this->GetLength();
	while (i < length) {
		glyph = this->GetAt(i);
		addRear = glyph->GetString();
		ret = ret + addRear;
		i++;
	}
	return ret;
}

/*
* 함수명칭:GetExactString
* 기능:저장을 위해 자료구조에 저장된 정확한 아스키코드의 문자를 문자열에 저장하여 출력한다.
*/
string Line::GetExactString() {
	Glyph* glyph = 0;
	string ret = "";
	string addRear;
	Long i = 0;
	Long length;
	length = this->GetLength();
	while (i < length) {
		glyph = this->GetAt(i);
		addRear = glyph->GetExactString();
		ret = ret + addRear;
		i++;
	}
	return ret;
}

/*
* 함수명칭:Accept
* 기능:Element로서 Visitor의 Visit를 허용한다.
*/
void Line::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* 함수명칭:operator=
* 기능:치환연산자
*/
Line& Line::operator=(const Line& source) {
	Composite::operator=(source);
	return *this;
}

/*
* 함수명칭:operator[]
* 기능:첨자연산자
*/
Glyph* Line::operator[](Long order) {
	return this->GetAt(order);
}
