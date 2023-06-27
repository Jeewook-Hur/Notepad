//Glyph.h
/*
* ���ϸ�Ī:Glyph.h
* ���:�߻�Ŭ���� ������ ���
* �ۼ���:������
* �ۼ�����:2022/7/11
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
	virtual ~Glyph() = 0; // ���� �����Լ� �߿� ����
	virtual Long Add(Glyph* glyph); // �����Լ�
	virtual Long Add(Long order, Glyph* glyph); //���� �ڷ����� ���� ��
	virtual Long Add(Glyph* other, Long orderToAdd); //���� �ڷ����� ���� �� 
	virtual Long Add(Glyph* paperToAdd, Long lineOrder, Long charIndex);
	virtual Glyph* GetAt(Long order); // �����Լ�
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


	virtual Long Move(Long index); //order�� ������ ����, index�� ��ġ(���л���)
	virtual Long First();
	virtual Long Previous();
	virtual Long Next();
	virtual Long Last();
	virtual Long PreviousWord();
	virtual Long NextWord();
	virtual void GetLocation(Long lineOrder, Long charIndex, Long* lineLocation, Long* charLocation);
	virtual void MoveToLocation(Long lineLocation, Long charLocation, Long* lineOrder, Long* charIndex);

	virtual Long GetCharNumber();

	virtual Long GetLength() const; // �����Լ�
	virtual Long GetCapacity() const; // �����Լ�
	virtual Long GetCurrent() const;
	virtual Long GetByte() const;

	virtual string GetString() = 0; // ���������Լ�
	virtual string GetExactString() = 0;
	virtual Glyph* Clone() = 0; // ���������Լ�
	virtual Glyph* Clone(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex);
	virtual void Accept(Visitor* visitor);

	virtual BOOL IsEqual(Glyph* other);
	virtual BOOL IsEqual(Long previousLineOrder, Long previousCharIndex);
	virtual BOOL IsEqualUpperLower(Glyph* other);
	virtual BOOL IsNotEqual(Long previousLineOrder, Long previousCharIndex);

	//�����Լ��� ������ �ʿ�
	//���������Լ��� ������ ���ʿ������� ����Ŭ�������� ������ ���� �� �Ҹ��ڴ� ����
};

#endif // !_GLYPH_H