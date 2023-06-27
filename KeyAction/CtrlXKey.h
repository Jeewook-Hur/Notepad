//CtrlXKey.h
/*
* 파일명칭:CtrlXKey.h
* 기능:ctrl과 X키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLXKEY_H
#define _CTRLXKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlXKey :public KeyAction {
public:
	CtrlXKey(Notepannel* notepannel);
	virtual ~CtrlXKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLXKEY_H
