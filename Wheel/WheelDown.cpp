//WheelDown.cpp
/*
* ���ϸ�Ī:WheelDown.cpp
* ���:���콺 ���� �Ʒ��� ���������� �̺�Ʈ�� �����ϴ� Ŭ����
* �ۼ���:������
* �ۼ�����:2022/10/12
*/
#include "WheelDown.h"
#include "Notepannel.h"
#include "VerticalScrollAction.h"
#include "VerticalScrollActionCreator.h"
#include "HorizontalScrollAction.h"
#include "HorizontalScrollActionCreator.h"


/*
* �Լ���Ī:WheelDown
* ���:������
*/
WheelDown::WheelDown(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~WheelDown
* ���:�Ҹ���
*/
WheelDown::~WheelDown() {
}

/*
* �Լ���Ī:OnMouseWheel
* ���:�ٿ� ������ ���� �̺�Ʈ�� �����Ѵ�.
*/
BOOL WheelDown::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	VerticalScrollAction* verticalScrollAction = 0;
	VerticalScrollActionCreator verticalScrollActionCreator(this->notepannel);
	HorizontalScrollAction* horizontalScrollAction = 0;
	HorizontalScrollActionCreator horizontalScrollActionCreator(this->notepannel);

	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);
	SCROLLINFO vScrollInfo = { 0, };
	SCROLLINFO hScrollInfo = { 0, };

	this->notepannel->GetScrollInfo(SB_VERT, &vScrollInfo);
	this->notepannel->GetScrollInfo(SB_HORZ, &hScrollInfo);

	SCROLLBARINFO vScrollBarInfo = { 0, };
	SCROLLBARINFO hScrollBarInfo = { 0, };

	this->notepannel->GetScrollBarInfo(SB_VERT, &vScrollBarInfo);
	this->notepannel->GetScrollBarInfo(SB_HORZ, &hScrollBarInfo);

	if (vScrollInfo.nPage <= (UINT)vScrollInfo.nMax) { //���� ��ũ���� Ȱ��ȭ �Ǿ��� ��
		//���ν�ũ���� ���� ���� �̵���Ų��.
		verticalScrollAction = verticalScrollActionCreator.Create(SB_LINEDOWN, 0, 0);
		verticalScrollAction->OnVScroll(0, 0, 0);
	}
	else if (vScrollInfo.nPage > (UINT)vScrollInfo.nMax && hScrollInfo.nPage <= (UINT)hScrollInfo.nMax) { //���ν�ũ���� ��Ȱ��ȭ �Ǿ��ְ� ���ν�ũ���� Ȱ��ȭ �Ǿ����� ��
		//���ν�ũ���� ���� �������� �̵���Ų��.
		horizontalScrollAction = horizontalScrollActionCreator.Create(SB_LINERIGHT, 0, 0);
		horizontalScrollAction->OnHScroll(0, 0, 0);
		horizontalScrollAction->OnHScroll(0, 0, 0);
	}

	delete horizontalScrollAction;
	delete verticalScrollAction;
	return TRUE;
}