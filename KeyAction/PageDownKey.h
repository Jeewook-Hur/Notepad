//PageDownKey.h
/*
* 파일명칭:PageDownKey.h
* 기능:페이지다운 키를 클릭했을때의 이벤트를 수행하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/10/5
*/
#ifndef _PAGEDOWNKEY_H
#define _PAGEDOWNKEY_H
#include "KeyAction.h"

class Notepannel;
class PageDownKey : public KeyAction {
public:
	PageDownKey(Notepannel* notepannel);
	virtual ~PageDownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_PAGEDOWNKEY_H