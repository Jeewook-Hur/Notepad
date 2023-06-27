//CtrlLeftKey.h
/*
* 파일명칭:CtrlLeftKey.h
* 기능:컨트롤과 왼쪽 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _CTRLLEFTKEY_H
#define _CTRLLEFTKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlLeftKey :public KeyAction {
public:
	CtrlLeftKey(Notepannel* notepannel);
	virtual ~CtrlLeftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLLEFTKEY_H
