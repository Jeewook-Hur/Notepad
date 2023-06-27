//PasteCommand.h
/*
* ���ϸ�Ī:PasteCommand.h
* ���:�ٿ��ֱ⸦ �ϴ� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/21
*/
#ifndef _PASTECOMMAND_H
#define _PASTECOMMAND_H
#include "Command.h"

class Glyph;
class Notepannel;
class PasteCommand : public Command {
public:
	PasteCommand(Notepannel* notepannel);
	PasteCommand(Notepannel* notepannel, Glyph* paper);
	virtual ~PasteCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
	Glyph* previousPaper;
	Long frontLineLocation;
	Long frontCharLocation;
	Long endLineLocation;
	Long endCharLocation;
};

#endif // !_PASTECOMMAND_H
