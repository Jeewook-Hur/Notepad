//UpKey.h
/*
* ���ϸ�Ī:UpKey.h
* ���:�� ȭ��ǥ�� Ŭ���������� ���
* �ۼ���:������
* �ۼ�����:2022/9/15
*/
#ifndef _UPKEY_H
#define _UPKEY_H
#include "KeyAction.h"

class Notepannel;

class UpKey : public KeyAction {
public:
	UpKey(Notepannel* notepannel);
	virtual ~UpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_UPKEY_H
