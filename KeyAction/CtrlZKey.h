//CtrlZKey.h
/*
* 파일명칭:CtrlZKey.h
* 기능:ctrl과 Z키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#ifndef _CTRLZKEY_H
#define _CTRLZKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlZKey :public KeyAction {
public:
	CtrlZKey(Notepannel* notepannel);
	virtual ~CtrlZKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLZKEY_H
