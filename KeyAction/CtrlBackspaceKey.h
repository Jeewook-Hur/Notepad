//CtrlBackspaceKey.h
/*
* 파일명칭:CtrlBackspaceKey.h
* 기능:컨트롤 백스페이스 키를 눌렀을때의 전략 헤더
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#ifndef _CTRLBACKSPACEKEY_H
#define _CTRLBACKSPACEKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlBackspaceKey :public KeyAction {
public:
	CtrlBackspaceKey(Notepannel* notepannel);
	virtual ~CtrlBackspaceKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLBACKSPACEKEY_H
