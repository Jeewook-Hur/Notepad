//CtrlWKey.h
/*
* 파일명칭:CtrlWKey.h
* 기능:ctrl과 W키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLWKEY_H
#define _CTRLWKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlWKey :public KeyAction {
public:
	CtrlWKey(Notepannel* notepannel);
	virtual ~CtrlWKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLWKEY_H
