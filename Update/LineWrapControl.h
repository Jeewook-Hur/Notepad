//LineWrapControl.h
/*
* 파일명칭:LineWrapControl.h
* 기능:자동 줄바꿈을 조정하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/9/21
*/
#ifndef _LINEWRAPCONTROL_H
#define _LINEWRAPCONTROL_H
#include "Observer.h"

class Notepannel;
class LineWrapControl : public Observer {
public:
	LineWrapControl(Notepannel* notepannel);
	virtual ~LineWrapControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_LINEWRAPCONTROL_H
