//VerticalLineUp.h
/*
* ���ϸ�Ī:VerticalLineUp.h
* ���:���� ��ũ���� �׼��� �� �� ���� �̵��ϴ� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALLINEUP_H
#define _VERTICALLINEUP_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalLineUp : public VerticalScrollAction {
public:
	VerticalLineUp(Notepannel* notepannel);
	virtual ~VerticalLineUp();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALLINEUP_H