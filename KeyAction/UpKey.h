//UpKey.h
/*
* 파일명칭:UpKey.h
* 기능:위 화살표를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _UPKEY_H
#define _UPKEY_H
#include "KeyAction.h"

class Notepannel;

class UpKey : public KeyAction {
public:
	UpKey(Notepannel* notepannel);
	virtual ~UpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_UPKEY_H
