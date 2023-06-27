//FontCommand.cpp
/*
* ���ϸ�Ī:FontCommand.cpp
* ���:��Ʈ�� �ٲٴ� Ŀ���
* �ۼ���:������
* �ۼ�����:20220824
*/
#include "FontCommand.h"
#include "Notepannel.h"
#include "Font.h"
#include "CharacterMatrix.h"
#include "Caret.h"
#include "DocumentVirtualSize.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "Paper.h"
#include "Line.h"
#include <afxdlgs.h>

/*
* �Լ���Ī:FontCommand
* ���:������
*/
FontCommand::FontCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~FontCommand
* ���:�Ҹ���
*/
FontCommand::~FontCommand() {
}

/*
* �Լ���Ī:Execute
* ���:��Ʈ �ٲٱ� Ŀ��带 �����ϴ�
*/
void FontCommand::Execute() {
	Command* command = NULL;
	LOGFONT logFont;
	INT_PTR ret;
	UINT lineWrapState = -1;

	int fontSize = -1;

	//�����ȭ������ �ʱⰪ�� ���Ѵ�.
	CPaintDC cPaintDC(this->notepannel);
	cPaintDC.GetCurrentFont()->GetLogFont(&logFont);
	CFont cFont;
	Long bold = 400;
	if (this->notepannel->font->bold == TRUE) {
		bold = 800;
	}
	cFont.CreateFontA(this->notepannel->font->size, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
		this->notepannel->font->italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
		logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, this->notepannel->font->name);
	cFont.GetLogFont(&logFont);
	CFontDialog cFontDialog(&logFont);

	//�۲� ���� ��ȭ���ڸ� ǥ���Ѵ�.
	ret = cFontDialog.DoModal();
	
	if (ret == IDOK) { //��ȭ���ڿ��� ���� ����������
		//��ȭ���ڿ��� ������ �۲��� �����´�.
		cFontDialog.GetCurrentFont(&logFont);

		//�۲��� ���� 8~72 ���̰� �ƴϸ� �׿� �°� �������ش�.
		fontSize = cFontDialog.GetSize();
		if (fontSize < 80) {
			logFont.lfHeight = -MulDiv(8, GetDeviceCaps(this->notepannel->GetDC()->m_hDC, LOGPIXELSY), 72);
		}
		else if (fontSize > 720) {
			logFont.lfHeight = -MulDiv(72, GetDeviceCaps(this->notepannel->GetDC()->m_hDC, LOGPIXELSY), 72);
		}


		//�۲ÿ� �°� ��Ʈ�� �Է��Ѵ�.
		delete this->notepannel->font;
		this->notepannel->font = new Font(logFont);
		//������ ũ�⸦ �Է��Ѵ�.
		delete this->notepannel->characterMatrix;
		this->notepannel->characterMatrix = new CharacterMatrix(this->notepannel);
		//Ŭ���̾�Ʈ�� ũ�⼳���� �ٲ۴� - �۲ÿ� ���� �ٲ�� Ŭ���� �Ӽ��� �ֱ⿡
		delete this->notepannel->clientMatrix;
		this->notepannel->clientMatrix = new ClientMatrix(this->notepannel);
		//�������� ������ ������Ʈ�� ������ ǥ���Ѵ�. 
		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		//�޸����� ������Ʈ�� ȣ���Ѵ�.
		this->notepannel->Notify();
		//Ŭ���̾�Ʈ ȭ���� �����Ѵ�.
		this->notepannel->Invalidate(TRUE);
		//ĳ���� ǥ���Ѵ�. 
		this->notepannel->caret->ShowCaret();
	}
}