//FindCommand.cpp
/*
* ���ϸ�Ī:FindCommand.cpp
* ���:�ݱ� Ŀ���
* �ۼ���:������
* �ۼ�����:20220826
*/
#include "FindCommand.h"
#include "Notepannel.h"
#include "Finder.h"
#include "ResultFound.h"
#include "Select.h"
#include "Paper.h"
#include <afxdlgs.h>
#include<string>
using namespace std;

/*
* �Լ���Ī:FindCommand
* ���:������
*/
FindCommand::FindCommand(Notepannel* notepannel) : notepannel(notepannel) {
}

/*
* �Լ���Ī:~FindCommand
* ���:�Ҹ���
*/
FindCommand::~FindCommand() {
}

/*
* �Լ���Ī:Execute
* ���:�ݱ� Ŀ��带 �����ϴ�
*/
void FindCommand::Execute() {
	CFindReplaceDialog* cFindDialog = NULL;
	Glyph* clone;
	string stringWritten = this->notepannel->resultFound->stringToFind;
	string stringSelected = "";
	//string test = "�׽�Ʈ ����"; //���߿� ã��Ŭ������ �������� ��ü 
	Long frontLineOrder = this->notepannel->select->frontLineOrder;
	Long frontCharIndex = this->notepannel->select->frontXIndex;
	Long endLineOrder = this->notepannel->select->endLineOrder;
	Long endCharIndex = this->notepannel->select->endXIndex;

	//ã�� �����ȭ���ڸ� ����. 
	cFindDialog = new CFindReplaceDialog;
	
	if (this->notepannel->isSelected == FALSE) { //���̿��� ���õǾ����� ������
		//����� ã�� ������ ã�� ��ȭ������ ã�³��뿡 ���´�. 
		//cFindDialog->Create(TRUE, test.c_str(), NULL, FR_DOWN, this->notepannel);
		cFindDialog->Create(TRUE, stringWritten.c_str(), NULL, FR_DOWN, this->notepannel);
	}
	else { //���̿��� ���õǾ� ������
		//���õ� ������ ã���ȭ������ ã�³��뿡 ���´�. 
		clone = this->notepannel->paper->Clone(frontLineOrder, frontCharIndex, endLineOrder, endCharIndex);
		clone->MergeAllDummyLines();
		stringSelected = clone->GetString();
		delete clone;
		cFindDialog->Create(TRUE, stringSelected.c_str(), NULL, FR_DOWN, this->notepannel);
	}
}