//LeftKey.h
/*
* 파일명칭:LeftKey.h
* 기능:왼쪽 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _LEFTKEY_H
#define _LEFTKEY_H
#include "KeyAction.h"

class Notepannel;

class LeftKey :public KeyAction {
public:
	LeftKey(Notepannel* notepannel);
	virtual ~LeftKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_LEFTKEY_H
