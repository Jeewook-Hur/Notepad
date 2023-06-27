//VerticalEndScroll.h
/*
* ���ϸ�Ī:VerticalEndScroll.h
* ���:���� ��ũ���� �׼��� �� �Ʒ��� �̵��ϴ� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220928
*/
#ifndef _VERTICALENDSCROLL_H
#define _VERTICALENDSCROLL_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalEndScroll : public VerticalScrollAction {
public:
	VerticalEndScroll(Notepannel* notepannel);
	virtual ~VerticalEndScroll();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALENDSCROLL_H