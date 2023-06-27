//CommandCreator.cpp
/*
* ���ϸ�Ī:CommandCreator.h
* ���:Ŀ��� �Լ��� ����� �Լ�
* �ۼ���:������
* �ۼ�����:20220826
*/
#include "CommandCreator.h"
#include "resource.h"
#include "Notepannel.h"

#include "FontCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"
#include "LoadCommand.h"
#include "CloseCommand.h"
#include "LineWrapCommand.h"
#include "ZoomInCommand.h"
#include "ZoomOutCommand.h"
#include "RestoreDefaultZoomCommand.h"
#include "NewCommand.h"
#include "SelectAllCommand.h"
#include "CopyCommand.h"
#include "CutCommand.h"
#include "DeleteCommand.h"
#include "PasteCommand.h"
#include "OnCharCommand.h"
#include "UndoCommand.h"
#include "OnIDECharCommand.h"
#include "BackspaceCommand.h"
#include "FindCommand.h"
#include "ReplaceCommand.h"
#include "PageSettingCommand.h"
#include "PreviewCommand.h"
#include "PrintCommand.h"
#include "StatusBarCommand.h"
#include "DateCommand.h"
#include "MoveToLineCommand.h"
#include "AboutNotepadCommand.h"
#include "NotepadHelpCommand.h"

#include "Paper.h"
#include "Line.h"

/*
* �Լ���Ī:CommandCreator
* ���:������
*/
CommandCreator::CommandCreator(Notepannel* notepannel)
	:notepannel(notepannel) {
}

/*
* �Լ���Ī:~CommandCreator
* ���:�Ҹ���
*/
CommandCreator::~CommandCreator() {
}

/*
* �Լ���Ī:Create
* ���:�Է¹��� ��ɿ� �°� �Լ��� �����Ѵ�.
*/
Command* CommandCreator::Create(int id) {
	Command* command = 0;

	if (id == IDM_FORMAT_FONT) {
		command = new FontCommand(notepannel);
	}
	else if (id == IDM_FORMAT_SAVE) {
		command = new SaveCommand(notepannel);
	}	
	else if (id == IDM_FORMAT_SAVEAS) {
		command = new SaveAsCommand(notepannel);
	}
	else if (id == IDM_FORMAT_LOAD) {
		command = new LoadCommand(notepannel);
	}
	else if (id == IDM_FORMAT_CLOSE) {
		command = new CloseCommand(notepannel);
	}
	else if (id == IDM_FORMAT_LINEWRAP) {
		command = new LineWrapCommand(notepannel);
	}
	else if (id == IDM_FORMAT_ZOOMIN) {
		command = new ZoomInCommand(notepannel);
	}
	else if (id == IDM_FORMAT_ZOOMOUT) {
		command = new ZoomOutCommand(notepannel);
	}
	else if (id == IDM_FORMAT_RESTOREDEFALTZOOM) {
		command = new RestoreDefaultZoomCommand(notepannel);
	}
	else if (id == IDM_FORMAT_NEW) {
		command = new NewCommand(notepannel);
	}
	else if (id == IDM_FORMAT_COPY) {
		command = new CopyCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_SELECTALL) {
		command = new SelectAllCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_CUT) {
		command = new CutCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_DELETE) {
		command = new DeleteCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_PASTE) {
		command = new PasteCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_UNDO) {
		command = new UndoCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_REDO) {
		command = new UndoCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_FIND) {
		command = new FindCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_REPLACE) {
		command = new ReplaceCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_PAGESETTING) {
		command = new PageSettingCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_PREVIEW) {
		command = new PreviewCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_PRINT) {
		command = new PrintCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_STATUSBAR) {
		command = new StatusBarCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_DATE) {
		command = new DateCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_MOVETO) {
		command = new MoveToLineCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_ABOUTNOTEPAD) {
		command = new AboutNotepadCommand(this->notepannel);
	}
	else if (id == IDM_FORMAT_VIEWHELP) {
		command = new NotepadHelpCommand(this->notepannel);
	}
	return command;
}
Command* CommandCreator::Create(int id, Glyph* paper) {
	Command* command = 0;
	if (id == IDM_FORMAT_PASTE) {
		command = new PasteCommand(this->notepannel, paper);
	}
	return command;
}
Command* CommandCreator::Create(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Command* command = 0;
	Long lineOrder = -1;
	Glyph* currentLine = 0;
	Long charIndex = -2;
	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);

	lineOrder = this->notepannel->paper->GetCurrent();
	currentLine = this->notepannel->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();

	if (!(ctrlKeyState & 0x8000) && nChar != VK_BACK && nChar != VK_ESCAPE) { //�Է��� ���� ���ͳ� �̱۹���Ʈ�� //���߿� �и� ���
		command = new OnCharCommand(notepannel, nChar, nRepCnt, nFlags);
	}
	else if (nChar == VK_BACK && (!(lineOrder <= 0 && charIndex <= -1) || this->notepannel->isSelected == TRUE)) { //�Է��� ���� �齺���̽� �̰� �� ���� �ƴϸ�
		command = new BackspaceCommand(notepannel, nChar, nRepCnt, nFlags);
	}

	return command;
}
Command* CommandCreator::Create(WPARAM wParam, LPARAM lParam) {
	Command* command = 0;

	command = new OnIDECharCommand(this->notepannel, wParam, lParam);
	
	return command;
}