//CtrlDeleteKey.h
/*
* ���ϸ�Ī:CtrlDeleteKey.h
* ���:��Ʈ�� ����Ʈ Ű�� ���������� ���� ���
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#ifndef _CTRLDELETEKEY_H
#define _CTRLDELETEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlDeleteKey :public KeyAction {
public:
	CtrlDeleteKey(Notepannel* notepannel);
	virtual ~CtrlDeleteKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLDELETEKEY_H
