//DateCommand.cpp
/*
* ���ϸ�Ī:DateCommand.cpp
* ���:��¥ Ŀ���
* �ۼ���:������
* �ۼ�����:2023/1/31
*/
#include "DateCommand.h"
#include "Notepannel.h"
#include "Paper.h"
#include "GlyphCreater.h"
#include "CommandCreator.h"
#include "MacroCommand.h"
#include "resource.h"
#include<ctime>
#include<string>
#pragma warning(disable:4996) //localtime���� �ʿ� 

/*
* �Լ���Ī:DateCommand
* ���:������
*/
DateCommand::DateCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~DateCommand
* ���:�Ҹ���
*/
DateCommand::~DateCommand() {
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����Ѵ�. 
*/
void DateCommand::Execute() {
	time_t timer; 
	struct tm* today;
	time(&timer);
	today = localtime(&timer);
	int year = today->tm_year + 1900;
	int month = today->tm_mon + 1;
	int day = today->tm_mday;
	int hour = today->tm_hour;
	int min = today->tm_min;
	CString noon = "����";

	if (hour > 12) {
		noon = "����";
		hour = hour - 12;
	}
	
	CString timeToPrint;
	timeToPrint.Format("%s %d:%02d %d-%d-%d", _T(noon), hour, min, year, month, day);

	string timeInString;
	timeInString = timeToPrint;

	GlyphCreater glyphCreater;
	Glyph* datePaper;
	datePaper = glyphCreater.Create(timeInString);

	CommandCreator commandCreater(this->notepannel);
	Command* command = NULL;

	if (this->notepannel->isSelected == TRUE) {//���õǾ�����
		//���õ� ������ �����Ѵ�. 
		command = commandCreater.Create(IDM_FORMAT_DELETE);
		if (command != NULL) {
			command->Execute();
			this->notepannel->macroCommand->Add(command, 0);
			command = NULL;
		}
	}
	//���� ��ġ�� �ٲ� ������ ���δ�. 
	command = commandCreater.Create(IDM_FORMAT_PASTE, datePaper);
	if (command != NULL) {
		command->Execute();
		this->notepannel->macroCommand->Add(command, 1); //��ũ�� �÷��׸� �ø���. 
	}




	//������Ʈ�� �Ѵ�.(��ġ)
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->Notify();
	//Ŭ���̾�Ʈ�� �����Ѵ�.
	this->notepannel->Invalidate(TRUE);

	this->notepannel->ShowCaret();


	delete datePaper;
}
