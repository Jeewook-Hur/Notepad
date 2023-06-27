//CtrlShiftDeleteKey.h
/*
* 파일명칭:CtrlShiftDeleteKey.h
* 기능:컨트롤 쉬프트 딜리트 키를 눌렀을때의 전략 헤더
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#ifndef _CTRLSHIFTDELETEKEY_H
#define _CTRLSHIFTDELETEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftDeleteKey :public KeyAction {
public:
	CtrlShiftDeleteKey(Notepannel* notepannel);
	virtual ~CtrlShiftDeleteKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTDELETEKEY_H
