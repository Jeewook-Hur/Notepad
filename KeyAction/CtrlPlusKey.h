//CtrlPlusKey.h
/*
* 파일명칭:CtrlPlusKey.h
* 기능:ctrl과 +키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLPLUSKEY_H
#define _CTRLPLUSKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlPlusKey :public KeyAction {
public:
	CtrlPlusKey(Notepannel* notepannel);
	virtual ~CtrlPlusKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLPLUSKEY_H
