//SingleByteCharacter.h
/*
* ���ϸ�Ī:SingleByteCharacter.h
* ���:�̱۹���Ʈ ������ ���
* �ۼ���:������
* �ۼ�����:2022/6/30
*/
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H
#include "Character.h"
#include<string>
using namespace std;

class SingleByteCharacter : public Character {
public:
	SingleByteCharacter();
	SingleByteCharacter(char content);
	SingleByteCharacter(const SingleByteCharacter& source);
	virtual ~SingleByteCharacter();
	bool IsEqual(const SingleByteCharacter& other);
	virtual BOOL IsEqual(Glyph* other);
	virtual BOOL IsEqualUpperLower(Glyph* other);
	bool IsNotEqual(const SingleByteCharacter& other);
	virtual string GetString();
	virtual string GetExactString();

	virtual Glyph* Clone();
	virtual void Accept(Visitor* visitor);
	SingleByteCharacter& operator=(const SingleByteCharacter& source);
	bool operator==(const SingleByteCharacter& other);
	bool operator!=(const SingleByteCharacter& other);
	char GetContent() const;
	virtual Long GetByte();
private:
	char content;
};

inline char SingleByteCharacter::GetContent() const {
	return this->content;
}

#endif // !_SINGLEBYTECHARACTER_H