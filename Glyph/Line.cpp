//Line.cpp
/*
* ���ϸ�Ī:Line.cpp
* ���:��
* �ۼ���:������
* �ۼ�����:2022/7/11
*/
#include "Line.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "GlyphCreater.h"
#include "Visitor.h"
#include<string>
using namespace std;

/*
* �Լ���Ī:Line
* ���:������
*/
Line::Line(Long capacity) :Composite(capacity) {
}
Line::Line(const Line& source) : Composite(source) {
}

/*
* �Լ���Ī:~Line
* ���:�Ҹ���
*/
Line::~Line() {
}

/*
* �Լ���Ī:PreviousWord
* ���:���� �ܾ�� �̵��Ѵ�.
*/
Long Line::PreviousWord() {
	Long length;
	Glyph* character = 0;
	string stringCharacter;
	Long index = -2; //��ȯ ��ġ
	Long order = -1;

	length = Composite::GetLength();
	if (length > 0) { //���ڰ� ����������
		//���� ��ġ�� Ȯ���Ѵ�.
		index = Composite::GetCurrent();
		//���� ������ ���ڸ� �����´�.
		order = index;
		if (order > -1) {//���ڰ� �����ϸ�
			character = Composite::GetAt(order);
			stringCharacter = character->GetString();
		}
		//�ǿ��� ���밡���ϰ� �Ѵ�. 
		//������ġ�� �� ���� �ƴϰ� ���ڰ� Ư�����ڸ�
		if (index > -1 &&
			(!(stringCharacter >= "0" && stringCharacter <= "9") && !(stringCharacter >= "A" && stringCharacter <= "Z") && !(stringCharacter >= "a" && stringCharacter <= "z") && stringCharacter <= "~")) {
			//������ġ�� �̵��Ѵ�.
			index = Composite::Previous();
			//���� ���ڷ� �̵��Ѵ�.
			order = index;
			if (order > -1) {//�ձ��ڰ� �����ϸ�
				character = Composite::GetAt(order);
				stringCharacter = character->GetString();
			}
		}
		//������ġ�� �� ���� �ƴϰ� ���ڰ� Ư�����ڰ� �ƴϸ�
		while (index > -1 && 
			((stringCharacter >= "0" && stringCharacter <= "9") || (stringCharacter >= "A" && stringCharacter <= "Z") || (stringCharacter >= "a" && stringCharacter <= "z") || stringCharacter > "~")) {
			//������ġ�� �̵��Ѵ�.
			index = Composite::Previous();
			//���� ���ڷ� �̵��Ѵ�.
			order = index;
			if (order > -1) {//�ձ��ڰ� �����ϸ�
				character = Composite::GetAt(order);
				stringCharacter = character->GetString();
			}
		}
	}
	else { //���ڰ� ������ ��ġ�� �� ���̴�. 
		index = -1;
	}
	//��ġ�� ����Ѵ�. 
	return index;
}

/*
* �Լ���Ī:NextWord
* ���:���� �ܾ�� �̵��Ѵ�
*/
Long Line::NextWord() {
	Long length;
	Glyph* character = 0;
	string stringCharacter;
	Long index = -2; //��ȯ ��ġ
	Long order = -1;

	length = Composite::GetLength();
	if (length > 0) { //���ڰ� ����������
		//���� ��ġ�� Ȯ���Ѵ�.
		index = Composite::GetCurrent();
		//���� ������ ������ ���ڸ� �����´�.
		order = index +1 ;
		if (order < length - 1) {//���ڰ� �����ϸ�
			character = Composite::GetAt(order);
			stringCharacter = character->GetString();
		}
		//stringCharacter == "\t"
		//������ġ�� �� �ڰ� �ƴϰ� ���ڰ� Ư�����ڰ� �ƴϸ�
		while (index < length - 1 && 
			((stringCharacter >= "0" && stringCharacter <= "9") || (stringCharacter >= "A" && stringCharacter <= "Z") || (stringCharacter >= "a" && stringCharacter <= "z") || stringCharacter > "~")) {
			//������ġ�� �̵��Ѵ�.
			index = Composite::Next();
			//���� ���ڷ� �̵��Ѵ�.
			order = index + 1;
			if (order < length - 1) {//�ڱ��ڰ� �����ϸ�
				//�ڿ� �ִ� ���ڸ� �����´�.
				character = Composite::GetAt(order);
				stringCharacter = character->GetString();
			}
		}
		//������ġ�� �� �ڰ� �ƴϰ� ���ڰ� Ư�����ڸ�
		if (index < length - 1 &&
			(!(stringCharacter >= "0" && stringCharacter <= "9") && !(stringCharacter >= "A" && stringCharacter <= "Z") && !(stringCharacter >= "a" && stringCharacter <= "z") && stringCharacter <= "~")) {
			//������ġ�� �̵��Ѵ�.
			index = Composite::Next();
			//���� ���ڷ� �̵��Ѵ�.
			order = index + 1;
			if (order < length) {//�ڱ��ڰ� �����ϸ�
				character = Composite::GetAt(order);
				stringCharacter = character->GetString();
			}
		}
	}
	else { //���ڰ� ������ ��ġ�� �� ���̴�. 
		index = -1;
	}
	//��ġ�� ����Ѵ�. 
	return index;
}


/*
* �Լ���Ī:Clone
* ���:������Ÿ�� ���������� �����Ѵ�
*/
Glyph* Line::Clone() {
	return new Line(*this);
}

/*
* �Լ���Ī:GetString
* ���:���� ���ڸ� �����´�.
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
* �Լ���Ī:GetExactString
* ���:������ ���� �ڷᱸ���� ����� ��Ȯ�� �ƽ�Ű�ڵ��� ���ڸ� ���ڿ��� �����Ͽ� ����Ѵ�.
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
* �Լ���Ī:Accept
* ���:Element�μ� Visitor�� Visit�� ����Ѵ�.
*/
void Line::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* �Լ���Ī:operator=
* ���:ġȯ������
*/
Line& Line::operator=(const Line& source) {
	Composite::operator=(source);
	return *this;
}

/*
* �Լ���Ī:operator[]
* ���:÷�ڿ�����
*/
Glyph* Line::operator[](Long order) {
	return this->GetAt(order);
}
