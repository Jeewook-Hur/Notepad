//SingleByteCharacter.cpp
/*
* ���ϸ�Ī:SingleByteCharacter.cpp
* ���:�̱۹���Ʈ ����
* �ۼ���:������
* �ۼ�����:2022/6/30
*/
#include "SingleByteCharacter.h"
#include "Visitor.h"
#include<string>
using namespace std;

/*
* �Լ���Ī:SingleByteCharacter
* ���:������
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
* �Լ���Ī:~SingleByteCharacter
* ���:�Ҹ���
*/
SingleByteCharacter::~SingleByteCharacter() {
}

/*
* �Լ���Ī:IsEqual
* ���:������ ���Ѵ�
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
		if (oneChar >= 'a' && oneChar <= 'z') { //���� ���ڰ� �ҹ��ڸ� �빮�ڷ� ġȯ�Ѵ�. 
			oneChar = oneChar - 32;
		}
		if (otherChar >= 'a' && otherChar <= 'z') { //�ٸ� ���ڰ� �ҹ��ڸ� �빮�ڷ� ġȯ�Ѵ�. 
			otherChar = otherChar - 32;
		}
		if (oneChar == otherChar) { //�빮�ڷ� ġȯ�� ���� ������ 
			ret = true;
		}
	}
	return ret;
}

/*
* �Լ���Ī:IsNotEqual
* ���:������ ���Ѵ�
*/
bool SingleByteCharacter::IsNotEqual(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->content != other.content) {
		ret = true;
	}
	return ret;
}

/*
* �Լ���Ī:GetString
* ���:���ڿ� ���·� ��ȯ�Ѵ�.
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
		ret = string("        "); //��ĭ 16��
	}
	return ret;
}

/*
* �Լ���Ī:GetExactString
* ���:������ ���� �ڷᱸ���� ����� ��Ȯ�� �ƽ�Ű�ڵ��� ���ڸ� ���ڿ��� �����Ͽ� ����Ѵ�.
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
* �Լ���Ī:Clone
* ���:������Ÿ�� ���������� �����Ѵ�. 
*/
Glyph* SingleByteCharacter::Clone() {
	return new SingleByteCharacter(*this);
}

/*
* �Լ���Ī:Accept
* ���:Element�μ� Visitor�� Visit�� ����Ѵ�.
*/
void SingleByteCharacter::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* �Լ���Ī:operator==
* ���:������==
*/
bool SingleByteCharacter::operator==(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->content == other.content) {
		ret = true;
	}
	return ret;
}

/*
* �Լ���Ī:operator!=
* ���:������!=
*/
bool SingleByteCharacter::operator!=(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->content != other.content) {
		ret = true;
	}
	return ret;
}

/*
* �Լ���Ī:oprator=
* ���:ġȯ������
*/
SingleByteCharacter& SingleByteCharacter::operator=(const SingleByteCharacter& source) {
	this->content = source.content;
	return *this;
}

/*
* �Լ���Ī:GetByte
* ���:����Ʈ ���� ��ȯ�Ѵ�. 
*/
Long SingleByteCharacter::GetByte() {
	return 1;
}