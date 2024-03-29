//WheelDown.cpp
/*
* 파일명칭:WheelDown.cpp
* 기능:마우스 휠을 아래로 굴렸을때의 이벤트를 수행하는 클래스
* 작성자:허지욱
* 작성일자:2022/10/12
*/
#include "WheelDown.h"
#include "Notepannel.h"
#include "VerticalScrollAction.h"
#include "VerticalScrollActionCreator.h"
#include "HorizontalScrollAction.h"
#include "HorizontalScrollActionCreator.h"


/*
* 함수명칭:WheelDown
* 기능:생성자
*/
WheelDown::WheelDown(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~WheelDown
* 기능:소멸자
*/
WheelDown::~WheelDown() {
}

/*
* 함수명칭:OnMouseWheel
* 기능:휠울 굴렸을 때의 이벤트를 실행한다.
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

	if (vScrollInfo.nPage <= (UINT)vScrollInfo.nMax) { //세로 스크롤이 활성화 되었을 때
		//세로스크롤을 한줄 위로 이동시킨다.
		verticalScrollAction = verticalScrollActionCreator.Create(SB_LINEDOWN, 0, 0);
		verticalScrollAction->OnVScroll(0, 0, 0);
	}
	else if (vScrollInfo.nPage > (UINT)vScrollInfo.nMax && hScrollInfo.nPage <= (UINT)hScrollInfo.nMax) { //세로스크롤이 비활성화 되어있고 가로스크롤이 활성화 되어있을 때
		//가로스크롤을 한줄 왼쪽으로 이동시킨다.
		horizontalScrollAction = horizontalScrollActionCreator.Create(SB_LINERIGHT, 0, 0);
		horizontalScrollAction->OnHScroll(0, 0, 0);
		horizontalScrollAction->OnHScroll(0, 0, 0);
	}

	delete horizontalScrollAction;
	delete verticalScrollAction;
	return TRUE;
}