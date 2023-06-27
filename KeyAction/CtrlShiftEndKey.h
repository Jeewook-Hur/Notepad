//CtrlShiftEndKey.h
/*
* 파일명칭:CtrlShiftEndKey.h
* 기능:ctrl키와 shift키와 엔드키를 클릭했을때의 헤더
* 작성자:허지욱
* 작성일자:2022/10/31
*/
#ifndef _CTRLSHIFTENDKEY_H
#define _CTRLSHIFTENDKEY_H
#include "KeyAction.h"

class Notepannel;

class CtrlShiftEndKey :public KeyAction {
public:
	CtrlShiftEndKey(Notepannel* notepannel);
	virtual ~CtrlShiftEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_CTRLSHIFTENDKEY_H
