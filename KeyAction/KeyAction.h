//KeyAction.h
/*
* 파일명칭:KeyAction.h
* 기능:키액션 가상함수의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _KEYACTION_H
#define _KEYACTION_H

typedef unsigned int UINT;
class KeyAction {
public:
	KeyAction();
	virtual ~KeyAction() = 0;
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
};

#endif// !_KEYACTION_H