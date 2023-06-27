//DeleteKey.h
/*
* ���ϸ�Ī:DeleteKey.h
* ���:����ƮŰ�� ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/16
*/
#ifndef _DELETEKEY_H
#define _DELETEKEY_H
#include "KeyAction.h"

class Notepannel;

class DeleteKey :public KeyAction {
public:
	DeleteKey(Notepannel* notepannel);
	virtual ~DeleteKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_DELETEKEY_H
