//CtrlShiftSKey.h
/*
* 파일명칭:CtrlShiftSKey.h
* 기능:ctrl과 shift와 S키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLSHFITSKEY_H
#define _CTRLSHFITSKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftSKey :public KeyAction {
public:
	CtrlShiftSKey(Notepannel* notepannel);
	virtual ~CtrlShiftSKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHFITSKEY_H
