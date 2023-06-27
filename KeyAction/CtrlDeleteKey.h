//CtrlDeleteKey.h
/*
* 파일명칭:CtrlDeleteKey.h
* 기능:컨트롤 딜리트 키를 눌렀을때의 전략 헤더
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#ifndef _CTRLDELETEKEY_H
#define _CTRLDELETEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlDeleteKey :public KeyAction {
public:
	CtrlDeleteKey(Notepannel* notepannel);
	virtual ~CtrlDeleteKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLDELETEKEY_H
