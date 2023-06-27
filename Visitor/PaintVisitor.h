//PaintVisitor.h
/*
* ���ϸ�Ī:PaintVisitor.h
* ���:Ŭ���̾�Ʈ�� ����ϴ� ��ũ��Ʈ ������ Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/11/8
*/
#ifndef _PAINTVISITOR_H
#define _PAINTVISITOR_H
#include "Visitor.h"

class Notepannel;
class CDC;
class PaintVisitor : public Visitor{
public:
	PaintVisitor(Notepannel* notepannel, CDC* cPaintDC);
	~PaintVisitor();
	virtual void Visit(Paper* paper);
	virtual void Visit(Line* line);
	virtual void Visit(DummyLine* dummyLine);
	virtual void Visit(SingleByteCharacter* singleByteCharacter);
	virtual void Visit(DoubleByteCharacter* doubleByteCharacter);
	int lineOrder = 0;
	int charOrder = 0;
	int currentLineWidth = 0;
public:
	Notepannel* notepannel;
	CDC* cPaintDC;
};


#endif // !_PAINTVISITOR_H
