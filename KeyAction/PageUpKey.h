//PageUpKey.h
/*
* 파일명칭:PageUpKey.h
* 기능:페이지업키를 클릭했을때의 이벤트를 수행하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/10/5
*/
#ifndef _PAGEUPKEY_H
#define _PAGEUPKEY_H
#include "KeyAction.h"

class Notepannel;
class PageUpKey : public KeyAction {
public:
	PageUpKey(Notepannel* notepannel);
	virtual ~PageUpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_PAGEUPKEY_H