//CtrlCKey.h
/*
* 파일명칭:CtrlCKey.h
* 기능:ctrl과 C키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#ifndef _CTRLCKEY_H
#define _CTRLCKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlCKey :public KeyAction {
public:
	CtrlCKey(Notepannel* notepannel);
	virtual ~CtrlCKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLCKEY_H
