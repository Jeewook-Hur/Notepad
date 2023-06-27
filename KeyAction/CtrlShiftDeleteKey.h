//CtrlShiftDeleteKey.h
/*
* ���ϸ�Ī:CtrlShiftDeleteKey.h
* ���:��Ʈ�� ����Ʈ ����Ʈ Ű�� ���������� ���� ���
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#ifndef _CTRLSHIFTDELETEKEY_H
#define _CTRLSHIFTDELETEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftDeleteKey :public KeyAction {
public:
	CtrlShiftDeleteKey(Notepannel* notepannel);
	virtual ~CtrlShiftDeleteKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTDELETEKEY_H
