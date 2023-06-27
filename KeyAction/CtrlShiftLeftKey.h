//CtrlShiftLeftKey.h
/*
* 파일명칭:CtrlShiftLeftKey.h
* 기능:shift와 ctrl키와 오른쪽 화살표를 클릭했을때의 전략 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _CTRLSHIFTLEFTKEY_H
#define _CTRLSHIFTLEFTKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftLeftKey :public KeyAction {
public:
	CtrlShiftLeftKey(Notepannel* notepannel);
	virtual ~CtrlShiftLeftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTLEFTKEY_H
