//Subject.h
/*
* ���ϸ�Ī:Subject.h
* ���:SubjectŬ������ ���
* �ۼ���:������
* �ۼ�����:2022/8/9
*/
#include "Array.h"
#include "Observer.h"

class Subject {
public:
	Subject(Long capacity = 100);
	virtual ~Subject();
	virtual Long AttachObserver(Observer* observer);
	virtual Observer* DetachObserver(Observer* observer);
	virtual void Notify();
	virtual Observer* GetObserver(Long index);

	virtual Long GetSubjectCapacity() const;
	virtual Long GetSubjectLength() const;
private:
	Array<Observer*> observers;
	Long capacity;
	Long length;
};

inline Long Subject::GetSubjectCapacity() const {
	return this->observers.GetCapacity();
}

inline Long Subject::GetSubjectLength() const {
	return this->observers.GetLength();
}

int CompareObserverLink(void* one, void* other);