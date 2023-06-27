//F5Key.h
/*
* 파일명칭:F5Key.h
* 기능:F5키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2023/1/31
*/
#ifndef _F5KEY_H
#define _F5KEY_H
#include "KeyAction.h"

class Notepannel;

class F5Key :public KeyAction {
public:
	F5Key(Notepannel* notepannel);
	virtual ~F5Key();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_F5KEY_H
