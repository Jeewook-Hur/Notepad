//CutCommand.cpp
/*
* ���ϸ�Ī:CutCommand.cpp
* ���:�߶󳻱⸦ �ϴ� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "CutCommand.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "KeyAction.h"
#include "KeyActionCreator.h"
#include "CommandCreator.h"
#include "resource.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "Document.h"
#include "Caret.h"

/*
* �Լ���Ī:CutCommand
* ���:������
*/
CutCommand::CutCommand(Notepannel* notepannel) :notepannel(notepannel) {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL; Glyph* currentLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLength = -1;

	//Ŭ�����忡 ������ �����Ѵ�. 
	command = commandCreator.Create(IDM_FORMAT_COPY);
	if (command != NULL) { //Ŀ��Ʈ�� ��ȯ�Ǿ������
		command->Execute();
	}
	delete command;

	//���� ��ġ�� ���Ѵ�. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	frontLineOrder = this->notepannel->select->frontLineOrder;
	frontCharIndex = this->notepannel->select->frontXIndex;
	endLineOrder = this->notepannel->select->endLineOrder;
	endCharIndex = this->notepannel->select->endXIndex;

	//���� ��ġ�� ���� ��ġ�� �����Ѵ�.
	this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &this->endLineLocation, &this->endCharLocation);
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);

	//���� ��ġ�� �������� ���Ѵ�. 
	this->previousPaper = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
	this->previousPaper->MergeAllDummyLines();
}

/*
* �Լ���Ī:~CutCommand
* ���:�Ҹ���
*/
CutCommand::~CutCommand() {
	delete this->previousPaper;
}

/*
* �Լ���Ī:Execute
* ���:�ڸ��� Ŀ��带 �����Ѵ�.
*/
void CutCommand::Execute() {
	KeyActionCreator keyActionCreator(this->notepannel);
	KeyAction* keyAction = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;

	//���̿� ����
	this->notepannel->paper->MergeAllDummyLines();

	//���� ��ġ�� ���� ��ġ�� ġȯ�Ѵ�.
	this->notepannel->paper->MoveToLocation(this->frontLineLocation, this->frontCharLocation, &frontLineOrder, &frontCharIndex);
	this->notepannel->paper->MoveToLocation(this->endLineLocation, this->endCharLocation, &endLineOrder, &endCharIndex);

	//���� ������ ������ �����. 
	this->notepannel->paper->Remove(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);

	//���� ��ġ�� �̵��Ѵ�.
	this->notepannel->paper->Move(frontLineOrder);
	this->notepannel->paper->GetAt(frontLineOrder)->Move(frontCharIndex);

	//����Ŭ������ �ʱ�ȭ�Ѵ�.
	delete this->notepannel->select;
	this->notepannel->select = new Select(notepannel);

	//������ ����Ǿ����� ǥ���Ѵ�. 
	this->notepannel->hasChanged = TRUE;

	//�������� ������ �����Ѵ�.
	CString windowTitle;
	windowTitle.Format("*%s - Windows �޸���", this->notepannel->document->GetName().c_str());
	this->notepannel->notepad->SetWindowText(windowTitle);

	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//deleteŰ�� ��� ȣ���� ���ϱ⿡ ȣ���Լ��� �ʿ��ϴ�. 
	this->notepannel->Invalidate(TRUE);
	//ĳ���� ���̰��Ѵ�.
	this->notepannel->caret->ShowCaret();
}

/*
* �Լ���Ī:UnExecute
* ���:�ڸ��� Ŀ��带 ��������Ѵ�.
*/
void CutCommand::UnExecute() {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;


	//���̿� ����
	this->notepannel->paper->MergeAllDummyLines();

	//���� ���� ��ġ�� ���� ��ġ�� ġȯ�Ѵ�.
	this->notepannel->paper->MoveToLocation(this->frontLineLocation, this->frontCharLocation, &frontLineOrder, &frontCharIndex);
	//���� ��ġ�� ����� ������ �����Ѵ�.
	this->notepannel->paper->Add(this->previousPaper, frontLineOrder, frontCharIndex);
	//���� ���� ��ġ�� ���� ��ġ�� ġȯ�Ѵ�.
	this->notepannel->paper->MoveToLocation(this->endLineLocation, this->endCharLocation, &endLineOrder, &endCharIndex);
	//������ ��ġ�� ������ �̵��Ѵ�. 
	lineOrder = this->notepannel->paper->Move(endLineOrder);
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	currentLine->Move(endCharIndex);

	//�����ߴ� ��ġ�� ǥ���Ѵ�. 
	delete this->notepannel->select;
	this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);

	//������ ����Ǿ����� ǥ���Ѵ�. 
	this->notepannel->hasChanged = TRUE;

	//�������� ������ �����Ѵ�.
	CString windowTitle;
	windowTitle.Format("*%s - Windows �޸���", this->notepannel->document->GetName().c_str());
	this->notepannel->notepad->SetWindowText(windowTitle);

	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//deleteŰ�� ��� ȣ���� ���ϱ⿡ ȣ���Լ��� �ʿ��ϴ�. 
	this->notepannel->Invalidate(TRUE);
	//ĳ���� ���̰��Ѵ�.
	this->notepannel->caret->ShowCaret();
}