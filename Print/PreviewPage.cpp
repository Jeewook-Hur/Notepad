//PreviewPage.cpp
/*
* 파일명칭:PreviewPage.cpp
* 기능:미리보기 프레임윈도우
* 작성자:허지욱
* 작성일자:2022/12/16
*/
#include "PreviewPage.h"
#include "Notepannel.h"
#include "Glyph.h"
#include "Font.h"
#include "CharacterMatrix.h"
#include "PrintVisitor.h"
#include "Document.h"
#include "LineWrapper.h"
#include "PageSetting.h"

#include "Paper.h"
#include "Line.h"
#include "DummyLine.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

#include "resource.h"

#include <wingdi.h>
//wingdi.h

BEGIN_MESSAGE_MAP(PreviewPage, CFrameWnd)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_FIRST, OnUpdateCmdUIFirstButton)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_PREVIOUS, OnUpdateCmdUIPreviousButton)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_NEXT, OnUpdateCmdUINextButton)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_LAST, OnUpdateCmdUILastButton)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


/*
* 함수명칭:PreviewPage
* 기능:생성자
*/
PreviewPage::PreviewPage(Notepannel* notepannel) :notepannel(notepannel) {
	this->paperPreview = this->notepannel->paper->Clone();
	//종이의 더미줄을 병합한다. 
	this->paperPreview->MergeAllDummyLines();
	this->pageNumber = -1;
	this->currentPage = 0;
	this->lineNumberInPage = -1;
	this->widthToCutInPoint = 0;
	this->marginLeftStart = 0;
	this->marginTopStart = 0;
	this->marginRightEnd = 0;
	this->headerPoint = 0;
	this->marginBottomEnd = 0;
	this->footerPoint = 0;
	this->textHeigth = 0;
	this->isMaximixed = FALSE;
	this->isCreating = TRUE;
	
	this->dialogHeight = -1;
}

/*
* 함수명칭:~PreviewPage
* 기능:소멸자
*/
PreviewPage::~PreviewPage() {
	if (this->paperPreview != NULL) {
		delete this->paperPreview;
	}
	CWnd::DestroyWindow();
	this->notepannel->SetFocus();
}

/*
* 함수명칭:OnClose
* 기능:
*/
void PreviewPage::OnClose() {
	this->notepannel->ShowWindow(SW_SHOW);
	CWnd::DestroyWindow();
}


/*
* 함수명칭:OnCreate
* 기능:윈도우가 생성될때의 이벤트를 실행한다.
*/
int PreviewPage::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	LineWrapper lineWrapper(this->notepannel);

	int widthToCutInMM;
	int heightToCutInMM;
	int heightToCutInPoint;
	int charHeight = this->notepannel->characterMatrix->height;

	//다이얼로그 바를 추가한다. 
	this->reBar.Create(this, RBS_BANDBORDERS, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP, AFX_IDW_REBAR);
	this->dialogBar.Create(&this->reBar, IDD_DIALOGBAR, CBRS_TOP, IDD_DIALOGBAR);
	this->reBar.SetBorders(55);
	this->reBar.AddBar(&this->dialogBar);
	CRect dialogRect;
	this->dialogBar.GetWindowRect(&dialogRect);
	this->dialogHeight = dialogRect.bottom - dialogRect.top;

#if 0
	WINDOWINFO windowInfo{ 0, };
	this->GetWindowInfo(&windowInfo);
	CRect windowRect = windowInfo.rcClient;
	CRect pannelRect;
	pannelRect = { 0,windowRect.bottom - 20, windowRect.right - windowRect.left, 20 };
	this->dialogBar.MoveWindow(&pannelRect);
	this->dialogBar.ShowWindow(SW_SHOW);
#endif

	//메모장의 글꼴을 기준으로 
	//자동개행한다.
	widthToCutInMM = this->notepannel->pageSetting->pageWidth - this->notepannel->pageSetting->marginLeft - this->notepannel->pageSetting->marginRight;
	//실제 길이와 1.2배 배율로 용지를 만든다. 
	this->widthToCutInPoint = (int)(widthToCutInMM / 0.3528 / 0.7333);
	lineWrapper.Warp(this->paperPreview, widthToCutInPoint);

	//배율에 따른 용지안의 줄수를 구한다. 
	heightToCutInMM = this->notepannel->pageSetting->pageHeight - this->notepannel->pageSetting->marginTop - this->notepannel->pageSetting->marginBottom - this->notepannel->pageSetting->headerLength - this->notepannel->pageSetting->footerLength;
	heightToCutInPoint = (int)(heightToCutInMM / 0.3528 / 0.7333);
	this->lineNumberInPage = (heightToCutInPoint - this->dialogHeight) / charHeight;

	//개행된 종이 수를 구한다.
	this->pageNumber = this->paperPreview->GetLength() / this->lineNumberInPage + 1;
	//디폴트 페이지 수를 정한다. 
	this->currentPage = 1;

	this->isCreating = FALSE;
	return 0;
}

