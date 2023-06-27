//Subject.cpp
/*
* ���ϸ�Ī:Subject.cpp
* ���:Subject Ŭ����
* �ۼ���:������
* �ۼ�����:2022/8/9
*/
#include "Subject.h"

/*
* �Լ���Ī:Subject
* ���:������
*/
Subject::Subject(Long capacity) :observers(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

/*
* �Լ���Ī:~Subject
* ���:�Ҹ���
*/
Subject::~Subject() {
}

/*
* �Լ���Ī:Attach
* ���:�Է¹޴� ������ Ŭ������ �ִ´�.
*/
Long Subject::AttachObserver(Observer* observer) {
	Long index = -1;
	if (this->length < this->capacity) {
		index = this->observers.Store(this->length, observer);
	}
	else if (this->length >= this->capacity) {
		index = this->observers.AppendFromRear(observer);
		this->capacity++;
	}
	this->length++;
	return index;
}

/*
* �Լ���Ī:Detach
* ���:�Է¹��� ������ Ŭ������ ����. 
*/
Observer* Subject::DetachObserver(Observer* observer) { //�������� �Է¹޴´�.
	Observer* ret = 0;
	Long index = -1;
	//�������� ã�´�. 
	index = this->observers.LinerSearchUnique(observer, CompareObserverLink);
	if (index != -1) { //�������� ã����
		//�������� �����´�. 
		ret = this->observers.GetAt(index);
		//Subject���� �������� ����.
		this->observers.Delete(index);
		this->capacity--;
		this->length--;
	}
	//�������� ��ȯ�Ѵ�.
	return ret;
}

/*
* �Լ���Ī:Notify
* ���:�Ҽӵ� �������鿡�� ������Ʈ�� ���� �˸��� �����Ѵ�. 
*/
void Subject::Notify() {
	Long i = 0;
	while (i < this->length) {//�������� ������ŭ �ݺ��Ѵ�.
		this->observers.GetAt(i)->Update(this);
		i++;
	}
}

/*
* �Լ���Ī:GetObserver
* ���:�Է¹��� ��ġ�� �������� ��ȯ�Ѵ�.
*/
Observer* Subject::GetObserver(Long index) {
	return this->observers.GetAt(index);
}

int CompareObserverLink(void* one, void* other) {
	Observer* one_ = (Observer*)one;
	Observer* other_ = (Observer*)other;
	int ret;
	if (one_ == other_) {
		ret = 0;
	}
	else {
		ret = -1;
	}
	return ret;
}