//CtrlShiftBackspaceKey.h
/*
* 파일명칭:CtrlShiftBackspaceKey.h
* 기능:컨트롤 쉬프트 백스페이스 키를 눌렀을때의 전략 헤더
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#ifndef _CTRLSHIFTBACKSPACEKEY_H
#define _CTRLSHIFTBACKSPACEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftBackspaceKey :public KeyAction {
public:
	CtrlShiftBackspaceKey(Notepannel* notepannel);
	virtual ~CtrlShiftBackspaceKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTBACKSPACEKEY_H
