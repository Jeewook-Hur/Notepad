//CtrlHKey.h
/*
* ���ϸ�Ī:CtrlHKey.h
* ���:ctrl�� HŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/12/8
*/
#ifndef _CTRLHKEY_H
#define _CTRLHKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlHKey :public KeyAction {
public:
	CtrlHKey(Notepannel* notepannel);
	virtual ~CtrlHKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLHKEY_H
