//Composite.cpp
/*
* ���ϸ�Ī:Composite.cpp
* ���:�߻�Ŭ���� �ռ�
* �ۼ���:������
* �ۼ�����:2022/7/11
*/
#include "Composite.h"

/*
* �Լ���Ī:Composite
* ���:������
*/
Composite::Composite(Long capacity) :glyphes(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}
Composite::Composite(const Composite& source) : glyphes(source.glyphes) {
	Long i = 0;
	Glyph* glyph = 0;
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
	
	while (i < this->length) {
		glyph = this->glyphes[i]->Clone();
		this->glyphes.Modify(i, glyph);
		i++;
	}
}

/*
* �Լ���Ī:~Composite
* ���:�Ҹ���
*/
Composite::~Composite() {
	Long i = 0;
	while (i < this->length) {
		delete this->glyphes[i];
		i++;
	}
}

/*
* �Լ���Ī:Add
* ���:�����ϴ�
*/
Long Composite::Add(Glyph* glyph) {
	Long order = -1;
	if (this->current < this->length - 1) { //���� ��ġ�� �ǵڰ� �ƴϸ� 
		order = this->glyphes.Insert(this->current + 1, glyph);
		this->capacity++;
	}
	else { //���� ��ġ�� �� ���϶� 
		if (this->length < this->capacity) {
			order = this->glyphes.Store(this->length, glyph);
		}
		else if (this->length >= this->capacity) {
			order = this->glyphes.AppendFromRear(glyph);
			this->capacity++;
		}
	}
	this->length++;
	this->current++;
	return order;
}
Long Composite::Add(Long order, Glyph* glyph) { //order�� ���� 
	Long index = -2; //��ġ
	order = this->glyphes.Insert(order, glyph);
	this->length++;
	this->capacity++;
	index = order;
	this->current = index;
	return index;
}
Long Composite::Add(Glyph* other, Long orderToAdd) { //���� �ڷ����� Glyph�� ��ĥ�� 
	Glyph* branch = 0;
	Glyph* clone = 0;
	Long length = other->GetLength();
	Long order = orderToAdd;
	Long index = -2;
	Long i = 0;
	Long thisLength = this->GetLength();

	if (orderToAdd <= thisLength - 1) {
		while (i < length) {
			branch = other->GetAt(i);
			clone = branch->Clone();
			this->Add(order, clone);
			order++;
			i++;
		}
	}
	else {
		while (i < length) {
			branch = other->GetAt(i);
			this->Last();
			this->Add(branch->Clone());
			order++;
			i++;
		}
	}
	index = order - 1; 
	index = this->Move(index);
	return index;
}

/*
* �Լ���Ī:GetAt
* ���:��������
*/
Glyph* Composite::GetAt(Long order) {
	return this->glyphes.GetAt(order);
}

/*
* �Լ���Ī:Remove
* ���:�����
*/
Long Composite::Remove(Long order) { //���� ������ �Է¹޴´�.
	Long index = -2;
	//������ �ִ� �۸����� �� �Ҵ� ������ �����.
	delete this->glyphes[order];
	//�迭���� ������ �ּҸ� �����. 
	this->glyphes.Delete(order);
	this->capacity--;
	this->length--;
	//��ġ�� �����Ѵ�.
	index = order - 1;
	this->current = index;
	//����� ��ġ�� ��ȯ�ϴ�. 
	return index;
}
/*
* �Լ���Ī:Remove
* ���:�Է¹��� ����(������ġ���� ����ġ����)�� ������ �����Ѵ�.
* �Է�:������ġ(�߿�), ����ġ
* ���:������ġ
*/
Long Composite::Remove(Long startOrder, Long endOrder) { //��Ģ������ �������� ��ġ�� �ڷḦ ���°��� �±⿡ ��ġ�� �������� �ߴ�. 
	Long length = endOrder - startOrder + 1;
	Long index = 0;
	Long i = 0;

	while (i < length) {
		index = this->Remove(startOrder);
		i++;
	}
	return index;
}


/*
* �Լ���Ī:Move
* ���:�Էµ� ��ġ�� �̵��Ѵ�.
*/
Long Composite::Move(Long index) {
	this->current = index;
	return this->current;
}

/*
* �Լ���Ī:First
* ���:ó����ġ�� �̵��Ѵ�.
*/
Long Composite::First() {
	this->current = -1;
	return this->current;
}

/*
* �Լ���Ī:Previous
* ���:������ġ�� �̵��Ѵ�.
*/
Long Composite::Previous() {
	this->current--;
	if (this->current < -1) {
		this->current = -1;
	}
	return this->current;
}

/*
* �Լ���Ī:Next
* ���:���� ��ġ�� �̵��Ѵ�.
*/
Long Composite::Next() {
	this->current++;
	if (this->current >= this->length) {
		this->current = this->length - 1;
	}
	return this->current;
}

/*
* �Լ���Ī:Last
* ���:������ ��ġ�� �̵��Ѵ�.
*/
Long Composite::Last() {
	this->current = this->length - 1;
	return this->current;

}

/*
* �Լ���Ī:operator=
* ���:ġȯ������
*/
Composite& Composite::operator=(const Composite& source) {
	Long i = 0;
	Glyph* glyph = 0;

	this->glyphes = source.glyphes;
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	while (i < this->length) {
		glyph = this->glyphes[i]->Clone();
		this->glyphes.Modify(i, glyph);
		i++;
	}
	return *this;
}

/*
* �Լ���Ī:operator[]
* ���:÷�ڿ�����
*/
Glyph* Composite::operator[](Long order) {
	return this->glyphes[order];
}
