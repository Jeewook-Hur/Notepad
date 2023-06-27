//PreviewPage.cpp
/*
* ���ϸ�Ī:PreviewPage.cpp
* ���:�̸����� ������������
* �ۼ���:������
* �ۼ�����:2022/12/16
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
* �Լ���Ī:PreviewPage
* ���:������
*/
PreviewPage::PreviewPage(Notepannel* notepannel) :notepannel(notepannel) {
	this->paperPreview = this->notepannel->paper->Clone();
	//������ �������� �����Ѵ�. 
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
* �Լ���Ī:~PreviewPage
* ���:�Ҹ���
*/
PreviewPage::~PreviewPage() {
	if (this->paperPreview != NULL) {
		delete this->paperPreview;
	}
	CWnd::DestroyWindow();
	this->notepannel->SetFocus();
}

/*
* �Լ���Ī:OnClose
* ���:
*/
void PreviewPage::OnClose() {
	this->notepannel->ShowWindow(SW_SHOW);
	CWnd::DestroyWindow();
}


/*
* �Լ���Ī:OnCreate
* ���:�����찡 �����ɶ��� �̺�Ʈ�� �����Ѵ�.
*/
int PreviewPage::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	LineWrapper lineWrapper(this->notepannel);

	int widthToCutInMM;
	int heightToCutInMM;
	int heightToCutInPoint;
	int charHeight = this->notepannel->characterMatrix->height;

	//���̾�α� �ٸ� �߰��Ѵ�. 
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

	//�޸����� �۲��� �������� 
	//�ڵ������Ѵ�.
	widthToCutInMM = this->notepannel->pageSetting->pageWidth - this->notepannel->pageSetting->marginLeft - this->notepannel->pageSetting->marginRight;
	//���� ���̿� 1.2�� ������ ������ �����. 
	this->widthToCutInPoint = (int)(widthToCutInMM / 0.3528 / 0.7333);
	lineWrapper.Warp(this->paperPreview, widthToCutInPoint);

	//������ ���� �������� �ټ��� ���Ѵ�. 
	heightToCutInMM = this->notepannel->pageSetting->pageHeight - this->notepannel->pageSetting->marginTop - this->notepannel->pageSetting->marginBottom - this->notepannel->pageSetting->headerLength - this->notepannel->pageSetting->footerLength;
	heightToCutInPoint = (int)(heightToCutInMM / 0.3528 / 0.7333);
	this->lineNumberInPage = (heightToCutInPoint - this->dialogHeight) / charHeight;

	//����� ���� ���� ���Ѵ�.
	this->pageNumber = this->paperPreview->GetLength() / this->lineNumberInPage + 1;
	//����Ʈ ������ ���� ���Ѵ�. 
	this->currentPage = 1;

	this->isCreating = FALSE;
	return 0;
}

