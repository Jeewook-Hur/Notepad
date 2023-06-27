//CtrlHomeKey.h
/*
* 파일명칭:CtrlHomeKey.h
* 기능:컨트롤과 홈키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _CTRLHOMEKEY_H
#define _CTRLHOMEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlHomeKey :public KeyAction {
public:
	CtrlHomeKey(Notepannel* notepannel);
	virtual ~CtrlHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLHOMEKEY_H
