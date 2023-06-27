//ShiftHomeKey.h
/*
* 파일명칭:ShiftHomeKey.h
* 기능:shift와 홈키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _SHIFTHOMEKEY_H
#define _SHIFTHOMEKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftHomeKey :public KeyAction {
public:
	ShiftHomeKey(Notepannel* notepannel);
	virtual ~ShiftHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTHOMEKEY_H