/*
* �Լ���Ī:OnPaint
* ���:�����찡 ���ŵɶ��� �̺�Ʈ�� �����Ѵ�.
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

	//Ŭ���̾�Ʈ�� ������ �����´�.
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


	//������ ĥ�Ѵ�.
	GetClientRect(rect);
	CRect grayRect = rect;
	grayRect.top = grayRect.top + dialogHeight;
	cPaintDC.FillSolidRect(grayRect, rgbGray);

	//���̸� ��Ī�� �׸� �����. 
	cPaintDC.Rectangle(pageLocation, 5 + dialogHeight, pageLocation + pageWidth, 5 + pageHeight + dialogHeight);

	//�׸� �ȿ� ������ ǥ���ϴ� ������ �׸���. 
	this->marginLeftStart = pageLocation + (int)(defaultPointForOne * this->notepannel->pageSetting->marginLeft);
	this->marginTopStart = dialogHeight + 5 + (int)(defaultPointForOne * this->notepannel->pageSetting->marginTop);
	this->marginRightEnd = pageLocation + pageWidth - (int)(defaultPointForOne * this->notepannel->pageSetting->marginRight);
	this->headerPoint = marginTopStart + (int)(defaultPointForOne * this->notepannel->pageSetting->headerLength);
	this->marginBottomEnd = dialogHeight + 5 + pageHeight - (int)(defaultPointForOne * this->notepannel->pageSetting->marginBottom);
	this->footerPoint = marginBottomEnd - (int)(defaultPointForOne * this->notepannel->pageSetting->footerLength);

	//����ũ�⸦ �����Ѵ�.
	double ratio = (pageHeight / 297.0);
	this->textHeigth = (int)(this->notepannel->characterMatrix->height * ratio / 2.85 * 0.7333);
	if (this->textHeigth <= 0) {
		this->textHeigth = 1;
	}
	//this->textHeigth = 24;

	//���� ����
	//���� ������ �ý��� �⺻ �۲��� �����´�. 
	cPaintDC.GetCurrentFont()->GetLogFont(&logFont);
	//�ٲ� �۲��� ��Ÿ���� �����´�. //Font�� ���������ڴ� �� ���ش�. 
	name = this->notepannel->font->name;
	height = this->textHeigth;
	if (this->notepannel->font->bold == TRUE) {
		bold = 800;
	}
	italic = this->notepannel->font->italic;
	//�ٲܱ۲ÿ� �°� �۲��� �����Ѵ�. 
	cFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
		italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
		logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);
	//�ٲ� �۲��� �����Ѵ�.
	previousFont = cPaintDC.SelectObject(&cFont);

	printVisitor.lineOrder = lineNumberInPage * (currentPage - 1);
	this->paperPreview->Accept(&printVisitor);


	//cPaintDC.SelectObject(previousFont);

	hfFont.CreateFontA(20, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
		italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
		logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);
	//�ٲ� �۲��� �����Ѵ�.
	cPaintDC.SelectObject(&hfFont);


	//�Ӹ����� ����Ѵ�. 
	//cPaintDC.TextOutA(marginLeftStart + 2, marginTopStart + 2, this->notepannel->pageSetting->headerString.c_str());
	RECT header = { marginLeftStart , marginTopStart , marginRightEnd , headerPoint };
	cPaintDC.DrawTextA(this->notepannel->pageSetting->headerString.c_str(), &header, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//�������� ����Ѵ�.
	//cPaintDC.TextOutA(marginLeftStart + 2, marginBottomEnd - this->textHeigth, this->notepannel->pageSetting->footerString.c_str());
	RECT footer = { marginLeftStart, footerPoint, marginRightEnd, marginBottomEnd };
	cPaintDC.DrawTextA(this->notepannel->pageSetting->footerString.c_str(), &footer, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	cPaintDC.SelectObject(&pen);
	//����
	cPaintDC.MoveTo(marginLeftStart, marginTopStart);
	cPaintDC.LineTo(marginRightEnd, marginTopStart);
	//�Ӹ���
	cPaintDC.MoveTo(marginLeftStart, headerPoint);
	cPaintDC.LineTo(marginRightEnd, headerPoint);
	//������
	cPaintDC.MoveTo(marginLeftStart, footerPoint);
	cPaintDC.LineTo(marginRightEnd, footerPoint);
	//�Ʒ���
	cPaintDC.MoveTo(marginLeftStart, marginBottomEnd);
	cPaintDC.LineTo(marginRightEnd, marginBottomEnd);
	//����
	cPaintDC.MoveTo(marginLeftStart - 2, marginTopStart);
	cPaintDC.LineTo(marginLeftStart - 2, marginBottomEnd);
	//������
	cPaintDC.MoveTo(marginRightEnd + 2, marginTopStart);
	cPaintDC.LineTo(marginRightEnd + 2, marginBottomEnd);

}

/*
* �Լ���Ī:OnSize
* ���:�ִ�ȭ, �ּ�ȭ �Ҷ��� �̺�Ʈ�� �����Ѵ�.
*/
void PreviewPage::OnSize(UINT nType, int cx, int cy) {
	if (nType == SIZE_MAXIMIZED) { //�ִ�ȭ ��ư�� Ŭ������ ��
		this->OnSizing(0, 0);

		this->isMaximixed = TRUE;
	}
	else if (nType == SIZE_RESTORED && this->isMaximixed == TRUE) { //�ִ�ȭ���¿��� �Ϲ�ȭ �ɶ�
		this->OnSizing(0, 0);


		this->isMaximixed = FALSE;
	}
}

