//DoubleByteCharacter.cpp
/*
* ���ϸ�Ī:DoubleByteCharacter.cpp
* ���:�������Ʈ ����
* �ۼ���:������
* �ۼ�����:2022/6/30
*/
#include "DoubleByteCharacter.h"
#include "Visitor.h"
#include<string>
using namespace std;

/*
* �Լ���Ī:DoubleByteCharacter
* ���:������
*/
DoubleByteCharacter::DoubleByteCharacter() {
	this->contents[0] = ' '; //���� �� ����
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
* �Լ���Ī:~DoubleByteCharacter
* ���:�Ҹ���
*/
DoubleByteCharacter::~DoubleByteCharacter() {
}

/*
* �Լ���Ī:Accept
* ���:Element�μ� Visitor�� Visit�� ����Ѵ�.
*/
void DoubleByteCharacter::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* �Լ���Ī:IsEqual
* ���:������ ���Ѵ�
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
* �Լ���Ī:IsNotEqual
* ���:�ٸ��� ���Ѵ�
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
* �Լ���Ī:GetString
* ���:���ڿ��� ��ȯ�Ѵ�
*/
string DoubleByteCharacter::GetString() {
	char buffer[3];
	buffer[0] = this->contents[0];
	buffer[1] = this->contents[1];
	buffer[2] = '\0';
	return string(buffer);
}

/*
* �Լ���Ī:GetExactString
* ���:������ ���� �ڷᱸ���� ����� ��Ȯ�� �ƽ�Ű�ڵ��� ���ڸ� ���ڿ��� �����Ͽ� ����Ѵ�.
*/
string DoubleByteCharacter::GetExactString() {
	char buffer[3];
	buffer[0] = this->contents[0];
	buffer[1] = this->contents[1];
	buffer[2] = '\0';
	return string(buffer);
}


/*
* �Լ���Ī:Clone
* ���:������Ÿ�� ���������� �����Ѵ�.
*/
Glyph* DoubleByteCharacter::Clone() {
	return new DoubleByteCharacter(*this);
}

/*
* �Լ���Ī:operator==
* ���:������==
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
* �Լ���Ī:operator!=
* ���:������!=
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
* �Լ���Ī:operator=
* ���:ġȯ������
*/
DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	this->contents[0] = source.contents[0];
	this->contents[1] = source.contents[1];
	return *this;
}

/*
* �Լ���Ī:GetByte
* ���:����Ʈ ���� ��ȯ�Ѵ�.
*/
Long DoubleByteCharacter::GetByte() {
	return 2;
}