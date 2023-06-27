//RightKey.h
/*
* 파일명칭:RightKey.h
* 기능:오른쪽 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _RIGTHKEY_H
#define _RIGTHKEY_H
#include "KeyAction.h"

class Notepannel;

class RightKey :public KeyAction {
public:
	RightKey(Notepannel* notepannel);
	virtual ~RightKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_RIGTHKEY_H
