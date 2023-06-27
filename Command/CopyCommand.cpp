//CopyCommand.cpp
/*
* ���ϸ�Ī:CopyCommand.cpp
* ���:���縦 �ϴ� Ŀ��� 
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "CopyCommand.h"
#include "Notepannel.h"
#include "Select.h"
#include "Clipboard.h"

#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"

/*
* �Լ���Ī:CopyCommand
* ���:������
*/
CopyCommand::CopyCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* �Լ���Ī:~CopyCommand
* ���:�Ҹ���
*/
CopyCommand::~CopyCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�����ϱ� Ŀ��带 �����Ѵ�. 
*/
void CopyCommand::Execute() {
	GlyphCreater glyphCreater;
	Glyph* paperCopy = NULL;
	Glyph* currentLine = NULL;
	Glyph* cloneLine = NULL;
	int lineOrder = -1;
	int lineLength = -1;
	int frontLineOrder = this->notepannel->select->frontLineOrder;
	int frontCharIndex = this->notepannel->select->frontXIndex;
	int endLineOrder = this->notepannel->select->endLineOrder;
	int endCharIndex = this->notepannel->select->endXIndex;
	int index = -1;
	string stringToCopy = "";

	//(���� �ڵ�)������ ���õ� ������ ���纻�� �����.
	paperCopy = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);

#if 0
	//�� �ڵ��� �������� �� ���̿� ù��° �ٷ� �������� �� ��� ������ �߻��Ѵ�. 
	//�� ���̸� �����.
	paperCopy = glyphCreater.Create("");
	index = frontLineOrder;
	while (index <= endLineOrder) { //������ ���� �����ٺ��� ���ٱ��� �ݺ��Ѵ�. 
		currentLine = this->notepannel->paper->GetAt(index);
		cloneLine = currentLine->Clone();
		paperCopy->Add(cloneLine);
		index++;
	}

	//������ ������ �ٿ��� ���õ� ��ġ���� ������ �����.
	lineOrder = paperCopy->Last();
	currentLine = paperCopy->GetAt(lineOrder);
	lineLength = currentLine->GetLength();
	if (lineLength > 0 && endCharIndex < lineLength - 1) {
		currentLine->Remove(endCharIndex + 1, lineLength - 1);
	}
	//������ �Ǿ� �ٿ��� �Ǿտ��� ���õ� ��ġ���� �����. 
	if (frontCharIndex > -1) {
		lineOrder = paperCopy->First();
		currentLine = paperCopy->GetAt(lineOrder);
		currentLine->Remove(0, frontCharIndex);
	}
#endif
	//�������� �����Ѵ�. 
	paperCopy->MergeAllDummyLines();

	stringToCopy = paperCopy->GetExactString();
	delete paperCopy;

	this->notepannel->clipboard->Copy(stringToCopy);
}