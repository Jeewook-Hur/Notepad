//CtrlShiftBackspaceKey.h
/*
* ���ϸ�Ī:CtrlShiftBackspaceKey.h
* ���:��Ʈ�� ����Ʈ �齺���̽� Ű�� ���������� ���� ���
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#ifndef _CTRLSHIFTBACKSPACEKEY_H
#define _CTRLSHIFTBACKSPACEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftBackspaceKey :public KeyAction {
public:
	CtrlShiftBackspaceKey(Notepannel* notepannel);
	virtual ~CtrlShiftBackspaceKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTBACKSPACEKEY_H
