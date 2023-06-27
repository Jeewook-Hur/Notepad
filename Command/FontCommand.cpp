//FontCommand.cpp
/*
* 파일명칭:FontCommand.cpp
* 기능:폰트를 바꾸는 커멘드
* 작성자:허지욱
* 작성일자:20220824
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
* 함수명칭:FontCommand
* 기능:생성자
*/
FontCommand::FontCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~FontCommand
* 기능:소멸자
*/
FontCommand::~FontCommand() {
}

/*
* 함수명칭:Execute
* 기능:폰트 바꾸기 커멘드를 실행하다
*/
void FontCommand::Execute() {
	Command* command = NULL;
	LOGFONT logFont;
	INT_PTR ret;
	UINT lineWrapState = -1;

	int fontSize = -1;

	//공통대화상자의 초기값을 정한다.
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

	//글꼴 공통 대화상자를 표시한다.
	ret = cFontDialog.DoModal();
	
	if (ret == IDOK) { //대화상자에서 예를 선택했으면
		//대화상자에서 선택한 글꼴을 가져온다.
		cFontDialog.GetCurrentFont(&logFont);

		//글꼴의 값이 8~72 사이가 아니면 그에 맞게 조정해준다.
		fontSize = cFontDialog.GetSize();
		if (fontSize < 80) {
			logFont.lfHeight = -MulDiv(8, GetDeviceCaps(this->notepannel->GetDC()->m_hDC, LOGPIXELSY), 72);
		}
		else if (fontSize > 720) {
			logFont.lfHeight = -MulDiv(72, GetDeviceCaps(this->notepannel->GetDC()->m_hDC, LOGPIXELSY), 72);
		}


		//글꼴에 맞게 폰트를 입력한다.
		delete this->notepannel->font;
		this->notepannel->font = new Font(logFont);
		//글자의 크기를 입력한다.
		delete this->notepannel->characterMatrix;
		this->notepannel->characterMatrix = new CharacterMatrix(this->notepannel);
		//클라이언트의 크기설정을 바꾼다 - 글꼴에 따라 바뀌는 클래스 속성이 있기에
		delete this->notepannel->clientMatrix;
		this->notepannel->clientMatrix = new ClientMatrix(this->notepannel);
		//문서에서 내용의 업데이트를 했음을 표시한다. 
		this->notepannel->documentUploaded = TRUE;
		this->notepannel->clientMoveCheck = TRUE;
		//메모장의 업데이트를 호출한다.
		this->notepannel->Notify();
		//클라이언트 화면을 갱신한다.
		this->notepannel->Invalidate(TRUE);
		//캐럿을 표시한다. 
		this->notepannel->caret->ShowCaret();
	}
}