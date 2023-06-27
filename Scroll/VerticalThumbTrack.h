//VerticalThumbTrack.h
/*
* ���ϸ�Ī:VerticalThumbTrack.h
* ���:���� ��ũ���� �׼��� ������ �̺�Ʈ�� �����ϴ� ���
* �ۼ���:������
* �ۼ�����:20220929
*/
#ifndef _VERTICALTHUMBTRACK_H
#define _VERTICALTHUMBTRACK_H
#include "VerticalScrollAction.h"

class Notepannel;
class VerticalThumbTrack : public VerticalScrollAction {
public:
	VerticalThumbTrack(Notepannel* notepannel);
	virtual ~VerticalThumbTrack();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	Notepannel* notepannel;
};

#endif // !_VERTICALTHUMBTRACK_H