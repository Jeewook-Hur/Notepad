//PreviewCommand.h
/*
* ���ϸ�Ī:PreviewCommand.h
* ���:�̸����� Ŀ����� ���
* �ۼ���:������
* �ۼ�����:2022/12/16
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
