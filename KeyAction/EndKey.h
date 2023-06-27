//EndKey.h
/*
* 파일명칭:EndKey.h
* 기능:엔드키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#ifndef _ENDKEY_H
#define _ENDKEY_H
#include "KeyAction.h"

class Notepannel;

class EndKey :public KeyAction {
public:
	EndKey(Notepannel* notepannel);
	virtual ~EndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_ENDKEY_H
