//Glyph.h
/*
* 파일명칭:Glyph.h
* 기능:추상클래스 글자의 헤더
* 작성자:허지욱
* 작성일자:2022/7/11
*/
#ifndef _GLYPH_H
#define _GLYPH_H
#include<string>
using namespace std;

typedef signed long int Long;
typedef int BOOL;

class Visitor;
class Glyph {
public:
	Glyph();
	virtual ~Glyph() = 0; // 순수 가상함수 중에 예외
	virtual Long Add(Glyph* glyph); // 가상함수
	virtual Long Add(Long order, Glyph* glyph); //하위 자료형을 더할 때
	virtual Long Add(Glyph* other, Long orderToAdd); //같은 자료형를 더할 때 
	virtual Long Add(Glyph* paperToAdd, Long lineOrder, Long charIndex);
	virtual Glyph* GetAt(Long order); // 가상함수
	virtual Long Remove(Long order);
	virtual Long Remove(Long startOrder, Long endOrder);
	virtual Long Remove(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex);
	virtual Long SplitDummyLine(Long lineOrder, Long characterIndex);
	virtual void MergeAllDummyLines();
	virtual Long MergeDummyLines(Long startlineOrder);

	virtual void FindChar(Glyph* characterToFind, Long*(*lineOrders), Long*(*charOrders), Long* count);
	virtual void FindCharUpperLower(Glyph* characterToFind, Long*(*lineOrders), Long*(*charOrders), Long* count);
	virtual void FindPaper(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count);
	virtual void FindPaperUpperLower(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count);


	virtual Long Move(Long index); //order는 성분의 순서, index는 위치(성분사이)
	virtual Long First();
	virtual Long Previous();
	virtual Long Next();
	virtual Long Last();
	virtual Long PreviousWord();
	virtual Long NextWord();
	virtual void GetLocation(Long lineOrder, Long charIndex, Long* lineLocation, Long* charLocation);
	virtual void MoveToLocation(Long lineLocation, Long charLocation, Long* lineOrder, Long* charIndex);

	virtual Long GetCharNumber();

	virtual Long GetLength() const; // 가상함수
	virtual Long GetCapacity() const; // 가상함수
	virtual Long GetCurrent() const;
	virtual Long GetByte() const;

	virtual string GetString() = 0; // 순수가상함수
	virtual string GetExactString() = 0;
	virtual Glyph* Clone() = 0; // 순수가상함수
	virtual Glyph* Clone(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex);
	virtual void Accept(Visitor* visitor);

	virtual BOOL IsEqual(Glyph* other);
	virtual BOOL IsEqual(Long previousLineOrder, Long previousCharIndex);
	virtual BOOL IsEqualUpperLower(Glyph* other);
	virtual BOOL IsNotEqual(Long previousLineOrder, Long previousCharIndex);

	//가상함수는 선언이 필요
	//순수가상함수는 선언이 불필요하지만 하위클래스에는 무조건 선언 단 소멸자는 예외
};

#endif // !_GLYPH_H