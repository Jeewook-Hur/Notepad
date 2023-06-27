//Subject.h
/*
* 파일명칭:Subject.h
* 기능:Subject클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/8/9
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