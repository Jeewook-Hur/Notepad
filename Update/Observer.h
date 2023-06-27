//Observer.h
/*
* 파일명칭:Observer.h
* 기능:옵저버 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/8/9
*/
#ifndef _OBSERVER_H
#define _OBSERVER_H

class Subject;
class Observer {
public:
	Observer();
	virtual ~Observer() = 0;
	virtual void Update(Subject* theChangedSubject) = 0;
};

#endif // !_OBSERVER_H