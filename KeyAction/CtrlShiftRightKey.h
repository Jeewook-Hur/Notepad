//CtrlShiftRightKey.h
/*
* 파일명칭:CtrlShiftRightKey.h
* 기능:ctrl키와 shift와 오른쪽 화살표를 클릭했을때의 전략의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _CTRLSHIFTRIGHTKEY_H
#define _CTRLSHIFTRIGHTKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftRightKey :public KeyAction {
public:
	CtrlShiftRightKey(Notepannel* notepannel);
	virtual ~CtrlShiftRightKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTRIGHTKEY_H
