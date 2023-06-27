//CtrlGKey.h
/*
* 파일명칭:CtrlGKey.h
* 기능:ctrl과 G키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLGKEY_H
#define _CTRLGKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlGKey :public KeyAction {
public:
	CtrlGKey(Notepannel* notepannel);
	virtual ~CtrlGKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLGKEY_H
