//PageDownKey.h
/*
* ���ϸ�Ī:PageDownKey.h
* ���:�������ٿ� Ű�� Ŭ���������� �̺�Ʈ�� �����ϴ� Ŭ������ ���
* �ۼ���:������
* �ۼ�����:2022/10/5
*/
#ifndef _PAGEDOWNKEY_H
#define _PAGEDOWNKEY_H
#include "KeyAction.h"

class Notepannel;
class PageDownKey : public KeyAction {
public:
	PageDownKey(Notepannel* notepannel);
	virtual ~PageDownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_PAGEDOWNKEY_H