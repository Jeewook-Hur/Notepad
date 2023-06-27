//CopyCommand.cpp
/*
* 파일명칭:CopyCommand.cpp
* 기능:복사를 하는 커멘드 
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#include "CopyCommand.h"
#include "Notepannel.h"
#include "Select.h"
#include "Clipboard.h"

#include "GlyphCreater.h"
#include "Paper.h"
#include "Line.h"

/*
* 함수명칭:CopyCommand
* 기능:생성자
*/
CopyCommand::CopyCommand(Notepannel* notepannel) :notepannel(notepannel) {
}

/*
* 함수명칭:~CopyCommand
* 기능:소멸자
*/
CopyCommand::~CopyCommand() {
}

/*
* 함수명칭:Execute
* 기능:복사하기 커멘드를 실행한다. 
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

	//(수정 코드)종이의 선택된 범위의 복사본을 만든다.
	paperCopy = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);

#if 0
	//이 코드의 문제점은 빈 종이에 첫번째 줄로 더미줄이 들어갈 경우 문제가 발생한다. 
	//빈 종이를 만든다.
	paperCopy = glyphCreater.Create("");
	index = frontLineOrder;
	while (index <= endLineOrder) { //선택한 줄의 시작줄부터 끝줄까지 반복한다. 
		currentLine = this->notepannel->paper->GetAt(index);
		cloneLine = currentLine->Clone();
		paperCopy->Add(cloneLine);
		index++;
	}

	//종이의 마지막 줄에서 선택된 위치부터 끝까지 지운다.
	lineOrder = paperCopy->Last();
	currentLine = paperCopy->GetAt(lineOrder);
	lineLength = currentLine->GetLength();
	if (lineLength > 0 && endCharIndex < lineLength - 1) {
		currentLine->Remove(endCharIndex + 1, lineLength - 1);
	}
	//종이의 맨앞 줄에서 맨앞에서 선택된 위치까지 지운다. 
	if (frontCharIndex > -1) {
		lineOrder = paperCopy->First();
		currentLine = paperCopy->GetAt(lineOrder);
		currentLine->Remove(0, frontCharIndex);
	}
#endif
	//더미줄을 병합한다. 
	paperCopy->MergeAllDummyLines();

	stringToCopy = paperCopy->GetExactString();
	delete paperCopy;

	this->notepannel->clipboard->Copy(stringToCopy);
}