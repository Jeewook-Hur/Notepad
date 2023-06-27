//CtrlAKey.h
/*
* 파일명칭:CtrlAKey.h
* 기능:ctrl과 A키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#ifndef _CTRLAKEY_H
#define _CTRLAKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlAKey :public KeyAction {
public:
	CtrlAKey(Notepannel* notepannel);
	virtual ~CtrlAKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLAKEY_H
