//StatusBarControl.h
/*
* 파일명칭:StatusBarControl.h
* 기능:상태표시줄을 조정하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2023/1/8
*/
#ifndef _STATUSBARCONTROL_H
#define _STATUSBARCONTROL_H
#include "Observer.h"

class Notepannel;
class StatusBarControl : public Observer {
public:
	StatusBarControl(Notepannel* notepannel);
	virtual ~StatusBarControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_STATUSBARCONTROL_H
