//OnCharCommand.h
/*
* 파일명칭:OnCharCommand.h
* 기능:싱글바이트 커멘드의 헤더
* 작성자:허지욱
* 작성일자:2022/11/29
*/
#ifndef _ONCHARCOMMAND_H
#define _ONCHARCOMMAND_H
#include "Command.h"

typedef unsigned int UINT;
typedef signed long int Long;
class Notepannel;
class Glyph;
class OnCharCommand : public Command {
public:
	OnCharCommand(Notepannel* notepannel, UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual ~OnCharCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
	Glyph* character;
	Long lineLocation;
	Long charLocation;
};

#endif // !_ONCHARCOMMAND_H
