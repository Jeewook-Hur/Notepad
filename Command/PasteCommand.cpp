//PasteCommand.cpp
/*
* ���ϸ�Ī:PasteCommand.cpp
* ���:�ٿ��ֱ⸦ �ϴ� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/11/21
*/
#include "PasteCommand.h"
#include "Notepannel.h"
#include "Clipboard.h"
#include "KeyAction.h"
#include "KeyActionCreator.h"
#include "Command.h"
#include "CommandCreator.h"
#include "Caret.h"
#include "Select.h"
#include "MacroCommand.h"
#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"
#include "resource.h"
#include <string>
using namespace std;

/*
* �Լ���Ī:PasteCommand
* ���:������
*/
PasteCommand::PasteCommand(Notepannel* notepannel) :notepannel(notepannel) {
	GlyphCreater glyphCreater;
	Glyph* currentLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLength = -1;
	string stringToAdd;

	//���õǾ����� ���õ� ������ �����. 
	CommandCreator commandCreator(this->notepannel);
	Command* command = 0;
	if (this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		command->Execute();
		this->notepannel->macroCommand->Add(command);
	}

	//���� ��ġ�� ���Ѵ�. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	frontLineOrder = lineOrder;
	frontCharIndex = charIndex;

	//���� ��ġ�� ���� ��ġ�� �����Ѵ�.
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);

	this->endLineLocation = -1;
	this->endCharLocation = -2;

	//Ŭ������ Ŭ�������� ���ڿ��� �����´�.
	stringToAdd = this->notepannel->clipboard->GetData();
	//���ڿ��� ���������� ġȯ�Ѵ�. 
	this->previousPaper = glyphCreater.Create(stringToAdd);
}
PasteCommand::PasteCommand(Notepannel* notepannel, Glyph* paper) :notepannel(notepannel){
	Glyph* currentLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLength = -1;

	//���õǾ����� ���õ� ������ �����. 
	CommandCreator commandCreator(this->notepannel);
	Command* command = 0;
	if (this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		command->Execute();
		this->notepannel->macroCommand->Add(command);
	}

	//���� ��ġ�� ���Ѵ�. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	frontLineOrder = lineOrder;
	frontCharIndex = charIndex;

	//���� ��ġ�� ���� ��ġ�� �����Ѵ�.
	this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &this->frontLineLocation, &this->frontCharLocation);

	this->endLineLocation = -1;
	this->endCharLocation = -2;

	this->previousPaper = paper->Clone();
	this->previousPaper->MergeAllDummyLines();

}

/*
* �Լ���Ī:~PasteCommand
* ���:�Ҹ���
*/
PasteCommand::~PasteCommand() {
	delete this->previousPaper;
}

/*
* �Լ���Ī:Execute
* ���:�����ϱ� Ŀ��带 �����Ѵ�.
*/
void PasteCommand::Execute() {
	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	KeyActionCreator keyActionCreator(this->notepannel);
	KeyAction* keyAction = NULL;
	Glyph* currentLine = NULL;
	Long frontLineOrder = -1;
	Long frontCharIndex = -2;
	Long endLineOrder = -1;
	Long endCharIndex = -2;
	Long lineOrder = -1;
	Long charIndex = -2;

	//���̿� ����
	this->notepannel->paper->MergeAllDummyLines();

	//���� ��ġ�� ���� ��ġ�� ġȯ�Ѵ�.
	this->notepannel->paper->MoveToLocation(this->frontLineLocation, this->frontCharLocation, &frontLineOrder, &frontCharIndex);
	//���� ������ ���δ�. 
	this->notepannel->paper->Add(this->previousPaper, frontLineOrder, frontCharIndex);
	//���� ��ġ�� ���Ѵ�. 
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//���� ��ġ�� ������ ��ġ�� �����ϰ� ���� ��ġ�� ���Ѵ�. 
	endLineOrder = lineOrder;
	endCharIndex = charIndex;
	this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &this->endLineLocation, &this->endCharLocation);
	//�ٿ� ���� ��ġ�� �����Ѵ�. 
	//delete this->notepannel->select;
	//this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	//���� ��ġ�� �̵��Ѵ�.
	lineOrder = this->notepannel->paper->Move(lineOrder);
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->Move(charIndex);

	//������Ʈ�� �Ѵ�(��ġ, ���� ��)
	this->notepannel->hasChanged = TRUE;
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//Ŭ���̾�Ʈ�� �����ϴ�.
	this->notepannel->Invalidate(TRUE);
	//ĳ���� ����Ѵ�.
	this->notepannel->caret->ShowCaret();

}

/*
* �Լ���Ī:UnExecute
* ���:�����ϱ� Ŀ��带 ��������Ѵ�.
*/
void PasteCommand::UnExecute() {
	Glyph* currentLine = 0;
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

	//������Ʈ�� �Ѵ�(��ġ, ���� ��)
	this->notepannel->hasChanged = TRUE;
	this->notepannel->documentUploaded = TRUE;
	this->notepannel->clientMoveCheck = TRUE;
	this->notepannel->Notify();
	//Ŭ���̾�Ʈ�� �����ϴ�.
	this->notepannel->Invalidate(TRUE);
	//ĳ���� ����Ѵ�.
	this->notepannel->caret->ShowCaret();
}