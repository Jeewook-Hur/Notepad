//AutoScrollPositionControl.h
/*
* ���ϸ�Ī:AutoScrollPositionControl.h
* ���:ĳ���� ���߾� Ŭ���̾�Ʈ�� �ڵ��̵���Ű�� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/1
*/
#ifndef _AUTOSCROLLPOSITIONCONTROL_H
#define _AUTOSCROLLPOSITIONCONTROL_H
#include "Observer.h"

class Notepannel;
class AutoScrollPositionControl : public Observer {
public:
	AutoScrollPositionControl(Notepannel* notepannel);
	virtual ~AutoScrollPositionControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_AUTOSCROLLPOSITIONCONTROL_H
