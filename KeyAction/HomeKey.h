//HomeKey.h
/*
* ���ϸ�Ī:HomeKey.h
* ���:ȨŰ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _HOMEKEY_H
#define _HOMEKEY_H
#include "KeyAction.h"

class Notepannel;

class HomeKey :public KeyAction {
public:
	HomeKey(Notepannel* notepannel);
	virtual ~HomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_HOMEKEY_H
