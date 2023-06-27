//CtrlShiftZKey.h
/*
* 파일명칭:CtrlShiftZKey.h
* 기능:ctrl과 shift와 Z키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#ifndef _CTRLSHIFTZKEY_H
#define _CTRLSHIFTZKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftZKey :public KeyAction {
public:
	CtrlShiftZKey(Notepannel* notepannel);
	virtual ~CtrlShiftZKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTZKEY_H
