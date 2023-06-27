//Subject.cpp
/*
* 파일명칭:Subject.cpp
* 기능:Subject 클래스
* 작성자:허지욱
* 작성일자:2022/8/9
*/
#include "Subject.h"

/*
* 함수명칭:Subject
* 기능:생성자
*/
Subject::Subject(Long capacity) :observers(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

/*
* 함수명칭:~Subject
* 기능:소멸자
*/
Subject::~Subject() {
}

/*
* 함수명칭:Attach
* 기능:입력받는 옵저버 클래스를 넣는다.
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
* 함수명칭:Detach
* 기능:입력받은 옵저버 클래스를 뺀다. 
*/
Observer* Subject::DetachObserver(Observer* observer) { //옵저버를 입력받는다.
	Observer* ret = 0;
	Long index = -1;
	//옵저버를 찾는다. 
	index = this->observers.LinerSearchUnique(observer, CompareObserverLink);
	if (index != -1) { //옵저버를 찾으면
		//옵저버를 가져온다. 
		ret = this->observers.GetAt(index);
		//Subject에서 옵저버를 뺀다.
		this->observers.Delete(index);
		this->capacity--;
		this->length--;
	}
	//옵저버를 반환한다.
	return ret;
}

/*
* 함수명칭:Notify
* 기능:소속된 옵저버들에게 업데이트를 위한 알림을 전송한다. 
*/
void Subject::Notify() {
	Long i = 0;
	while (i < this->length) {//옵저버의 개수만큼 반복한다.
		this->observers.GetAt(i)->Update(this);
		i++;
	}
}

/*
* 함수명칭:GetObserver
* 기능:입력받은 위치의 옵저버를 반환한다.
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