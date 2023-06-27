//DocumentVirtualSizeControl.h
/*
* 파일명칭:DocumentVirtualSizeControl.h
* 기능:문서의 가상크기를 조정하는 클래스의 헤더
* 작성자:허지욱
* 작성일자:2022/9/29
*/
#ifndef _DOCUMENTVERTUALSIZECONTROL_H
#define _DOCUMENTVERTUALSIZECONTROL_H
#include "Observer.h"

class Notepannel;
class DocumentVirtualSizeControl : public Observer {
public:
	DocumentVirtualSizeControl(Notepannel* notepannel);
	virtual ~DocumentVirtualSizeControl();
	virtual void Update(Subject* theChangedSubject);
private:
	Notepannel* notepannel;
};

#endif // !_DOCUMENTVERTUALSIZECONTROL_H
