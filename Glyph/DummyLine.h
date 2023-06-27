//DummyLine.h
/*
* 함수명칭:DummyLine.h
* 기능:더미 라인의 헤더
* 작성자:허지욱
* 작성일자:20220919
*/
#ifndef _DUMMYLINE_H
#define _DUMMYLINE_H
#include "Line.h"

class DummyLine : public Line {
public:
	DummyLine(Long capacity = 1000);
	DummyLine(const DummyLine& source);
	virtual ~DummyLine();
	virtual void Accept(Visitor* visitor);
	virtual Glyph* Clone();
};

#endif // !_DUMMYLINE_H