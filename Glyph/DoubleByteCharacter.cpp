//DoubleByteCharacter.cpp
/*
* 파일명칭:DoubleByteCharacter.cpp
* 기능:더블바이트 문자
* 작성자:허지욱
* 작성일자:2022/6/30
*/
#include "DoubleByteCharacter.h"
#include "Visitor.h"
#include<string>
using namespace std;

/*
* 함수명칭:DoubleByteCharacter
* 기능:생성자
*/
DoubleByteCharacter::DoubleByteCharacter() {
	this->contents[0] = ' '; //띄어쓰기 빈 문자
	this->contents[1] = ' ';
}
DoubleByteCharacter::DoubleByteCharacter(char(*contents)) {
	this->contents[0] = contents[0];
	this->contents[1] = contents[1];
}
DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source) {
	this->contents[0] = source.contents[0];
	this->contents[1] = source.contents[1];
}

/*
* 함수명칭:~DoubleByteCharacter
* 기능:소멸자
*/
DoubleByteCharacter::~DoubleByteCharacter() {
}

/*
* 함수명칭:Accept
* 기능:Element로서 Visitor의 Visit를 허용한다.
*/
void DoubleByteCharacter::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* 함수명칭:IsEqual
* 기능:같은지 비교한다
*/
bool DoubleByteCharacter::IsEqual(const DoubleByteCharacter& other) {
	bool ret = false;
	if (this->contents[0] == other.contents[0]
		&& this->contents[1] == other.contents[1]) {
		ret = true;
	}
	return ret;
}
BOOL DoubleByteCharacter::IsEqual(Glyph* other) {
	BOOL ret = 0;
	bool ret2 = false;
	if (dynamic_cast<DoubleByteCharacter*>(other)) {
		ret2 = this->IsEqual(*dynamic_cast<DoubleByteCharacter*>(other));
	}
	if (ret2 == true) {
		ret = 1;
	}
	return ret;
}
BOOL DoubleByteCharacter::IsEqualUpperLower(Glyph* other) {
	return this->IsEqual(other);
}


/*
* 함수명칭:IsNotEqual
* 기능:다른지 비교한다
*/
bool DoubleByteCharacter::IsNotEqual(const DoubleByteCharacter& other) {
	bool ret = false;
	if (this->contents[0] != other.contents[0]
		|| this->contents[1] != other.contents[1]) {
		ret = true;
	}
	return ret;
}

/*
* 함수명칭:GetString
* 기능:문자열로 반환한다
*/
string DoubleByteCharacter::GetString() {
	char buffer[3];
	buffer[0] = this->contents[0];
	buffer[1] = this->contents[1];
	buffer[2] = '\0';
	return string(buffer);
}

/*
* 함수명칭:GetExactString
* 기능:저장을 위해 자료구조에 저장된 정확한 아스키코드의 문자를 문자열에 저장하여 출력한다.
*/
string DoubleByteCharacter::GetExactString() {
	char buffer[3];
	buffer[0] = this->contents[0];
	buffer[1] = this->contents[1];
	buffer[2] = '\0';
	return string(buffer);
}


/*
* 함수명칭:Clone
* 기능:프로토타입 글자형으로 복제한다.
*/
Glyph* DoubleByteCharacter::Clone() {
	return new DoubleByteCharacter(*this);
}

/*
* 함수명칭:operator==
* 기능:연산자==
*/
bool DoubleByteCharacter::operator==(const DoubleByteCharacter& other) {
	bool ret = false;
	if (this->contents[0] == other.contents[0]
		&& this->contents[1] == other.contents[1]) {
		ret = true;
	}
	return ret;
}

/*
* 함수명칭:operator!=
* 기능:연산자!=
*/
bool DoubleByteCharacter::operator!=(const DoubleByteCharacter& other) {
	bool ret = false;
	if (this->contents[0] != other.contents[0]
		|| this->contents[1] != other.contents[1]) {
		ret = true;
	}
	return ret;
}

/*
* 함수명칭:operator=
* 기능:치환연산자
*/
DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	this->contents[0] = source.contents[0];
	this->contents[1] = source.contents[1];
	return *this;
}

/*
* 함수명칭:GetByte
* 기능:바이트 수를 반환한다.
*/
Long DoubleByteCharacter::GetByte() {
	return 2;
}