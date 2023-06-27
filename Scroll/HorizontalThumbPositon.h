//HorizontalThumbPositon.h
/*
* ���ϸ�Ī:HorizontalThumbPositon.h
* ���:���� ��ũ���� �׼��� ������ġ �϶��� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALTHUMBPOSITION_H
#define _HORIZONTALTHUMBPOSITION_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalThumbPositon : public HorizontalScrollAction {
public:
	HorizontalThumbPositon(Notepannel* notepannel);
	virtual ~HorizontalThumbPositon();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALTHUMBPOSITION_H