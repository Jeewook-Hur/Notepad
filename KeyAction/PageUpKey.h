//PageUpKey.h
/*
* ���ϸ�Ī:PageUpKey.h
* ���:��������Ű�� Ŭ���������� �̺�Ʈ�� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/5
*/
#ifndef _PAGEUPKEY_H
#define _PAGEUPKEY_H
#include "KeyAction.h"

class Notepannel;
class PageUpKey : public KeyAction {
public:
	PageUpKey(Notepannel* notepannel);
	virtual ~PageUpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_PAGEUPKEY_H