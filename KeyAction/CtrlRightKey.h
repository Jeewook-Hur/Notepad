//CtrlRightKey.h
/*
* 파일명칭:CtrlRightKey.h
* 기능:컨트롤과 오른쪽 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _CTRLRIGHTKEY_H
#define _CTRLRIGHTKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlRightKey :public KeyAction {
public:
	CtrlRightKey(Notepannel* notepannel);
	virtual ~CtrlRightKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLRIGHTKEY_H
