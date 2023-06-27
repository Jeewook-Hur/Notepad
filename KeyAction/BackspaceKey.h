//BackspaceKey.h
/*
* 파일명칭:BackspaceKey.h
* 기능:백스페이스키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/16
*/
#ifndef _BACKSPACEKEY_H
#define _BACKSPACEKEY_H
#include "KeyAction.h"

class Notepannel;

class BackspaceKey :public KeyAction {
public:
	BackspaceKey(Notepannel* notepannel);
	virtual ~BackspaceKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_BACKSPACEKEY_H
