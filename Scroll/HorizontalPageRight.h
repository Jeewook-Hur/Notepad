//HorizontalPageRight.h
/*
* ���ϸ�Ī:HorizontalPageRight.h
* ���:���� ��ũ���� �׼��� �����ʷ� �� �� �̵��� ���� �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALPAGERIGHT_H
#define _HORIZONTALPAGERIGHT_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalPageRight : public HorizontalScrollAction {
public:
	HorizontalPageRight(Notepannel* notepannel);
	virtual ~HorizontalPageRight();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALPAGERIGHT_H