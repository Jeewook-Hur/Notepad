//PreviewCommand.h
/*
* 파일명칭:PreviewCommand.h
* 기능:미리보기 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/12/16
*/
#ifndef _PREVIEWCOMAND_H
#define _PREVIEWCOMAND_H
#include "Command.h"

class Notepannel;

class PreviewCommand :public Command {
public:
	PreviewCommand(Notepannel* notepannel);
	virtual ~PreviewCommand();
	virtual void Execute();
private:
	Notepannel* notepannel;
};

#endif // !_PREVIEWCOMAND_H
