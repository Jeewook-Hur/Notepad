//AutoScrollPositionControl.h
/*
* 파일명칭:AutoScrollPositionControl.h
* 기능:캐럿에 맞추어 클라이언트를 자동이동시키는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/10/1
*/
#ifndef _AUTOSCROLLPOSITIONCONTROL_H
#define _AUTOSCROLLPOSITIONCONTROL_H
#include "Observer.h"

class Notepannel;
class AutoScrollPositionControl : public Observer {
public:
	AutoScrollPositionControl(Notepannel* notepannel);
	virtual ~AutoScrollPositionControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_AUTOSCROLLPOSITIONCONTROL_H
