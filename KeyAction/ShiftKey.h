//ShiftKey.h
/*
* 파일명칭:ShiftKey.h
* 기능:shift키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/18
*/
#ifndef _SHIFTKEY_H
#define _SHIFTKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftKey :public KeyAction {
public:
	ShiftKey(Notepannel* notepannel);
	virtual ~ShiftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTKEY_H
