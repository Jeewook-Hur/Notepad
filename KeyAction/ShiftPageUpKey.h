//ShiftPageUpKey.h
/*
* 파일명칭:ShiftPageUpKey.h
* 기능:shift와 페이지업키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _SHIFTPAGEUPKEY_H
#define _SHIFTPAGEUPKEY_H
#include "KeyAction.h"

class Notepannel;

class ShiftPageUpKey :public KeyAction {
public:
	ShiftPageUpKey(Notepannel* notepannel);
	virtual ~ShiftPageUpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SHIFTPAGEUPKEY_H