/*
* �Լ���Ī:OnSizing
* ���:ȭ���� ũ�⸦ ������ ���� �̺�Ʈ�� �����Ѵ�. 
*/
void PreviewPage::OnSizing(UINT nSide, LPRECT lpRect) {
	//Ŭ���̾�Ʈ�� ������ �����´�.
	WINDOWINFO windowInfo{ 0, };
	this->GetWindowInfo(&windowInfo);

	//������ ��踦 �������ش�. 
	int clientWidth = windowInfo.rcClient.right - windowInfo.rcClient.left;
	int dialogBarWidth = 500;
	int reBarXBorders = (clientWidth - dialogBarWidth) / 2;
	if (clientWidth < 500) {
		reBarXBorders = 0;
	}
	this->reBar.SetBorders(reBarXBorders);

	//���̾�α� ���� ũ�⸦ �������ش�. 
	CRect windowRect = windowInfo.rcClient;
	CRect pannelRect;
	pannelRect = { 0, 0, windowRect.right - windowRect.left, dialogHeight };
	this->reBar.MoveWindow(&pannelRect);

	this->Invalidate(FALSE);

}


/*
* �Լ���Ī:Print
* ���:DC�� �μ��Ѵ�.
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

	if (hPrinter != 0) { //������ �ڵ��� �����ϸ� 
		//������ DC�� �����´�. 
		printer = CDC::FromHandle(hPrinter);

		//Ŭ���̾�Ʈ�� ������ �����´�.
		pageHeight = GetDeviceCaps(hPrinter, VERTRES);
		pageWidth = GetDeviceCaps(hPrinter, HORZRES);
		defaultPointForOne = pageHeight / 297;

		//�׸� �ȿ� ������ ǥ���ϴ� ������ �׸���. 
		this->marginLeftStart = (int)(defaultPointForOne * this->notepannel->pageSetting->marginLeft);
		this->marginTopStart = (int)(defaultPointForOne * this->notepannel->pageSetting->marginTop);
		this->marginRightEnd = pageWidth - (int)(defaultPointForOne * this->notepannel->pageSetting->marginRight);
		this->headerPoint = marginTopStart + (int)(defaultPointForOne * this->notepannel->pageSetting->headerLength);
		this->marginBottomEnd = pageHeight - (int)(defaultPointForOne * this->notepannel->pageSetting->marginBottom);
		this->footerPoint = marginBottomEnd - (int)(defaultPointForOne * this->notepannel->pageSetting->footerLength);

		PrintVisitor printVisitor(this, this->notepannel, printer);

		if (printer != 0) { //������ DC�� �����ϸ� 
			//���� ������ �ý��� �⺻ �۲��� �����´�. 
			cPaintDC.GetCurrentFont()->GetLogFont(&logFont);
			//�ٲ� �۲��� ��Ÿ���� �����´�. //Font�� ���������ڴ� �� ���ش�. 
			name = this->notepannel->font->name;
			this->textHeigth = (int)(GetDeviceCaps(hPrinter, LOGPIXELSY) / 72.0 * this->notepannel->characterMatrix->height * 0.7333);
			height = this->textHeigth;
			if (this->notepannel->font->bold == TRUE) {
				bold = 800;
			}
			italic = this->notepannel->font->italic;
			//�ٲܱ۲ÿ� �°� �۲��� �����Ѵ�. 
			cFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
				italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
				logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);

			hfFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
				italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
				logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);

			//�ٲ� �۲��� �����Ѵ�.
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

					//�Ӹ����� ����Ѵ�. 
					//printer->TextOutA(marginLeftStart + 2, marginTopStart + 2, this->notepannel->pageSetting->headerString.c_str());
					printer->DrawTextA(this->notepannel->pageSetting->headerString.c_str(), &header, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

					//�������� ����Ѵ�.
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
				// Abort doc �Ⱦ��� ������ �ٽ� ¥�� 
			}
			//printer->AbortDoc();

			//������ �ʱ�ȭ 
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