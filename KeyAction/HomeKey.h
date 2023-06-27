//HomeKey.h
/*
* 파일명칭:HomeKey.h
* 기능:홈키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _HOMEKEY_H
#define _HOMEKEY_H
#include "KeyAction.h"

class Notepannel;

class HomeKey :public KeyAction {
public:
	HomeKey(Notepannel* notepannel);
	virtual ~HomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_HOMEKEY_H
