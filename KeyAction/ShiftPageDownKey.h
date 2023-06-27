//ShiftPageDownKey.h
/*
* 파일명칭:ShiftPageDownKey.h
* 기능:shift와 PgDn키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _SHIFTPAGEDOWNKEY_H
#define _SHIFTPAGEDOWNKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftPageDownKey :public KeyAction {
public:
	ShiftPageDownKey(Notepannel* notepannel);
	virtual ~ShiftPageDownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTPAGEDOWNKEY_H
