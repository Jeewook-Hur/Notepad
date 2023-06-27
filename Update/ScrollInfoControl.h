//ScrollInfoControl.h
/*
* ���ϸ�Ī:ScrollInfoControl.h
* ���:��ũ���� ������ �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/9/29
*/
#ifndef _SCROLLCONTROL_H
#define _SCROLLCONTROL_H
#include "Observer.h"

class Notepannel;
class ScrollInfoControl : public Observer {
public:
	ScrollInfoControl(Notepannel* notepannel);
	virtual ~ScrollInfoControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_SCROLLCONTROL_H
