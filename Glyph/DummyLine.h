//DummyLine.h
/*
* �Լ���Ī:DummyLine.h
* ���:���� ������ ���
* �ۼ���:������
* �ۼ�����:20220919
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