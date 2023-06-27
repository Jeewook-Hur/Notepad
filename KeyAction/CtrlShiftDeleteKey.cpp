//CtrlShiftDeleteKey.cpp
/*
* ���ϸ�Ī:CtrlShiftDeleteKey.cpp
* ���:��Ʈ�� ����Ʈ ����Ʈ Ű�� ���������� ����
* �ۼ���:������
* �ۼ�����:2022/11/15
*/
#include "CtrlShiftDeleteKey.h"
#include "Notepannel.h"
#include "Notepad.h"
#include "Caret.h"
#include "Document.h"
#include "Select.h"
#include "Paper.h"
#include "Line.h"
#include "SelectDelete.h"
#include "CommandCreator.h"
#include "Command.h"
#include "MacroCommand.h"
#include "resource.h"

/*
* �Լ���Ī:CtrlShiftDeleteKey
* ���:������
*/
CtrlShiftDeleteKey::CtrlShiftDeleteKey(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~CtrlShiftDeleteKey
* ���:�Ҹ���
*/
CtrlShiftDeleteKey::~CtrlShiftDeleteKey() {
}

/*
* �Լ���Ī:OnKeyDown
* ���:Ű�� ���������� �̺�Ʈ�� �����Ѵ�.
*/
void CtrlShiftDeleteKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* currentLine = NULL;
	Glyph* tempLine = NULL;
	Glyph* character = NULL;
	Long paperLength = 0;
	Long lineOrder = -1;
	Long lineLength = -1;
	Long charIndex = -2;
	Long tempOrder = -2;
	Long tempLength = -1;
	Long order = 0;
	Long i = 0;

	paperLength = this->notepannel->paper->GetLength();
	//���̿��� ���� ���� ��ġ�� ã�´�.
	lineOrder = this->notepannel->paper->GetCurrent();
	//���̿��� ���� ���� �����´�.
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	//���� �ٿ��� ���� �ܾ� ��ġ�� �����´�.
	charIndex = currentLine->GetCurrent();
	lineLength = currentLine->GetLength();


	CommandCreator commandCreator(this->notepannel);
	Command* command = NULL;
	if (!(lineOrder >= paperLength - 1 && charIndex >= lineLength - 1) || this->notepannel->isSelected == TRUE) {
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		if (command != NULL) {
			command->Execute();
			this->notepannel->macroCommand->Add(command, 1);
		}
	}
#if 0
	//�����ϱ⸦ �Ҵ������Ѵ�.
	delete this->notepannel->select;
	//������ġ���� ���� �ܾ���� �����Ѵ�.
	this->notepannel->select = new Select(notepannel, charIndex, lineOrder, charIndex, lineOrder);
	if (charIndex < lineLength - 1) {//���� �ܾ� ��ġ�� �� �������� �ƴϸ�
		//���� �ܾ�� �̵��Ѵ�.
		charIndex = currentLine->Last();
		//���� �ܾ���� �����Ѵ�. 
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	}
	else if (charIndex >= lineLength - 1 && lineOrder < paperLength - 1) {//���� �ܾ� ��ġ�� �� �������̰� ���� ���� �� �������� �ƴϸ�
		//���� �ٷ� �̵��Ѵ�.
		lineOrder = this->notepannel->paper->Next();
		currentLine = this->notepannel->paper->GetAt(lineOrder);
		//���� ���� ������ �̵��Ѵ�. 
		charIndex = currentLine->First();
		//���� ���� ������ �����Ѵ�. 
		this->notepannel->select->MoveCurrent(charIndex, lineOrder);
	}
#endif

	//������ ����Ǿ����� ǥ���Ѵ�. 
	this->notepannel->hasChanged = TRUE;
	//�������� ������ �����Ѵ�.
	CString windowTitle;
	windowTitle.Format("*%s - Windows �޸���", this->notepannel->document->GetName().c_str());
	this->notepannel->notepad->SetWindowText(windowTitle);

	//������ ������ �����. 
	SelectDelete selectDelete(this->notepannel);
	selectDelete.OnKeyDown(nChar, nRepCnt, nFlags);
}