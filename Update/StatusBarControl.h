//StatusBarControl.h
/*
* ���ϸ�Ī:StatusBarControl.h
* ���:����ǥ������ �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2023/1/8
*/
#ifndef _STATUSBARCONTROL_H
#define _STATUSBARCONTROL_H
#include "Observer.h"

class Notepannel;
class StatusBarControl : public Observer {
public:
	StatusBarControl(Notepannel* notepannel);
	virtual ~StatusBarControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_STATUSBARCONTROL_H
