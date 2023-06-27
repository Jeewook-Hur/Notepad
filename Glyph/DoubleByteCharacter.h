//DoubleByteCharacter.h
/*
* ���ϸ�Ī:DoubleByteCharacter.h
* ���:�������Ʈ ������ ���
* �ۼ���:������
* �ۼ�����:2022/6/30
*/
#ifndef _DOUBLEBYTECHARACTER_H
#define _DOUBLEBYTECHARACTER_H
#include "Character.h"
#include<string>
using namespace std;

class DoubleByteCharacter : public Character {
public:
	DoubleByteCharacter();
	DoubleByteCharacter(char(*contents));
	DoubleByteCharacter(const DoubleByteCharacter& source);
	virtual ~DoubleByteCharacter();
	bool IsEqual(const DoubleByteCharacter& other);
	virtual BOOL IsEqual(Glyph* other);
	virtual BOOL IsEqualUpperLower(Glyph* other);
	bool IsNotEqual(const DoubleByteCharacter& other);
	virtual string GetExactString();
	virtual string GetString();
	virtual Glyph* Clone();
	virtual void Accept(Visitor* visitor);
	DoubleByteCharacter& operator=(const DoubleByteCharacter& source);
	bool operator==(const DoubleByteCharacter& other);
	bool operator!=(const DoubleByteCharacter& other);
	char* GetContents() const;
	virtual Long GetByte();
private:
	char contents[2];
};

inline char* DoubleByteCharacter::GetContents() const {
	return const_cast<char*>(this->contents); //�Լ��� ������ ��ȯ������ const_cast
}

#endif // !_DOUBLEBYTECHARACTER_H