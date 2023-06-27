//LeftKey.h
/*
* ���ϸ�Ī:LeftKey.h
* ���:���� ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _LEFTKEY_H
#define _LEFTKEY_H
#include "KeyAction.h"

class Notepannel;

class LeftKey :public KeyAction {
public:
	LeftKey(Notepannel* notepannel);
	virtual ~LeftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_LEFTKEY_H
