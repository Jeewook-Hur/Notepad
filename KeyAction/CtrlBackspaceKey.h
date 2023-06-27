//CtrlBackspaceKey.h
/*
* ���ϸ�Ī:CtrlBackspaceKey.h
* ���:��Ʈ�� �齺���̽� Ű�� ���������� ���� ���
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#ifndef _CTRLBACKSPACEKEY_H
#define _CTRLBACKSPACEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlBackspaceKey :public KeyAction {
public:
	CtrlBackspaceKey(Notepannel* notepannel);
	virtual ~CtrlBackspaceKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLBACKSPACEKEY_H
