//CtrlZeroKey.h
/*
* 파일명칭:CtrlZeroKey.h
* 기능:ctrl과 0키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLZEROKEY_H
#define _CTRLZEROKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlZeroKey :public KeyAction {
public:
	CtrlZeroKey(Notepannel* notepannel);
	virtual ~CtrlZeroKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLZEROKEY_H
