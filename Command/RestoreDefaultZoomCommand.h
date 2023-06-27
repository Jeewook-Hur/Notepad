//RestoreDefaultZoomCommand.h
/*
* 파일명칭:RestoreDefaultZoomCommand.h
* 기능:화면 확대/축소하기 기본값 복원 메뉴에 대한 명령(Command)의 헤더
* 작성자:허지욱
* 작성일자:20221007
*/
#ifndef _RESTOREDEFALTZOOM_H
#define _RESTOREDEFALTZOOM_H
#include "Command.h"

class Notepannel;
class RestoreDefaultZoomCommand : public Command {
public:
	RestoreDefaultZoomCommand(Notepannel* notepannel);
	virtual ~RestoreDefaultZoomCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_RESTOREDEFALTZOOM_H
