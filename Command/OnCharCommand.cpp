//OnCharCommand.cpp
/*
* ���ϸ�Ī:OnCharCommand.cpp
* ���:�̱۹���Ʈ�� �Է� �ϴ� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#include "OnCharCommand.h"
#include "Notepannel.h"
#include "Select.h"
#include "CommandCreator.h"
#include "MacroCommand.h"

#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"
#include "resource.h"

/*
* �Լ���Ī:OnCharCommand
* ���:������
*/
OnCharCommand::OnCharCommand(Notepannel* notepannel, UINT nChar, UINT nRepCnt, UINT nFlags) : notepannel(notepannel) {
	this->character = 0;
	this->lineLocation = -1;
	this->charLocation = -2;

	GlyphCreater glyphCreater;
	Glyph* currentLine;
	Long lineOrder;
	Long charIndex;
	char charArray[2];
	charArray[0] = nChar;
	charArray[1] = '\0';

	//���õǾ����� ���õ� ������ �����. 
	CommandCreator commandCreator(this->notepannel);
	Command* command = 0;
	if (this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		command->Execute();
		this->notepannel->macroCommand->Add(command);
	}

	if (nChar != VK_RETURN) { //����Ű�� �ƴϸ� ���ڿ� �´� ���ڸ� �����. 
		this->character = glyphCreater.Create(charArray);
	}
	else {
		this->character = 0;
	}
	//������ ���� ��ġ�� �д´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//������ġ�� ���� ���� ��ġ�� ����Ѵ�. 
	this->notepannel->paper->GetLocation(lineOrder, charIndex, &this->lineLocation, &this->charLocation);
}

/*
* �Լ���Ī:~OnCharCommand
* ���:�Ҹ���
*/
OnCharCommand::~OnCharCommand() {
	delete this->character;
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����Ѵ�.
*/
void OnCharCommand::Execute() {
	Glyph* currentLine = NULL;
	Glyph* clone = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//������ �������� �����Ѵ�.
	this->notepannel->paper->MergeAllDummyLines();

	//���� ��ġ�� ������ġ�� ã�´�. 
	this->notepannel->paper->MoveToLocation(this->lineLocation, this->charLocation, &lineOrder, &charIndex);
	
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	if (this->character != 0) {//����Ű�� �ƴϸ�
		//���� ��ġ�� ���ڸ� �Է��Ѵ�. 
		currentLine->Add(this->character->Clone());
	}
	else { //����Ű��
		//���� ���� Ŭ���� �����. 
		clone = currentLine->Clone();
		//Ŭ���� �� �������� ���� ��ġ���� �����. 
		clone->Remove(0, charIndex);
		//Ŭ���� �����ٷ� �ִ´�. 
		this->notepannel->paper->Add(lineOrder + 1, clone);
		//���� ���� ���� ��ġ���� ���� ������ �����. 
		currentLine->Remove(charIndex + 1, currentLine->GetLength() - 1);
		//���̿��� �����ٷ� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Move(lineOrder + 1);
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		//���� �ٿ��� �� ������ �̵��Ѵ�.
		currentLine->First();
	}
}

/*
* �Լ���Ī:UnExecute
* ���:Ŀ��带 ��������Ѵ�.
*/
void OnCharCommand::UnExecute() {
	Glyph* currentLine = NULL;
	Glyph* nextLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long charOrder = -1;

	//������ �������� �����Ѵ�.
	this->notepannel->paper->MergeAllDummyLines();

	//���� ��ġ�� ������ġ�� ã�´�. 
	this->notepannel->paper->MoveToLocation(this->lineLocation, this->charLocation, &lineOrder, &charIndex);
	
	//���� ������ ������ �Է��Ѵ�.
	charOrder = charIndex + 1;

	currentLine = this->notepannel->paper->GetAt(lineOrder);
	if (this->character != 0) {//����Ű�� �ƴϸ�
		//�Է��� ��ġ�� ���ڸ� �����. 
		currentLine->Remove(charOrder);
	}
	else { //����Ű��
		//�Է��� ��ġ�� ���� �����´�.
		//�Է��� ��ġ ������ ���� �����´�.
		nextLine = this->notepannel->paper->GetAt(lineOrder + 1);
		//�Է��� ��ġ�� �ٿ� ���� ���� ���Ѵ�.
		currentLine->Add(nextLine, charOrder);
		//���� ���� �����.
		this->notepannel->paper->Remove(lineOrder + 1);
		//������ġ�� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Move(lineOrder);
		currentLine->Move(charIndex);
	}


	if (this->notepannel->isSelected == TRUE) {//������ ���õǾ����� ���õ� ������ �����Ѵ�. 
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}
	else { //�������� �ʾҾ ����Ʈ�� �����������ش�.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}

}