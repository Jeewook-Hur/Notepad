//CtrlVKey.h
/*
* 파일명칭:CtrlVKey.h
* 기능:ctrl과 V키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLVKEY_H
#define _CTRLVKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlVKey :public KeyAction {
public:
	CtrlVKey(Notepannel* notepannel);
	virtual ~CtrlVKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLVKEY_H
