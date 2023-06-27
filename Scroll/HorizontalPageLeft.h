//HorizontalPageLeft.h
/*
* ���ϸ�Ī:HorizontalPageLeft.h
* ���:���� ��ũ���� �׼��� �� ������ �������� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALPAGELEFT_H
#define _HORIZONTALPAGELEFT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalPageLeft : public HorizontalScrollAction {
public:
	HorizontalPageLeft(Notepannel* notepannel);
	virtual ~HorizontalPageLeft();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALPAGELEFT_H