//CtrlShiftRightKey.h
/*
* ���ϸ�Ī:CtrlShiftRightKey.h
* ���:ctrlŰ�� shift�� ������ ȭ��ǥ�� Ŭ���������� ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/31
*/
#ifndef _CTRLSHIFTRIGHTKEY_H
#define _CTRLSHIFTRIGHTKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftRightKey :public KeyAction {
public:
	CtrlShiftRightKey(Notepannel* notepannel);
	virtual ~CtrlShiftRightKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTRIGHTKEY_H
