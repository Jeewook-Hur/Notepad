//CtrlEndKey.h
/*
* 파일명칭:CtrlEndKey.h
* 기능:컨트롤과 엔드키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _CTRLENDKEY_H
#define _CTRLENDKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlEndKey :public KeyAction {
public:
	CtrlEndKey(Notepannel* notepannel);
	virtual ~CtrlEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLENDKEY_H
