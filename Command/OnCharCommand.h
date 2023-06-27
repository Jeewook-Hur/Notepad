//OnCharCommand.h
/*
* ���ϸ�Ī:OnCharCommand.h
* ���:�̱۹���Ʈ Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/11/29
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
