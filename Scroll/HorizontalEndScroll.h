//HorizontalEndScroll.h
/*
* ���ϸ�Ī:HorizontalEndScroll.h
* ���:���� ��ũ���� �׼��� ������ ������ �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALENDSCROLL_H
#define _HORIZONTALENDSCROLL_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalEndScroll : public HorizontalScrollAction {
public:
	HorizontalEndScroll(Notepannel* notepannel);
	virtual ~HorizontalEndScroll();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALENDSCROLL_H