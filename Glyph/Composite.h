//Composite.h
/*
* ���ϸ�Ī:Composite.h
* ���:�߻�Ŭ���� �ռ��� ���
* �ۼ���:������
* �ۼ�����:2022/7/11
*/
#ifndef _COMPOSITE_H
#define _COMPOSITE_H
#include "Array.h"
#include "Glyph.h"

class Composite : public Glyph {
public:
	Composite(Long capacity = 1000);
	Composite(const Composite& source);
	virtual ~Composite() = 0;
	virtual Long Add(Glyph* glyph);
	virtual Long Add(Long order, Glyph* glyph);
	virtual Long Add(Glyph* other, Long orderToAdd); //���� �ڷ����� ���� �� 
	virtual Glyph* GetAt(Long order);
	virtual Long Remove(Long order);
	virtual Long Remove(Long startOrder, Long endOrder);
	virtual Long Move(Long index);
	virtual Long First();
	virtual Long Previous();
	virtual Long Next();
	virtual Long Last();

	Composite& operator=(const Composite& source);
	Glyph* operator[](Long order);

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;
private:
	Array<Glyph*> glyphes;
	Long capacity;
	Long length;
	Long current;
};

inline Long Composite::GetCapacity() const {
	return this->capacity;
}

inline Long Composite::GetLength() const {
	return this->length;
}

inline Long Composite::GetCurrent() const {
	return this->current;
}

#endif // !_COMPOSITE_H
