//DocumentVirtualSizeControl.h
/*
* ���ϸ�Ī:DocumentVirtualSizeControl.h
* ���:������ ����ũ�⸦ �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/9/29
*/
#ifndef _DOCUMENTVERTUALSIZECONTROL_H
#define _DOCUMENTVERTUALSIZECONTROL_H
#include "Observer.h"

class Notepannel;
class DocumentVirtualSizeControl : public Observer {
public:
	DocumentVirtualSizeControl(Notepannel* notepannel);
	virtual ~DocumentVirtualSizeControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_DOCUMENTVERTUALSIZECONTROL_H
