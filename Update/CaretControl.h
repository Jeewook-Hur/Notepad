//CaretControl.h
/*
* 파일명칭:CaretControl.h
* 기능:캐럿을 조정하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/8/9
*/
#ifndef _CARETCONTROL_H
#define _CARETCONTROL_H
#include "Observer.h"

class Notepannel;
class CaretControl : public Observer {
public:
	CaretControl(Notepannel* notepannel);
	virtual ~CaretControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_CARETCONTROL_H
