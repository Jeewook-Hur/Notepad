//ZoomOutCommand.h
/*
* 파일명칭:ZoomOutCommand.h
* 기능:화면 축소하기 메뉴에 대한 명령(Command)의 헤더
* 작성자:허지욱
* 작성일자:20221007
*/
#ifndef _ZOOMOUTCOMMAND_H
#define _ZOOMOUTCOMMAND_H
#include "Command.h"

class Notepannel;
class ZoomOutCommand : public Command {
public:
	ZoomOutCommand(Notepannel* notepannel);
	virtual ~ZoomOutCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_ZOOMOUTCOMMAND_H
