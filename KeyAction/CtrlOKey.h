//CtrlOKey.h
/*
* 파일명칭:CtrlOKey.h
* 기능:ctrl과 O키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLOKEY_H
#define _CTRLOKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlOKey :public KeyAction {
public:
	CtrlOKey(Notepannel* notepannel);
	virtual ~CtrlOKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLOKEY_H
