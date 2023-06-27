//HorizontalRight.h
/*
* ���ϸ�Ī:HorizontalRight.h
* ���:���� ��ũ���� �׼��� �����ʷ� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALRIGHT_H
#define _HORIZONTALRIGHT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalRight : public HorizontalScrollAction {
public:
	HorizontalRight(Notepannel* notepannel);
	virtual ~HorizontalRight();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALRIGHT_H