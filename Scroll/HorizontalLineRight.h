//HorizontalLineRight.h
/*
* ���ϸ�Ī:HorizontalLineRight.h
* ���:���� ��ũ���� �׼��� ���� �����ʷ� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALLINERIGHT_H
#define _HORIZONTALLINERIGHT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalLineRight : public HorizontalScrollAction {
public:
	HorizontalLineRight(Notepannel* notepannel);
	virtual ~HorizontalLineRight();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALLINERIGHT_H