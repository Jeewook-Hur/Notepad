//Line.h
/*
* 파일명칭:Line.h
* 기능:줄의 헤더
* 작성자:허지욱
* 작성일자:2022/7/11
*/
#ifndef _LINE_H
#define _LINE_H
#include "Composite.h"
#include<string>
using namespace std;

class Line : public Composite {
public:
	Line(Long capacity = 1000);
	Line(const Line& source);
	virtual ~Line();

	virtual Long PreviousWord();
	virtual Long NextWord();

	virtual Glyph* Clone();
	virtual string GetString();
	virtual string GetExactString();

	virtual void Accept(Visitor* visitor);

	Line& operator=(const Line& source);
	Glyph* operator[](Long order);
};

#endif // !_LINE_H
