//CtrlHKey.h
/*
* 파일명칭:CtrlHKey.h
* 기능:ctrl과 H키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/12/8
*/
#ifndef _CTRLHKEY_H
#define _CTRLHKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlHKey :public KeyAction {
public:
	CtrlHKey(Notepannel* notepannel);
	virtual ~CtrlHKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLHKEY_H
