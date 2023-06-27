//CtrlFKey.h
/*
* 파일명칭:CtrlFKey.h
* 기능:ctrl과 F키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/12/7
*/
#ifndef _CTRLFKEY_H
#define _CTRLFKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlFKey :public KeyAction {
public:
	CtrlFKey(Notepannel* notepannel);
	virtual ~CtrlFKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLFKEY_H
