//Character.h
/*
* 파일명칭:Character.h
* 기능:추상클래스 문자의 헤더
* 작성자:허지욱
* 작성일자:2022/6/30
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