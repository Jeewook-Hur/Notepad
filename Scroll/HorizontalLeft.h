//HorizontalLeft.h
/*
* ���ϸ�Ī:HorizontalLeft.h
* ���:���� ��ũ���� �׼��� �������� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALLEFT_H
#define _HORIZONTALLEFT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalLeft : public HorizontalScrollAction {
public:
	HorizontalLeft(Notepannel* notepannel);
	virtual ~HorizontalLeft();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALLEFT_H