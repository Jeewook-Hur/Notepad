//PrintVisitor.h
/*
* 파일명칭:PrintVisitor.h
* 기능:프린트 용지에 출력하는 콘크리트 비지터 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/12/16
*/
#ifndef _PAINTVISITOR_H
#define _PAINTVISITOR_H
#include "Visitor.h"

class PreviewPage;
class Notepannel;
class CDC;
class PrintVisitor : public Visitor {
public:
	PrintVisitor(PreviewPage* previewPage, Notepannel* notepannel, CDC* cPaintDC);
	~PrintVisitor();
	virtual void Visit(Paper* paper);
	virtual void Visit(Line* line);
	virtual void Visit(DummyLine* dummyLine);
	virtual void Visit(SingleByteCharacter* singleByteCharacter);
	virtual void Visit(DoubleByteCharacter* doubleByteCharacter);
	int lineOrder = 0;
	int charOrder = 0;
	int currentLineWidth = 0;
	int currentPageNumber = 0;
public:
	Notepannel* notepannel;
	PreviewPage* previewPage;
	CDC* cPaintDC;
};


#endif // !_PAINTVISITOR_H
