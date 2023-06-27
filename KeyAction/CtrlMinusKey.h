//CtrlMinusKey.h
/*
* 파일명칭:CtrlMinusKey.h
* 기능:ctrl과 -키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLMINUSKEY_H
#define _CTRLMINUSKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlMinusKey :public KeyAction {
public:
	CtrlMinusKey(Notepannel* notepannel);
	virtual ~CtrlMinusKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLMINUSKEY_H
