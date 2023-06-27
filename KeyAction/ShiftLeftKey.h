//ShiftLeftKey.h
/*
* 파일명칭:ShiftLeftKey.h
* 기능:shift와 왼쪽 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _SHIFTLEFTKEY_H
#define _SHIFTLEFTKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftLeftKey :public KeyAction {
public:
	ShiftLeftKey(Notepannel* notepannel);
	virtual ~ShiftLeftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTLEFTKEY_H
