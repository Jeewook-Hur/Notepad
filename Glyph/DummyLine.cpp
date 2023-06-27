 //DummyLine.cpp
/*
* �Լ���Ī:DummyLine.cpp
* ���:���� ����
* �ۼ���:������
* �ۼ�����:20220919
*/
#include "DummyLine.h"
#include "Visitor.h"

/*
* �Լ���Ī:DummyLine
* ���:������
*/
DummyLine::DummyLine(Long capacity) :Line(capacity) {
}
DummyLine::DummyLine(const DummyLine& source) : Line(source) {
}

/*
* �Լ���Ī:~DummyLine
* ���:�Ҹ���
*/
DummyLine::~DummyLine() {
}

/*
* �Լ���Ī:Accept
* ���:Element�μ� Visitor�� Visit�� ����Ѵ�.
*/
void DummyLine::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

/*
* �Լ���Ī:Clone
* ���:������Ÿ�� ���������� �����Ѵ�
*/
Glyph* DummyLine::Clone() {
	return new DummyLine(*this);
}