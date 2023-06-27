//LineWrapCommand.cpp
/*
* ���ϸ�Ī:LineWrapCommand.cpp
* ���:�ڵ� �� �ٲ� �޴�
* �ۼ���:������
* �ۼ�����:20220920
*/
#include "LineWrapCommand.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "Select.h"
#include "LineWrapper.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include<string>
using namespace std;



/*
* �Լ���Ī:LineWrapCommand
* ���:������
*/
LineWrapCommand::LineWrapCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:LineWrapCommand
* ���:�Ҹ���
*/
LineWrapCommand::~LineWrapCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�ڵ� �� �ٲ� Ŀ��带 �����Ѵ�.
*/
void LineWrapCommand::Execute() {
	Long widthToCut = -1;


#if 0
	Glyph* currentLine = NULL;
	Glyph* currentLineRemember = NULL;
	Glyph* lastPage = NULL;
	Glyph* character = NULL;
	string characterString;
	char characterLetter;
	Long currentLineOrder = -1;
	Long charIndex = -2;
	Long currentCharIndex = -2;
	Long lineLocation;
	Long charLocation;
	Long lastOrder = -1;
	Long lineOrder = -1;
	Long lineLength = -1;
	Long lineWidth = -1;
	Long paperLength = -1;
	Long dummyLineOrder = -1;
	Long widthToCut = -1;
	Long index = -2;
	Long i = 0;

	Long frontLineLocation;
	Long frontCharLocation;
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineLocation;
	Long endCharLocation;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//���̿��� ���� ���� ��ġ�� ���� �ٿ����� ���� ��ġ�� ����Ѵ�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLineRemember = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLineRemember->GetCurrent();
	currentLineOrder = lineOrder;
	currentCharIndex = charIndex;
	this->notepannel->paper->GetLocation(currentLineOrder, currentCharIndex, &lineLocation, &charLocation);
	if (this->notepannel->isSelected == TRUE) { //���õǾ�����
		this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &frontLineLocation, &frontCharLocation);
		this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &endLineLocation, &endCharLocation);
	}
	//���̿��� ������ ���� ����Ѵ�.
	lastOrder = this->notepannel->paper->Last();
	lastPage = this->notepannel->paper->GetAt(lastOrder);
	//���̿��� ó�� �ٷ� �̵��Ѵ�.
	lineOrder = this->notepannel->paper->First();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//�������� �ʺ� ���Ѵ�.
	widthToCut = this->notepannel->clientMatrix->width;
	//â�� ũ�Ⱑ �ʹ� �������� ����� �ּ�ġ�� �غ��Ѵ�. 
	if (widthToCut < 120) {
		widthToCut = 120;
	}
	paperLength = this->notepannel->paper->GetLength();
	while (i < paperLength) {//������ ���̸�ŭ �ݺ��Ѵ�.
		//���� ���� ���̸� ���Ѵ�.
		lineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine);
		//���� ���� ���̰� â�� ���̺��� ũ�� �ݺ��Ѵ�
		while (lineWidth > widthToCut) {
			//���� �ٿ��� ������ �ʺ�� ����� ���� �ܾ ã�´�.
			index = this->notepannel->characterMatrix->FindNearWidthPositionDown(currentLine, widthToCut); //letterDown���� �ٲ۴�.
			//��ġ�� �ܾ � �ڷ������� �����Ѵ�. 
			character = currentLine->GetAt(index);
			characterString = character->GetString();
			characterLetter = characterString[0];
			if (dynamic_cast<SingleByteCharacter*>(character)
				&& (characterLetter == 34 || characterLetter == 39 || (characterLetter >= 65 && characterLetter <= 90) || (characterLetter >= 97 && characterLetter <= 122))) { //��ġ�� �ܾ �����̸�
				//���� ��ġ�� �ܾ�� �����Ѵ�. 
				index = currentLine->Move(index);
				index = currentLine->PreviousWord();
				if (index <= -1) { //��ġ�� �� ���̸� 
					//���� �ٿ��� ������ �ʺ�� ����� ��ġ�� ã�´�.
					index = this->notepannel->characterMatrix->FindNearWidthPositionDown(currentLine, widthToCut);
				}
			}
			//���� ��ġ�� �������� �����ٷ� ������. 
			dummyLineOrder = this->notepannel->paper->SplitDummyLine(lineOrder, index);
			//���� �����ٷ� �̵��Ѵ�.
			lineOrder = dummyLineOrder;
			currentLine = this->notepannel->paper->GetAt(lineOrder);
			//���� ���� ���̸� ���Ѵ�. 
			lineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine);

		}
		//���� �ٷ� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		i++;
	}
	//����� ��ġ�� �̵��Ѵ�. 
	this->notepannel->paper->MoveToLocation(lineLocation, charLocation, &currentLineOrder, &currentCharIndex);
	currentLineOrder = this->notepannel->paper->Move(currentLineOrder);
	currentLine = this->notepannel->paper->GetAt(currentLineOrder);
	currentLine->Move(currentCharIndex);
	if (this->notepannel->isSelected == TRUE) { //���õǾ�����
		this->notepannel->paper->MoveToLocation(frontLineLocation, frontCharLocation, &frontLineOrder, &frontCharIndex);
		this->notepannel->paper->MoveToLocation(endLineLocation, endCharLocation, &endLineOrder, &endCharIndex);

		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}
