//ScrollInfoControl.h
/*
* 파일명칭:ScrollInfoControl.h
* 기능:스크롤의 설정을 조정하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/9/29
*/
#ifndef _SCROLLCONTROL_H
#define _SCROLLCONTROL_H
#include "Observer.h"

class Notepannel;
class ScrollInfoControl : public Observer {
public:
	ScrollInfoControl(Notepannel* notepannel);
	virtual ~ScrollInfoControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_SCROLLCONTROL_H
