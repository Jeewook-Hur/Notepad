//Observer.h
/*
* ���ϸ�Ī:Observer.h
* ���:������ Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/8/9
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