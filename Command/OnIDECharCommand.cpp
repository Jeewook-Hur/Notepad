//OnIDECharCommand.cpp
/*
* ���ϸ�Ī:OnIDECharCommand.cpp
* ���:�������Ʈ �Է��� �ϴ� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/11/29
*/
#include "OnIDECharCommand.h"
#include "Notepannel.h"
#include "Select.h"

#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"

/*
* �Լ���Ī:OnIDECharCommand
* ���:������
*/
OnIDECharCommand::OnIDECharCommand(Notepannel* notepannel, WPARAM wParam, LPARAM lParam) : notepannel(notepannel) {
	this->character = 0;
	this->lineLocation = -1;
	this->charLocation = -2;
	
	GlyphCreater glyphCreater;
	Glyph* currentLine;
	Long lineOrder;
	Long charIndex;
	char letter[3];
	//�Էµ� ���ڸ� �д´�.
	letter[0] = HIBYTE(wParam);
	letter[1] = LOBYTE(wParam);
	letter[2] = '\0';

	//�Է��� ���ڿ� �´� �������Ʈ ���ڸ� �����. 
	this->character = glyphCreater.Create(letter);
	//������ ���� ��ġ�� �д´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//������ġ�� ���� ���� ��ġ�� ����Ѵ�. 
	this->notepannel->paper->GetLocation(lineOrder, charIndex, &this->lineLocation, &this->charLocation);
}

/*
* �Լ���Ī:~OnIDECharCommand
* ���:�Ҹ���
*/
OnIDECharCommand::~OnIDECharCommand() {
	delete this->character;
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����Ѵ�.
*/
void OnIDECharCommand::Execute() {
	Glyph* currentLine = NULL;
	Glyph* clone = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//������ �������� �����Ѵ�.
	this->notepannel->paper->MergeAllDummyLines();

	//���� ��ġ�� ������ġ�� ã�´�. 
	this->notepannel->paper->MoveToLocation(this->lineLocation, this->charLocation, &lineOrder, &charIndex);

	currentLine = this->notepannel->paper->GetAt(lineOrder);

	//���� ��ġ�� ���ڸ� �Է��Ѵ�. 
	currentLine->Add(this->character->Clone());
	
}

/*
* �Լ���Ī:UnExecute
* ���:Ŀ��带 ��������Ѵ�.
*/
void OnIDECharCommand::UnExecute() {
	Glyph* currentLine = NULL;
	Glyph* nextLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;

	//������ �������� �����Ѵ�.
	this->notepannel->paper->MergeAllDummyLines();

	//���� ��ġ�� ������ġ�� ã�´�. 
	this->notepannel->paper->MoveToLocation(this->lineLocation, this->charLocation, &lineOrder, &charIndex);

	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//�Է��� ��ġ�� ���ڸ� �����. 
	currentLine->Remove(charIndex + 1);

	
	if (this->notepannel->isSelected == TRUE) {//������ ���õǾ����� ���õ� ������ �����Ѵ�. 
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}
	else { //�������� �ʾҾ ����Ʈ�� �����������ش�.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);
	}
	
}