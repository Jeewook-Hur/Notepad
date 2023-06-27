//ShiftRightKey.h
/*
* 파일명칭:ShiftRightKey.h
* 기능:shift와 오른쪽 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _SHIFTRIGHTKEY_H
#define _SHIFTRIGHTKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftRightKey :public KeyAction {
public:
	ShiftRightKey(Notepannel* notepannel);
	virtual ~ShiftRightKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTRIGHTKEY_H
