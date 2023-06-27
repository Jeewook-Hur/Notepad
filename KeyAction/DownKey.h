//DownKey.h
/*
* 파일명칭:DownKey.h
* 기능:아래 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _DOWNKEY_H
#define _DOWNKEY_H
#include "KeyAction.h"

class Notepannel;

class DownKey :public KeyAction {
public:
	DownKey(Notepannel* notepannel);
	virtual ~DownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_DOWNKEY_H
