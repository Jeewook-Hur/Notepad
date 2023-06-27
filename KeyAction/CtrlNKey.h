//CtrlNKey.h
/*
* 파일명칭:CtrlNKey.h
* 기능:ctrl과 N키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLNKEY_H
#define _CTRLNKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlNKey :public KeyAction {
public:
	CtrlNKey(Notepannel* notepannel);
	virtual ~CtrlNKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLNKEY_H
