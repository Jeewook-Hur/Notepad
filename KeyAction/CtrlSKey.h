//CtrlSKey.h
/*
* 파일명칭:CtrlSKey.h
* 기능:ctrl과 S키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLSKEY_H
#define _CTRLSKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlSKey :public KeyAction {
public:
	CtrlSKey(Notepannel* notepannel);
	virtual ~CtrlSKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSKEY_H
