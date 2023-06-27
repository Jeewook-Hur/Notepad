//ShiftDownKey.h
/*
* 파일명칭:ShiftDownKey.h
* 기능:shift와 아래쪽 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _SHIFTDOWNKEY_H
#define _SHIFTDOWNKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftDownKey :public KeyAction {
public:
	ShiftDownKey(Notepannel* notepannel);
	virtual ~ShiftDownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTDOWNKEY_H
