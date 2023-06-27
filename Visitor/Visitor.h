//Visitor.h
/*
* 파일명칭:Visitor.h
* 기능:추상클래스 Visitor의 헤더
* 작성자:허지욱
* 작성일자:2022/11/1
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
