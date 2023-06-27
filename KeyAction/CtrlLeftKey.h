//CtrlLeftKey.h
/*
* ���ϸ�Ī:CtrlLeftKey.h
* ���:��Ʈ�Ѱ� ���� ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _CTRLLEFTKEY_H
#define _CTRLLEFTKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlLeftKey :public KeyAction {
public:
	CtrlLeftKey(Notepannel* notepannel);
	virtual ~CtrlLeftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLLEFTKEY_H
