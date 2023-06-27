//CtrlRightKey.h
/*
* ���ϸ�Ī:CtrlRightKey.h
* ���:��Ʈ�Ѱ� ������ ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _CTRLRIGHTKEY_H
#define _CTRLRIGHTKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlRightKey :public KeyAction {
public:
	CtrlRightKey(Notepannel* notepannel);
	virtual ~CtrlRightKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLRIGHTKEY_H
