//OnIDECharCommand.h
/*
* ���ϸ�Ī:OnIDECharCommand.h
* ���:�������Ʈ Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#ifndef _ONIDECHARCOMMAND_H
#define _ONIDECHARCOMMAND_H
#include "Command.h"
#include "Notepannel.h"

typedef unsigned int UINT;
typedef signed long int Long;
//class Notepannel;
class Glyph;
class OnIDECharCommand : public Command {
public:
	OnIDECharCommand(Notepannel* notepannel, WPARAM wParam, LPARAM lParam);
	virtual ~OnIDECharCommand();
	virtual void Execute();
	virtual void UnExecute();
private:
	Notepannel* notepannel;
	Glyph* character;
	Long lineLocation;
	Long charLocation;
};

#endif // !_ONIDECHARCOMMAND_H
