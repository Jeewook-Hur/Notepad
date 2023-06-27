//CtrlEndKey.h
/*
* ���ϸ�Ī:CtrlEndKey.h
* ���:��Ʈ�Ѱ� ����Ű�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _CTRLENDKEY_H
#define _CTRLENDKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlEndKey :public KeyAction {
public:
	CtrlEndKey(Notepannel* notepannel);
	virtual ~CtrlEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLENDKEY_H
