//Visitor.h
/*
* ���ϸ�Ī:Visitor.h
* ���:�߻�Ŭ���� Visitor�� ���
* �ۼ���:������
* �ۼ�����:2022/11/1
*/
#ifndef _VISITOR_H
#define _VISITOR_H

class Paper;
class Line;
class DummyLine;
class SingleByteCharacter;
class DoubleByteCharacter;
class Visitor {
public:
	Visitor();
	virtual ~Visitor() = 0;
	virtual void Visit(Paper* paper) = 0;
	virtual void Visit(Line* line) = 0;
	virtual void Visit(DummyLine* dummyLine) = 0;
	virtual void Visit(SingleByteCharacter* singleByteCharacter) = 0;
	virtual void Visit(DoubleByteCharacter* doubleByteCharacter) = 0;
};

#endif // !_VISITOR_H
