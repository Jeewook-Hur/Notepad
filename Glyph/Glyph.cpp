//Glyph.cpp
/*
* ���ϸ�Ī:Glyph.cpp
* ���:�߻�Ŭ���� ����
* �ۼ���:������
* �ۼ�����:2022/7/11
*/
#include "Glyph.h"
#include "Visitor.h"
/*
* �Լ���Ī:Glyph
* ���:������
*/
Glyph::Glyph() {
}

/*
* �Լ���Ī:~Glyph
* ���:�Ҹ���
*/
Glyph::~Glyph() {
}

/*
* �Լ���Ī:Add
* ���:�����ϴ��� �����Լ�
*/
Long Glyph::Add(Glyph* glyph) {
	return -1;
}
Long Glyph::Add(Long order, Glyph* glyph) {
	return -1;
}
Long Glyph::Add(Glyph* other, Long orderToAdd) {
	return -1;
}
Long Glyph::Add(Glyph* paperToAdd, Long lineOrder, Long charIndex) {
	return - 1;
}


/*
* �Լ���Ī:GetAt
* ���:���������� �����Լ�
*/
Glyph* Glyph::GetAt(Long order) {
	return 0;
}

/*
* �Լ���Ī:Remove
* ���:������� �����Լ�
*/
Long Glyph::Remove(Long order) {
	return -1;
}
Long Glyph::Remove(Long startOrder, Long endOrder) {
	return -1;
}
Long Glyph::Remove(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex) {
	return -1;
}


/*
* �Լ���Ī:SplitDummyLine
* ���:�����ٷ� �������� �����Լ�
*/
Long Glyph::SplitDummyLine(Long lineOrder, Long characterIndex) {
	return -1;
}

/*
* �Լ���Ī:MergeAllDummyLines
* ���:�������� �����ٿ� �� ��ġ�� �Լ��� �����Լ�
*/
void Glyph::MergeAllDummyLines() {
}

/*
* �Լ���Ī:MergeDummyLines
* ���:�������� �����ٿ� �� ��ġ�� �Լ��� �����Լ�
*/
Long Glyph::MergeDummyLines(Long startlineOrder) {
	return -1;
}

/*
* �Լ���Ī:FindChar
* ���:�Է��� ������ ��ġ�� ã�´�. 
*/
void Glyph::FindChar(Glyph* characterToFind, Long*(*lineOrders), Long*(*charOrders), Long* count) {
}
void Glyph::FindCharUpperLower(Glyph* characterToFind, Long* (*lineOrders), Long* (*charOrders), Long* count) {
}

/*
* �Լ���Ī:FindPaper
* ���:�Է��� ���̿� ��ġ�ϴ� ������ �ִ� ��ġ�� ã�´�. 
*/
void Glyph::FindPaper(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count) {
}
void Glyph::FindPaperUpperLower(Glyph* otherPaper, Long* (*lineOrders), Long* (*charIndexes), Long* count) {
}




/*
* �Լ���Ī:Move
* ���:�Էµ� ��ġ�� �̵��Ѵ�.
*/
Long Glyph::Move(Long index) {
	return -2;
}

/*
* �Լ���Ī:First
* ���:ó����ġ�� �̵��Ѵ�.
*/
Long Glyph::First() {
	return -2;
}

/*
* �Լ���Ī:Previous
* ���:������ġ�� �̵��Ѵ�.
*/
Long Glyph::Previous() {
	return -2;
}

/*
* �Լ���Ī:Next
* ���:���� ��ġ�� �̵��Ѵ�.
*/
Long Glyph::Next() {
	return -2;
}

/*
* �Լ���Ī:Last
* ���:������ ��ġ�� �̵��Ѵ�.
*/
Long Glyph::Last() {
	return -2;
}

/*
* �Լ���Ī:PreviousWord
* ���:���� �ܾ�� �̵��Ѵ�.
*/
Long Glyph::PreviousWord() {
	return -2;
}

/*
* �Լ���Ī:NextWord
* ���:���� �ܾ�� �̵��Ѵ�
*/
Long Glyph::NextWord() {
	return -2;
}

/*
* �Լ���Ī:GetLocation
* ���:���� ��ġ�� ���Ѵ�.
*/
void Glyph::GetLocation(Long lineOrder, Long charIndex, Long* lineLocation, Long* charLocation) {
}

/*
* �Լ���Ī:MoveToLocation
* ���:���� ��ġ�� �̵��Ѵ�.
*/
void Glyph::MoveToLocation(Long lineLocation, Long charLocation, Long* lineOrder, Long* charIndex) {
}

/*
* �Լ���Ī:GetLength
* ���:���̸� ���������� �����Լ�
*/
Long Glyph::GetLength() const {
	return -1;
}

/*
* �Լ���Ī:GetCapacity
* ���:�Ҵ緮�� ���������� �����Լ�
*/
Long Glyph::GetCapacity() const {
	return -1;
}

/*
* �Լ���Ī:GetCurrent
* ���:���� ��ġ�� ���������� �����Լ�
*/
Long Glyph::GetCurrent() const {
	return -1;
}

/*
* �Լ���Ī:GetByte
* ���:�����ϰ�� ����Ʈ���� ��ȯ�Ѵ�
*/
Long Glyph::GetByte() const {
	return 0;
}

/*
* �Լ���Ī:Clone
* ���:�Էµ� ������ ���纻�� ����� ��ȯ�Ѵ�.
*/
Glyph* Glyph::Clone(Long startLineOrder, Long startCharIndex, Long endLineOrder, Long endCharIndex) {
	return 0;
}

/*
* �Լ���Ī:Accept
* ���:Element�μ� Visitor�� Visit�� ����Ѵ�. 
*/
void Glyph::Accept(Visitor* visitor) {
}

/*
* �Լ���Ī:IsEqual
* ���:�Է°��� ������ ���ϴ� �����Լ�
*/
BOOL Glyph::IsEqual(Long previousLineOrder, Long previousCharIndex) {
	return 0;
}
BOOL Glyph::IsEqual(Glyph* other) {
	return 0;
}
BOOL Glyph::IsEqualUpperLower(Glyph* other) {
	return 0;
}


/*
* �Լ���Ī:IsNotEqual
* ���:�Է°��� �ٸ��� ���ϴ� �����Լ�
*/
BOOL Glyph::IsNotEqual(Long previousLineOrder, Long previousCharIndex) {
	return 0;
}

/*
* �Լ���Ī:GetCharNumber
* ���:���̿� ���ϴ� �� ���ڼ��� ����ϴ� �Լ�
*/
Long Glyph::GetCharNumber() {
	return -1;
}
