//CtrlPKey.h
/*
* 파일명칭:CtrlPKey.h
* 기능:ctrl과 P키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/12/19
*/
#ifndef _CTRLPKEY_H
#define _CTRLPKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlPKey :public KeyAction {
public:
	CtrlPKey(Notepannel* notepannel);
	virtual ~CtrlPKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLPKEY_H
