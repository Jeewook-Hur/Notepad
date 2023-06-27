//WheelUp.cpp
/*
* ���ϸ�Ī:WheelUp.cpp
* ���:���콺 ���� ���� ���������� �̺�Ʈ�� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/10/12
*/
#include "WheelUp.h"
#include "Notepannel.h"
#include "VerticalScrollAction.h"
#include "VerticalScrollActionCreator.h"
#include "HorizontalScrollAction.h"
#include "HorizontalScrollActionCreator.h"


/*
* �Լ���Ī:WheelUp
* ���:������
*/
WheelUp::WheelUp(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~WheelUp
* ���:�Ҹ���
*/
WheelUp::~WheelUp() {
}

/*
* �Լ���Ī:OnMouseWheel
* ���:�ٿ� ������ ���� �̺�Ʈ�� �����Ѵ�.
*/
BOOL WheelUp::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	VerticalScrollAction* verticalScrollAction = 0;
	VerticalScrollActionCreator verticalScrollActionCreator(this->notepannel);
	HorizontalScrollAction* horizontalScrollAction = 0;
	HorizontalScrollActionCreator horizontalScrollActionCreator(this->notepannel);
	
	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);
	SCROLLINFO vScrollInfo = { 0, };
	SCROLLINFO hScrollInfo = { 0, };

	this->notepannel->GetScrollInfo(SB_VERT, &vScrollInfo);
	this->notepannel->GetScrollInfo(SB_HORZ, &hScrollInfo);

	if (vScrollInfo.nPage <= (UINT)vScrollInfo.nMax) { //���� ��ũ���� Ȱ��ȭ �Ǿ��� ��
		//���ν�ũ���� ���� ���� �̵���Ų��.
		verticalScrollAction = verticalScrollActionCreator.Create(SB_LINEUP, 0, 0);
		verticalScrollAction->OnVScroll(0, 0, 0);
	}
	else if (vScrollInfo.nPage > (UINT)vScrollInfo.nMax && hScrollInfo.nPage <= (UINT)hScrollInfo.nMax) { //���ν�ũ���� ��Ȱ��ȭ �Ǿ��ְ� ���ν�ũ���� Ȱ��ȭ �Ǿ����� ��
		//���ν�ũ���� ���� �������� �̵���Ų��.
		horizontalScrollAction = horizontalScrollActionCreator.Create(SB_LINELEFT, 0, 0);
		horizontalScrollAction->OnHScroll(0, 0, 0);
		horizontalScrollAction->OnHScroll(0, 0, 0);
	}

	delete horizontalScrollAction;
	delete verticalScrollAction;
	return TRUE;
}