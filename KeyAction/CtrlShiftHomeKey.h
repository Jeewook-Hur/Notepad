//CtrlShiftHomeKey.h
/*
* 파일명칭:CtrlShiftHomeKey.h
* 기능:ctrl키와 shift키와 홈키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _CTRLSHIFTHOMEKEY_H
#define _CTRLSHIFTHOMEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftHomeKey :public KeyAction {
public:
	CtrlShiftHomeKey(Notepannel* notepannel);
	virtual ~CtrlShiftHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTHOMEKEY_H
