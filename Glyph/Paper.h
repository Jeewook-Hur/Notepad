//Paper.h
/*
* 파일명칭:Paper.h
* 기능:종이의 헤더
* 작성자:허지욱
* 작성일자:2022/7/11
*/
#ifndef _PAPER_H
#define _PAPER_H
#include "Composite.h"
#include<string>
using namespace std;

class Paper : public Composite {
public:
	Paper(Long capacity = 1000);
	Paper(const Paper& source);
	virtual ~Paper();
	
	virtual Long Add(Glyph* paperToAdd, Long lineOrder, Long charIndex);
	virtual Long Remove(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex);

	virtual void FindChar(Glyph* characterToFind, Long*(*lineOrders), Long*(*charOrders), Long* count);
	virtual void FindCharUpperLower(Glyph* characterToFind, Long*(*lineOrders), Long*(*charOrders), Long* count);
	virtual void FindPaper(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count);
	virtual void FindPaperUpperLower(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count);


	virtual Long First();
	virtual Long Previous();

	virtual Long SplitDummyLine(Long lineOrder, Long characterIndex);
	virtual void MergeAllDummyLines();
	virtual Long MergeDummyLines(Long startlineOrder);

	virtual void GetLocation(Long lineOrder, Long charIndex, Long* lineLocation, Long* charLocation);
	virtual void MoveToLocation(Long lineLocation, Long charLocation, Long* lineOrder, Long* charIndex);

	virtual Glyph* Clone();
	virtual Glyph* Clone(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex);
	virtual string GetString();
	virtual string GetExactString();

	virtual void Accept(Visitor* visitor);

	virtual BOOL IsEqual(Long previousLineOrder, Long previousCharIndex);
	virtual BOOL IsEqual(Glyph* other);
	virtual BOOL IsEqualUpperLower(Glyph* other);
	virtual BOOL IsNotEqual(Long previousLineOrder, Long previousCharIndex);

	virtual Long GetCharNumber();

	Paper& operator=(const Paper& source);
	Glyph* operator[](Long order);
};

#endif // !_PAPER_H
