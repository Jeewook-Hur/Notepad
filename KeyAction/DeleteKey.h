//DeleteKey.h
/*
* 파일명칭:DeleteKey.h
* 기능:딜리트키를 눌렀을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/16
*/
#ifndef _DELETEKEY_H
#define _DELETEKEY_H
#include "KeyAction.h"

class Notepannel;

class DeleteKey :public KeyAction {
public:
	DeleteKey(Notepannel* notepannel);
	virtual ~DeleteKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_DELETEKEY_H