/*
* 함수명칭:OnPaint
* 기능:윈도우가 갱신될때의 이벤트를 실행한다.
*/
void PreviewPage::OnPaint() {
	CPaintDC cPaintDC(this);
	PrintVisitor printVisitor(this, this->notepannel, &cPaintDC);
	CString name;
	int height;
	Long bold = 400;
	BOOL italic;
	CFont cFont;
	CFont hfFont;
	CFont* previousFont = 0;
	LOGFONT logFont;
	COLORREF rgbGray = 0x009E9E9E;
	COLORREF rgbBlack = 0x00000000;
	COLORREF rgbWhite = 0x00FFFFFF;
	WINDOWINFO windowInfo{ 0, };
	int clientWidth;
	int clientHeight;
	int pageWidth;
	int pageHeight;
	int pageLocation;
	double defaultPointForOne;
	CRect rect;
	CPen pen(PS_DOT, 1, rgbBlack);

	//클라이언트의 정보를 가져온다.
	this->GetWindowInfo(&windowInfo);

	

	clientWidth = windowInfo.rcClient.right - windowInfo.rcClient.left;
	clientHeight = windowInfo.rcClient.bottom - windowInfo.rcClient.top;
	pageHeight = clientHeight - 10 - dialogHeight;
	pageWidth = (int)(pageHeight * 210 / 297);
	pageLocation = (clientWidth - pageWidth) / 2;
	if (pageLocation < 0) {
		pageLocation = 0;
	}
	defaultPointForOne = pageHeight / 297.0;


	//배경색을 칠한다.
	GetClientRect(rect);
	CRect grayRect = rect;
	grayRect.top = grayRect.top + dialogHeight;
	cPaintDC.FillSolidRect(grayRect, rgbGray);

	//종이를 지칭할 네모를 만든다. 
	cPaintDC.Rectangle(pageLocation, 5 + dialogHeight, pageLocation + pageWidth, 5 + pageHeight + dialogHeight);

	//네모 안에 여백을 표현하는 점선을 그린다. 
	this->marginLeftStart = pageLocation + (int)(defaultPointForOne * this->notepannel->pageSetting->marginLeft);
	this->marginTopStart = dialogHeight + 5 + (int)(defaultPointForOne * this->notepannel->pageSetting->marginTop);
	this->marginRightEnd = pageLocation + pageWidth - (int)(defaultPointForOne * this->notepannel->pageSetting->marginRight);
	this->headerPoint = marginTopStart + (int)(defaultPointForOne * this->notepannel->pageSetting->headerLength);
	this->marginBottomEnd = dialogHeight + 5 + pageHeight - (int)(defaultPointForOne * this->notepannel->pageSetting->marginBottom);
	this->footerPoint = marginBottomEnd - (int)(defaultPointForOne * this->notepannel->pageSetting->footerLength);

	//글자크기를 역산한다.
	double ratio = (pageHeight / 297.0);
	this->textHeigth = (int)(this->notepannel->characterMatrix->height * ratio / 2.85 * 0.7333);
	if (this->textHeigth <= 0) {
		this->textHeigth = 1;
	}
	//this->textHeigth = 24;

	//글자 쓰기
	//현재 설정된 시스템 기본 글꼴을 가져온다. 
	cPaintDC.GetCurrentFont()->GetLogFont(&logFont);
	//바꿀 글꼴의 스타일을 가져온다. //Font의 접근제한자는 다 없앤다. 
	name = this->notepannel->font->name;
	height = this->textHeigth;
	if (this->notepannel->font->bold == TRUE) {
		bold = 800;
	}
	italic = this->notepannel->font->italic;
	//바꿀글꼴에 맞게 글꼴을 설정한다. 
	cFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
		italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
		logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);
	//바꾼 글꼴을 갱신한다.
	previousFont = cPaintDC.SelectObject(&cFont);

	printVisitor.lineOrder = lineNumberInPage * (currentPage - 1);
	this->paperPreview->Accept(&printVisitor);


	//cPaintDC.SelectObject(previousFont);

	hfFont.CreateFontA(20, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
		italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
		logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);
	//바꾼 글꼴을 갱신한다.
	cPaintDC.SelectObject(&hfFont);


	//머릿말을 출력한다. 
	//cPaintDC.TextOutA(marginLeftStart + 2, marginTopStart + 2, this->notepannel->pageSetting->headerString.c_str());
	RECT header = { marginLeftStart , marginTopStart , marginRightEnd , headerPoint };
	cPaintDC.DrawTextA(this->notepannel->pageSetting->headerString.c_str(), &header, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//꼬릿말을 출력한다.
	//cPaintDC.TextOutA(marginLeftStart + 2, marginBottomEnd - this->textHeigth, this->notepannel->pageSetting->footerString.c_str());
	RECT footer = { marginLeftStart, footerPoint, marginRightEnd, marginBottomEnd };
	cPaintDC.DrawTextA(this->notepannel->pageSetting->footerString.c_str(), &footer, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	cPaintDC.SelectObject(&pen);
	//윗줄
	cPaintDC.MoveTo(marginLeftStart, marginTopStart);
	cPaintDC.LineTo(marginRightEnd, marginTopStart);
	//머릿말
	cPaintDC.MoveTo(marginLeftStart, headerPoint);
	cPaintDC.LineTo(marginRightEnd, headerPoint);
	//꼬릿말
	cPaintDC.MoveTo(marginLeftStart, footerPoint);
	cPaintDC.LineTo(marginRightEnd, footerPoint);
	//아랫줄
	cPaintDC.MoveTo(marginLeftStart, marginBottomEnd);
	cPaintDC.LineTo(marginRightEnd, marginBottomEnd);
	//왼줄
	cPaintDC.MoveTo(marginLeftStart - 2, marginTopStart);
	cPaintDC.LineTo(marginLeftStart - 2, marginBottomEnd);
	//오른줄
	cPaintDC.MoveTo(marginRightEnd + 2, marginTopStart);
	cPaintDC.LineTo(marginRightEnd + 2, marginBottomEnd);

}

/*
* 함수명칭:OnSize
* 기능:최대화, 최소화 할때의 이벤트를 수행한다.
*/
void PreviewPage::OnSize(UINT nType, int cx, int cy) {
	if (nType == SIZE_MAXIMIZED) { //최대화 버튼을 클릭했을 때
		this->OnSizing(0, 0);

		this->isMaximixed = TRUE;
	}
	else if (nType == SIZE_RESTORED && this->isMaximixed == TRUE) { //최대화상태에서 일반화 될때
		this->OnSizing(0, 0);


		this->isMaximixed = FALSE;
	}
}

/*
* 함수명칭:OnSizing
* 기능:화면의 크기를 조절할 때의 이벤트를 수행한다. 
*/
void PreviewPage::OnSizing(UINT nSide, LPRECT lpRect) {
	//클라이언트의 정보를 가져온다.
	WINDOWINFO windowInfo{ 0, };
	this->GetWindowInfo(&windowInfo);

	//리바의 경계를 조정해준다. 
	int clientWidth = windowInfo.rcClient.right - windowInfo.rcClient.left;
	int dialogBarWidth = 500;
	int reBarXBorders = (clientWidth - dialogBarWidth) / 2;
	if (clientWidth < 500) {
		reBarXBorders = 0;
	}
	this->reBar.SetBorders(reBarXBorders);

	//다이얼로그 바의 크기를 조정해준다. 
	CRect windowRect = windowInfo.rcClient;
	CRect pannelRect;
	pannelRect = { 0, 0, windowRect.right - windowRect.left, dialogHeight };
	this->reBar.MoveWindow(&pannelRect);

	this->Invalidate(FALSE);

}


/*
* 함수명칭:Print
* 기능:DC를 인쇄한다.
*/
void PreviewPage::Print(HDC hPrinter) {
	CPaintDC cPaintDC(this);
	CDC* printer = 0;
	CString name;
	int height;
	Long bold = 400;
	BOOL italic;
	CFont cFont;
	CFont hfFont;
	CFont* previousFont = 0;
	CFont* currentFont = 0;
	CFont* headerFont = 0;
	LOGFONT logFont;
	int i = 0;
	int pageWidth;
	int pageHeight;
	double defaultPointForOne;

	if (hPrinter != 0) { //프린터 핸들이 존재하면 
		//프린터 DC를 가져온다. 
		printer = CDC::FromHandle(hPrinter);

		//클라이언트의 정보를 가져온다.
		pageHeight = GetDeviceCaps(hPrinter, VERTRES);
		pageWidth = GetDeviceCaps(hPrinter, HORZRES);
		defaultPointForOne = pageHeight / 297;

		//네모 안에 여백을 표현하는 점선을 그린다. 
		this->marginLeftStart = (int)(defaultPointForOne * this->notepannel->pageSetting->marginLeft);
		this->marginTopStart = (int)(defaultPointForOne * this->notepannel->pageSetting->marginTop);
		this->marginRightEnd = pageWidth - (int)(defaultPointForOne * this->notepannel->pageSetting->marginRight);
		this->headerPoint = marginTopStart + (int)(defaultPointForOne * this->notepannel->pageSetting->headerLength);
		this->marginBottomEnd = pageHeight - (int)(defaultPointForOne * this->notepannel->pageSetting->marginBottom);
		this->footerPoint = marginBottomEnd - (int)(defaultPointForOne * this->notepannel->pageSetting->footerLength);

		PrintVisitor printVisitor(this, this->notepannel, printer);

		if (printer != 0) { //프린터 DC가 존재하면 
			//현재 설정된 시스템 기본 글꼴을 가져온다. 
			cPaintDC.GetCurrentFont()->GetLogFont(&logFont);
			//바꿀 글꼴의 스타일을 가져온다. //Font의 접근제한자는 다 없앤다. 
			name = this->notepannel->font->name;
			this->textHeigth = (int)(GetDeviceCaps(hPrinter, LOGPIXELSY) / 72.0 * this->notepannel->characterMatrix->height * 0.7333);
			height = this->textHeigth;
			if (this->notepannel->font->bold == TRUE) {
				bold = 800;
			}
			italic = this->notepannel->font->italic;
			//바꿀글꼴에 맞게 글꼴을 설정한다. 
			cFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
				italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
				logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);

			hfFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
				italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
				logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);

			//바꾼 글꼴을 갱신한다.
			previousFont = printer->SelectObject(&hfFont);
			headerFont = printer->SelectObject(&cFont);
			currentFont = printer->SelectObject(previousFont);
			printer->SelectObject(currentFont);

			RECT header = { marginLeftStart , marginTopStart , marginRightEnd , headerPoint };
			RECT footer = { marginLeftStart, footerPoint, marginRightEnd, marginBottomEnd };

			CString documentName;
			documentName.Format("%s", this->notepannel->document->GetName().c_str());

			this->currentPage = 1;

			int result = -1;

			result = printer->StartDocA((LPCTSTR)documentName);
			//DOCINFOA docInfo = { sizeof(DOCINFOA), documentName, documentName, NULL, 0 };
			//result = printer->StartDocA(&docInfo);
			//result = StartDocA(hPrinter , &docInfo);

			if (result > 0) {
				while (i < this->pageNumber) {
					printer->StartPage();


					this->paperPreview->Accept(&printVisitor);
					this->currentPage++;

					currentFont = printer->SelectObject(headerFont);

					//머릿말을 출력한다. 
					//printer->TextOutA(marginLeftStart + 2, marginTopStart + 2, this->notepannel->pageSetting->headerString.c_str());
					printer->DrawTextA(this->notepannel->pageSetting->headerString.c_str(), &header, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

					//꼬릿말을 출력한다.
					//printer->TextOutA(marginLeftStart + 2, marginBottomEnd - this->textHeigth, this->notepannel->pageSetting->footerString.c_str());
					printer->DrawTextA(this->notepannel->pageSetting->footerString.c_str(), &footer, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					
					headerFont = printer->SelectObject(currentFont);

					printer->EndPage();
					i++;
				}
				printer->EndDoc();
			}
			else {
				//printer->AbortDoc();
				// Abort doc 안쓰는 쪽으로 다시 짜자 
			}
			//printer->AbortDoc();

			//스레드 초기화 
			HRESULT hResult;
			hResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

			printer->SelectObject(previousFont);
			currentFont->DeleteObject();

			
		}
	}
}

void PreviewPage::OnUpdateCmdUIFirstButton(CCmdUI* pCmdUI) {
	if (pageNumber > 1) {
		pCmdUI->Enable(TRUE);
	}
}
void PreviewPage::OnUpdateCmdUIPreviousButton(CCmdUI* pCmdUI) {
	if (pageNumber > 1) {
		pCmdUI->Enable(TRUE);
	}
}
void PreviewPage::OnUpdateCmdUINextButton(CCmdUI* pCmdUI) {
	if (pageNumber > 1) {
		pCmdUI->Enable(TRUE);
	}
}
void PreviewPage::OnUpdateCmdUILastButton(CCmdUI* pCmdUI) {
	if (pageNumber > 1) {
		pCmdUI->Enable(TRUE);
	}
}

void PreviewPage::OnFirstButtonClicked() {
	currentPage = 1;

	this->Invalidate(FALSE);
}

void PreviewPage::OnPreviousButtonClicked() {
	currentPage--;
	if (currentPage <= 0) {
		currentPage = 1;
	}
	this->Invalidate(FALSE);
}

void PreviewPage::OnNextButtonClicked() {
	currentPage++;
	if (currentPage > pageNumber) {
		currentPage = pageNumber;
	}
	this->Invalidate(FALSE);
}

void PreviewPage::OnLastButtonClicked() {
	currentPage = pageNumber;
	this->Invalidate(FALSE);
}

void PreviewPage::OnGetMinMaxInfo(MINMAXINFO* lpMMI) {
	lpMMI->ptMinTrackSize.x = 630;

}