//ShiftUpKey.h
/*
* 파일명칭:ShiftUpKey.h
* 기능:shift와 위쪽 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _SHIFTUPKEY_H
#define _SHIFTUPKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftUpKey :public KeyAction {
public:
	ShiftUpKey(Notepannel* notepannel);
	virtual ~ShiftUpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTUPKEY_H