#endif

	LineWrapper lineWrapper(this->notepannel);

	//�������� �ʺ� ���Ѵ�.
	widthToCut = this->notepannel->clientMatrix->width;
	//â�� ũ�Ⱑ �ʹ� �������� ����� �ּ�ġ�� �غ��Ѵ�. 
	if (widthToCut < 80) {
		widthToCut = 80;
	}
	
	lineWrapper.Warp(this->notepannel->paper, widthToCut);

	if (this->notepannel->isCalledFromMenu == TRUE) { //�޴����� ȣ������ ��� //���� �� ������Ʈ�� �ؾ��� ��
		//������ �� ������ �̵��Ѵ�
		this->notepannel->paper->First();
		this->notepannel->paper->GetAt(0)->First();
		//����ó�������� ǥ���Ѵ�. //LineWrapCommand �� ����
		this->notepannel->isLineWraping = TRUE;
		//�������� ������ ������Ʈ�� ������ ǥ���Ѵ�. 
		this->notepannel->documentUploaded = TRUE;
		//��ũ�� �ڵ������� �ʿ����� ǥ���Ѵ�.
		this->notepannel->clientMoveCheck = TRUE;
		//�޸����� ������Ʈ�� ȣ���Ѵ�.
		this->notepannel->Notify();
		//���� Ŭ������ �ʱ�ȭ�Ѵ�.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);

		//Ŭ���̾�Ʈ�� ������ġ�� ������ġ�� �°� �̵���Ų��. 
		//this->notepannel->clientLocation->Move(0, 0);
		//this->notepannel->scroll->Move(0, 0);
		//Ŭ���̾�Ʈ ȭ���� �����Ѵ�.
		this->notepannel->Invalidate(TRUE);
		//ĳ���� ǥ���Ѵ�. 
		this->notepannel->caret->ShowCaret();
		this->notepannel->isCalledFromMenu = FALSE;
	}

	//��ũ���� ��Ȱ��ȭ �Ѵ�. 
	this->notepannel->EnableScrollBar(SB_HORZ, ESB_DISABLE_BOTH);


	//����ó���� �������� ǥ���Ѵ�.
	this->notepannel->isLineWraping = FALSE;
}

/*
* �Լ���Ī:UnExecute
* ���:�ڵ� �� �ٲ� Ŀ��带 �����Ѵ�.
*/
void LineWrapCommand::UnExecute() {


#if 0
	Glyph* currentLine = NULL;
	Glyph* currentLineRemember = NULL;

	Long lineOrder = -1;
	Long currentIndex = -2;
	
	Long charIndex;
	Long currentLineOrder;
	Long currentCharIndex;
	Long lineLocation;
	Long charLocation;

	Long frontLineLocation;
	Long frontCharLocation;
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineLocation;
	Long endCharLocation;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;
	//���̿��� ���� ���� ��ġ�� ���� �ٿ����� ���� ��ġ�� ����Ѵ�.
	lineOrder = this->notepannel->paper->GetCurrent();
	currentLineRemember = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLineRemember->GetCurrent();
	currentLineOrder = lineOrder;
	currentCharIndex = charIndex;
	this->notepannel->paper->GetLocation(currentLineOrder, currentCharIndex, &lineLocation, &charLocation);
	if (this->notepannel->isSelected == TRUE) { //���õǾ�����
		this->notepannel->paper->GetLocation(frontLineOrder, frontCharIndex, &frontLineLocation, &frontCharLocation);
		this->notepannel->paper->GetLocation(endLineOrder, endCharIndex, &endLineLocation, &endCharLocation);
	}
	//���̿��� ��� �������� ���� �ٿ� ��ģ��.
	this->notepannel->paper->MergeAllDummyLines();

	//����� ��ġ�� �̵��Ѵ�. 
	this->notepannel->paper->MoveToLocation(lineLocation, charLocation, &currentLineOrder, &currentCharIndex);
	currentLineOrder = this->notepannel->paper->Move(currentLineOrder);
	currentLine = this->notepannel->paper->GetAt(currentLineOrder);
	currentLine->Move(currentCharIndex);
	if (this->notepannel->isSelected == TRUE) { //���õǾ�����
		this->notepannel->paper->MoveToLocation(frontLineLocation, frontCharLocation, &frontLineOrder, &frontCharIndex);
		this->notepannel->paper->MoveToLocation(endLineLocation, endCharLocation, &endLineOrder, &endCharIndex);

		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}

#endif

	LineWrapper lineWrapper(this->notepannel);

	lineWrapper.UnWarp(this->notepannel->paper);

	if (this->notepannel->isCalledFromMenu == TRUE) { //�޴����� ȣ������ ��� //���� �� ������Ʈ�� �ؾ��� ��
		//������ �� ������ �̵��Ѵ�
		this->notepannel->paper->First();
		this->notepannel->paper->GetAt(0)->First();
		//����ó�������� ǥ���Ѵ�. //LineWrapCommand �� ����
		this->notepannel->isLineWraping = TRUE;
		//�������� ������ ������Ʈ�� ������ ǥ���Ѵ�. 
		this->notepannel->documentUploaded = TRUE;
		//��ũ�� �ڵ������� �ʿ����� ǥ���Ѵ�.
		this->notepannel->clientMoveCheck = TRUE;
		//�޸����� ������Ʈ�� ȣ���Ѵ�.
		this->notepannel->Notify();
		//���� Ŭ������ �ʱ�ȭ�Ѵ�.
		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel);

		//Ŭ���̾�Ʈ ȭ���� �����Ѵ�.
		this->notepannel->Invalidate(TRUE);
		//ĳ���� ǥ���Ѵ�. 
		this->notepannel->caret->ShowCaret();

		this->notepannel->isCalledFromMenu = FALSE;
	}

	//��ũ���� Ȱ��ȭ �Ѵ�. 
	this->notepannel->EnableScrollBar(SB_HORZ, ESB_ENABLE_BOTH);

	//����ó���� �������� ǥ���Ѵ�.
	this->notepannel->isLineWraping = FALSE;
}