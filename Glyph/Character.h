//Character.h
/*
* ���ϸ�Ī:Character.h
* ���:�߻�Ŭ���� ������ ���
* �ۼ���:������
* �ۼ�����:2022/6/30
*/
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include "Glyph.h"
#include<string>
using namespace std;

class Character : public Glyph{
public:
	Character();
	virtual ~Character() = 0;
	//virtual string GetString() = 0;
};

#endif // !_CHARACTER_H