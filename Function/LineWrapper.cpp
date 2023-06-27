//LineWrapper.cpp
/*
* ���ϸ�Ī:LineWrapper.cpp
* ���:�Է¹��� ���̸� �ڵ������ϰ� ��ġ�� �����ϴ� �Լ��� ���
* �ۼ���:������
* �ۼ�����:2022/12/19
*/
#include "LineWrapper.h"
#include "Notepannel.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "Select.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include<string>
using namespace std;

/*
* �Լ���Ī:LineWrapper
* ���:������
*/
LineWrapper::LineWrapper(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~LineWrapper
* ���:�Ҹ���
*/
LineWrapper::~LineWrapper() {
}

/*
* �Լ���Ī:Wrap
* ���:�Է¹��� ���̸� �Է¹��� ���� ������ �����Ѵ�. 
*/
void LineWrapper::Warp(Glyph* paper, int width) {
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
	Long widthToCut = width;
	Long index = -2;
	Long tempIndex = -2;
	Long i = 0;
	char checkTab = '\0';

	Long frontLineLocation;
	Long frontCharLocation;
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineLocation;
	Long endCharLocation;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//���̿��� ���� ���� ��ġ�� ���� �ٿ����� ���� ��ġ�� ����Ѵ�.
	lineOrder = paper->GetCurrent();
	currentLineRemember = paper->GetAt(lineOrder);
	charIndex = currentLineRemember->GetCurrent();
	currentLineOrder = lineOrder;
	currentCharIndex = charIndex;
	paper->GetLocation(currentLineOrder, currentCharIndex, &lineLocation, &charLocation);
	if (this->notepannel->isSelected == TRUE) { //���õǾ�����
		paper->GetLocation(frontLineOrder, frontCharIndex, &frontLineLocation, &frontCharLocation);
		paper->GetLocation(endLineOrder, endCharIndex, &endLineLocation, &endCharLocation);
	}
	//���̿��� ������ ���� ����Ѵ�.
	lastOrder = paper->Last();
	lastPage = paper->GetAt(lastOrder);
	//���̿��� ó�� �ٷ� �̵��Ѵ�.
	lineOrder = paper->First();
	currentLine = paper->GetAt(lineOrder);
	
	paperLength = paper->GetLength();
	while (i < paperLength) {//������ ���̸�ŭ �ݺ��Ѵ�.
		//���� ���� ���̸� ���Ѵ�.
		lineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine);
		//���� ���� ���̰� â�� ���̺��� ũ�� �ݺ��Ѵ�
		while (lineWidth > widthToCut) {
			//���� �ٿ��� ������ �ʺ�� ����� ���� �ܾ ã�´�.
			index = this->notepannel->characterMatrix->FindNearWidthPositionDown(currentLine, widthToCut); //letterDown���� �ٲ۴�.
			
			if (index >= 0) { //���� �ܾ ������
				//��ġ�� �ܾ � �ڷ������� �����Ѵ�. 
				character = currentLine->GetAt(index);
				characterString = character->GetString();
				characterLetter = characterString[0];

				tempIndex = index;
				if (dynamic_cast<SingleByteCharacter*>(character)
					&& (characterLetter == 34 || characterLetter == 39 || (characterLetter >= 65 && characterLetter <= 90) || (characterLetter >= 97 && characterLetter <= 122))) { //��ġ�� �ܾ �����̸�
					//���� ��ġ�� �ܾ�� �����Ѵ�. 
					index = currentLine->Move(index);
					index = currentLine->PreviousWord();

					if (index > -1) {
						checkTab = (currentLine->GetAt(index)->GetExactString())[0];
					}

					if (index <= -1) { //��ġ�� �� ���̸� 
						//���� �ٿ��� ������ �ʺ�� ����� ��ġ�� ã�´�.
						index = this->notepannel->characterMatrix->FindNearWidthPositionDown(currentLine, widthToCut);
					}
					else if (checkTab != '\0' && checkTab == '\t') {
						index = tempIndex;
					}
				}
			}
			else if (index < 0) {
				//���� �ܾ ������ �� �ܾ �����ϰ� �ܾ ������� ������.
				index = 0;
			}
			//���� ��ġ�� �������� �����ٷ� ������. 
			dummyLineOrder = paper->SplitDummyLine(lineOrder, index);
			//���� �����ٷ� �̵��Ѵ�.
			lineOrder = dummyLineOrder;
			currentLine = paper->GetAt(lineOrder);
			//���� ���� ���̸� ���Ѵ�. 
			lineWidth = this->notepannel->characterMatrix->GetLineWidth(currentLine);

		}
		//���� �ٷ� �̵��Ѵ�.
		lineOrder = paper->Next();
		currentLine = paper->GetAt(lineOrder);
		i++;
	}
	//����� ��ġ�� �̵��Ѵ�. 
	paper->MoveToLocation(lineLocation, charLocation, &currentLineOrder, &currentCharIndex);
	currentLineOrder = paper->Move(currentLineOrder);
	currentLine = paper->GetAt(currentLineOrder);
	currentLine->Move(currentCharIndex);
	if (this->notepannel->isSelected == TRUE) { //���õǾ�����
		paper->MoveToLocation(frontLineLocation, frontCharLocation, &frontLineOrder, &frontCharIndex);
		paper->MoveToLocation(endLineLocation, endCharLocation, &endLineOrder, &endCharIndex);

		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}
}

/*
* �Լ���Ī:UnWrap
* ���:�Է¹��� ���̸� ��������Ѵ�.
*/
void LineWrapper::UnWarp(Glyph* paper) {
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
	lineOrder = paper->GetCurrent();
	currentLineRemember = paper->GetAt(lineOrder);
	charIndex = currentLineRemember->GetCurrent();
	currentLineOrder = lineOrder;
	currentCharIndex = charIndex;
	paper->GetLocation(currentLineOrder, currentCharIndex, &lineLocation, &charLocation);
	if (this->notepannel->isSelected == TRUE) { //���õǾ�����
		paper->GetLocation(frontLineOrder, frontCharIndex, &frontLineLocation, &frontCharLocation);
		paper->GetLocation(endLineOrder, endCharIndex, &endLineLocation, &endCharLocation);
	}
	//���̿��� ��� �������� ���� �ٿ� ��ģ��.
	paper->MergeAllDummyLines();

	//����� ��ġ�� �̵��Ѵ�. 
	paper->MoveToLocation(lineLocation, charLocation, &currentLineOrder, &currentCharIndex);
	currentLineOrder = paper->Move(currentLineOrder);
	currentLine = paper->GetAt(currentLineOrder);
	currentLine->Move(currentCharIndex);
	if (this->notepannel->isSelected == TRUE) { //���õǾ�����
		paper->MoveToLocation(frontLineLocation, frontCharLocation, &frontLineOrder, &frontCharIndex);
		paper->MoveToLocation(endLineLocation, endCharLocation, &endLineOrder, &endCharIndex);

		delete this->notepannel->select;
		this->notepannel->select = new Select(this->notepannel, frontCharIndex, frontLineOrder, endCharIndex, endLineOrder);
	}





}