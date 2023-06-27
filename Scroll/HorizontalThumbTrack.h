//HorizontalThumbTrack.h
/*
* ���ϸ�Ī:HorizontalThumbTrack.h
* ���:���� ��ũ���� �׼��� ������ �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _HORIZONTALTHUMBTRACK_H
#define _HORIZONTALTHUMBTRACK_H
#include "HorizontalScrollAction.h"

class Notepannel;
class HorizontalThumbTrack : public HorizontalScrollAction {
public:
	HorizontalThumbTrack(Notepannel* notepannel);
	virtual ~HorizontalThumbTrack();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_HORIZONTALTHUMBTRACK_H