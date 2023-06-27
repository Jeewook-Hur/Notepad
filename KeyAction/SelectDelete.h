//SelectDelete.h
/*
* 파일명칭:SelectDelete.h
* 기능:선택영역을 지울때의 키액션 헤더
* 작성자:허지욱
* 작성일자:2022/11/15
*/
#ifndef _SELECTDELETE_H
#define _SELECTDELETE_H
#include "KeyAction.h"

class Notepannel;

class SelectDelete :public KeyAction {
public:
	SelectDelete(Notepannel* notepannel);
	virtual ~SelectDelete();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_SELECTDELETE_H
