//LineWrapControl.h
/*
* ���ϸ�Ī:LineWrapControl.h
* ���:�ڵ� �ٹٲ��� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/9/21
*/
#ifndef _LINEWRAPCONTROL_H
#define _LINEWRAPCONTROL_H
#include "Observer.h"

class Notepannel;
class LineWrapControl : public Observer {
public:
	LineWrapControl(Notepannel* notepannel);
	virtual ~LineWrapControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_LINEWRAPCONTROL_H
