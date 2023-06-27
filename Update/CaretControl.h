//CaretControl.h
/*
* ���ϸ�Ī:CaretControl.h
* ���:ĳ���� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/8/9
*/
#ifndef _CARETCONTROL_H
#define _CARETCONTROL_H
#include "Observer.h"

class Notepannel;
class CaretControl : public Observer {
public:
	CaretControl(Notepannel* notepannel);
	virtual ~CaretControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_CARETCONTROL_H
