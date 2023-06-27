//ReplaceCommand.cpp
/*
* ���ϸ�Ī:ReplaceCommand.cpp
* ���:�ݱ� Ŀ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#include "ReplaceCommand.h"
#include "Notepannel.h"
#include "Paper.h"
#include "Select.h"
#include "Finder.h"
#include "Replacer.h"
#include <afxdlgs.h>
#include<string>
using namespace std;

/*
* �Լ���Ī:ReplaceCommand
* ���:������
*/
ReplaceCommand::ReplaceCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* �Լ���Ī:~ReplaceCommand
* ���:�Ҹ���
*/
ReplaceCommand::~ReplaceCommand() {
}

/*
* �Լ���Ī:Execute
* ���:ã�� Ŀ��带 �����ϴ�
*/
void ReplaceCommand::Execute() {
	CFindReplaceDialog* cFindDialog = NULL;
	Glyph* clone;
	string stringWritten = this->notepannel->finder->find;
	string stringSelected = "";
	string stringReplace = this->notepannel->replacer->replace;
	//string test = "�׽�Ʈ ����"; //���߿� ã��Ŭ������ �������� ��ü 
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//ã��ٲٱ� �����ȭ���ڸ� ����. 
	cFindDialog = new CFindReplaceDialog;

	if (this->notepannel->isSelected == FALSE) { //���̿��� ���õǾ����� ������
		//����� ã�� ������ ã�� ��ȭ������ ã�³��뿡 ���´�. 
		//cFindDialog->Create(TRUE, test.c_str(), NULL, FR_DOWN, this->notepannel);
		cFindDialog->Create(FALSE, stringWritten.c_str(), stringReplace.c_str(), FR_DOWN, this->notepannel);
	}
	else { //���̿��� ���õǾ� ������
		//���õ� ������ ã���ȭ������ ã�³��뿡 ���´�. 
		clone = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
		clone->MergeAllDummyLines();
		stringSelected = clone->GetString();
		delete clone;
		cFindDialog->Create(FALSE, stringSelected.c_str(), stringReplace.c_str(), FR_DOWN, this->notepannel);
	}
}