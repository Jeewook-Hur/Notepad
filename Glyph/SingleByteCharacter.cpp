//SingleByteCharacter.cpp
/*
* 파일명칭:SingleByteCharacter.cpp
* 기능:싱글바이트 문자
* 작성자:허지욱
* 작성일자:2022/6/30
*/
#include "SingleByteCharacter.h"
#include "Visitor.h"
#include<string>
using namespace std;

/*
* 함수명칭:SingleByteCharacter
* 기능:생성자
*/
SingleByteCharacter::SingleByteCharacter() {
	this->content = ' ';
}
SingleByteCharacter::SingleByteCharacter(char content) {
	this->content = content;
}
SingleByteCharacter::SingleByteCharacter(const SingleByteCharacter& source) {
	this->content = source.content;
}

/*
* 함수명칭:~SingleByteCharacter
* 기능:소멸자
*/
SingleByteCharacter::~SingleByteCharacter() {
}

/*
* 함수명칭:IsEqual
* 기능:같은지 비교한다
*/
bool SingleByteCharacter::IsEqual(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->content == other.content) {
		ret = true;
	}
	return ret;
}
BOOL SingleByteCharacter::IsEqual(Glyph* other) {
	BOOL ret = 0;
	bool ret2 = false;
	if (dynamic_cast<SingleByteCharacter*>(other)) {
		ret2 = this->IsEqual(*dynamic_cast<SingleByteCharacter*>(other));
	}
	if (ret2 == true) {
		ret = 1;
	}
	return ret;
}
BOOL SingleByteCharacter::IsEqualUpperLower(Glyph* other) {
	BOOL ret = 0;
	char oneChar;
	char otherChar;
	oneChar = this->content;
	SingleByteCharacter* character;
	if (dynamic_cast<SingleByteCharacter*>(other)) {
		character = dynamic_cast<SingleByteCharacter*>(other);
		otherChar = character->content;
		if (oneChar >= 'a' && oneChar <= 'z') { //현재 문자가 소문자면 대문자로 치환한다. 
			oneChar = oneChar - 32;
		}
		if (otherChar >= 'a' && otherChar <= 'z') { //다른 문자가 소문자면 대문자로 치환한다. 
			otherChar = otherChar - 32;
		}
		if (oneChar == otherChar) { //대문자로 치환한 둘이 같으면 
			ret = true;
		}
	}
	return ret;
}

/*
* 함수명칭:IsNotEqual
* 기능:같은지 비교한다
*/
bool SingleByteCharacter::IsNotEqual(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->content != other.content) {
		ret = true;
	}
	return ret;
}

/*
* 함수명칭:GetString
* 기능:문자열 형태로 반환한다.
*/
string SingleByteCharacter::GetString() {
	char buffer[2];
	string ret;
	char blank = 32;

	if (this->content != '\t') {
		buffer[0] = this->content;
		buffer[1] = '\0';
		ret = string(buffer);
	}
	else {
		ret = string("        "); //빈칸 16개
	}
	return ret;
}

/*
* 함수명칭:GetExactString
* 기능:저장을 위해 자료구조에 저장된 정확한 아스키코드의 문자를 문자열에 저장하여 출력한다.
*/
string SingleByteCharacter::GetExactString() {
	char buffer[2];
	string ret;
	char blank = 32;

	buffer[0] = this->content;
	buffer[1] = '\0';
	ret = string(buffer);
	return ret;
}


/*
* 함수명칭:Clone
* 기능:프로토타입 글자형으로 복제한다. 
*/
Glyph* SingleByteCharacter::Clone() {
	return new SingleByteCharacter(*this);
}

/*
* 함수명칭:Accept
* 기능:Element로서 Visitor의 Visit를 허용한다.
*/
void SingleByteCharacter::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* 함수명칭:operator==
* 기능:연산자==
*/
bool SingleByteCharacter::operator==(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->content == other.content) {
		ret = true;
	}
	return ret;
}

/*
* 함수명칭:operator!=
* 기능:연산자!=
*/
bool SingleByteCharacter::operator!=(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->content != other.content) {
		ret = true;
	}
	return ret;
}

/*
* 함수명칭:oprator=
* 기능:치환연산자
*/
SingleByteCharacter& SingleByteCharacter::operator=(const SingleByteCharacter& source) {
	this->content = source.content;
	return *this;
}

/*
* 함수명칭:GetByte
* 기능:바이트 수를 반환한다. 
*/
Long SingleByteCharacter::GetByte() {
	return 1;
}