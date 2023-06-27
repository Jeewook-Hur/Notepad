//ShiftEndKey.h
/*
* 파일명칭:ShiftEndKey.h
* 기능:shift와 엔드키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _SHIFTENDKEY_H
#define _SHIFTENDKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftEndKey :public KeyAction {
public:
	ShiftEndKey(Notepannel* notepannel);
	virtual ~ShiftEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTENDKEY_H
#pragma once
