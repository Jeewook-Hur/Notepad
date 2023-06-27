//CtrlShiftLeftKey.h
/*
* ���ϸ�Ī:CtrlShiftLeftKey.h
* ���:shift�� ctrlŰ�� ������ ȭ��ǥ�� Ŭ���������� ���� ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _CTRLSHIFTLEFTKEY_H
#define _CTRLSHIFTLEFTKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftLeftKey :public KeyAction {
public:
	CtrlShiftLeftKey(Notepannel* notepannel);
	virtual ~CtrlShiftLeftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTLEFTKEY_H
