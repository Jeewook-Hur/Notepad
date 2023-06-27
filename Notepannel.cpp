//Notepannel.cpp
/*
* ���ϸ�Ī:Notepannel.cpp
* ���:�޸����� Ŭ���̾�Ʈ ������ ����� �ϴ� �г�
* �ۼ���:������
* �ۼ�����:2022/12/20
*/
#include "Notepannel.h"
#include "Notepad.h"
#include "resource.h"

#include "Paper.h"
#include "Line.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "GlyphCreater.h"
#include "Caret.h"
#include "Select.h"

#include "Font.h"
#include "CharacterMatrix.h"
#include "Document.h"
#include "DocumentVirtualSize.h"
#include "ClientLocation.h"
#include "ClientMatrix.h"
#include "Scroll.h"
#include "Zoomer.h"
#include "PaintVisitor.h"
#include "Clipboard.h"

#include "Command.h"
#include "CommandCreator.h"
#include "MacroCommand.h"

#include "KeyAction.h"
#include "KeyActionCreator.h"

#include "VerticalScrollAction.h"
#include "VerticalScrollActionCreator.h"
#include "HorizontalScrollAction.h"
#include "HorizontalScrollActionCreator.h"

#include "MouseWheelAction.h"
#include "MouseWheelActionCreator.h"

#include "Finder.h"
#include "ResultFound.h"
#include "Replacer.h"

#include "PageSetting.h"

#include "StatusBar.h"

#include <afxdlgs.h>
#include <afxcmn.h>

//#include <atlimage.h> // CImage��

#include <string>
using namespace std;

//������ Ŭ����
#include "LineWrapControl.h"
#include "DocumentVirtualSizeControl.h"
#include "ScrollInfoControl.h"
#include "CaretControl.h"
#include "AutoScrollPositionControl.h"
#include "StatusBarControl.h"

//�������� ����
HHOOK hSaveMessageBoxHook;
// Register Finder window message.
static UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

BEGIN_MESSAGE_MAP(Notepannel, CWnd)
	//ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnStartComposition)
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_SIZING()
	// Message map entry to map from message to handler function.
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE, OnFindReplace)
END_MESSAGE_MAP()

/*
* �Լ���Ī:Notepannel
* ���:������
*/
Notepannel::Notepannel(Notepad* notepad) :notepad(notepad) {
	//���� Ŭ������ �ʱ�ȭ�Ѵ�.
	this->paper = NULL;
	this->caret = NULL;
	this->font = NULL;
	this->characterMatrix = NULL;
	this->document = NULL;
	this->documentVirtualSize = NULL;
	this->clientLocation = NULL;
	this->clientMatrix = NULL;
	this->scroll = NULL;
	this->zoomer = NULL;
	this->select = NULL;
	this->clipboard = NULL;
	this->macroCommand = NULL;
	this->finder = NULL;
	this->resultFound = NULL;
	this->replacer = NULL;
	this->pageSetting = NULL;

	//�Ӽ��� �ʱ�ȭ�Ѵ�.
	this->isComposing = FALSE;
	this->isSaved = FALSE;
	this->hasChanged = FALSE;
	this->documentUploaded = FALSE;
	this->isLineWraping = FALSE;
	this->clientMoveCheck = FALSE;
	this->isCalledFromMenu = FALSE;
	this->isUpdating = FALSE;
	this->isMaximixed = FALSE;
	this->isSelected = FALSE;
	this->isSelecting = FALSE;
	this->hasLoaded = FALSE;
	this->hasOnSized = FALSE;
	this->hasClicked = FALSE;
	this->isScrollSetting = FALSE;
}

/*
* �Լ���Ī:~Notepannel
* ���:�Ҹ���
*/
Notepannel::~Notepannel() {
	Observer* observer = 0;


	//���� Ŭ������ �޸𸮸� �Ҵ������Ѵ�.
	if (this->paper != NULL) {
		delete this->paper;
	}
	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->font != NULL) {
		delete this->font;
	}
	if (this->characterMatrix != NULL) {
		delete this->characterMatrix;
	}
	if (this->document != NULL) {
		delete this->document;
	}
	if (this->documentVirtualSize != NULL) {
		delete this->documentVirtualSize;
	}
	if (this->clientLocation != NULL) {
		delete this->clientLocation;
	}
	if (this->clientMatrix != NULL) {
		delete this->clientMatrix;
	}
	if (this->scroll != NULL) {
		delete this->scroll;
	}
	if (this->zoomer != NULL) {
		delete this->zoomer;
	}
	if (this->select != NULL) {
		delete this->select;
	}
	if (this->clipboard != NULL) {
		delete this->clipboard;
	}
	if (this->macroCommand != NULL) {
		delete this->macroCommand;
	}
	if (this->finder != NULL) {
		delete this->finder;
	}
	if (this->resultFound != NULL) {
		delete this->resultFound;
	}
	if (this->replacer != NULL) {
		delete this->replacer;
	}
	if (this->pageSetting != NULL) {
		delete this->pageSetting;
	}


	//������ Ŭ�������� �Ҵ������Ѵ�.
	int i = 0;
	while (i < this->GetSubjectLength()) {
		observer = this->GetObserver(i);
		delete observer;
		i++;
	}
	
	this->tempDC.DeleteDC();
	this->currentBitmap.DeleteObject();
}

/*
* �Լ���Ī:OnCreate
* ���:�����찡 �����ɶ��� �̺�Ʈ�� �����Ѵ�.
*/
int Notepannel::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct); //�������̵�

	GlyphCreater glyphCreater;
	Glyph* line = NULL;
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long indexLine = -1;

//#if 0
	//���̸� �����.
	this->paper = glyphCreater.Create("");
	//���̿� ���� �����Ѵ�.
	line = glyphCreater.Create("\r\n");
	indexLine = this->paper->Add(line);

	//������ �����. 
	this->document = new Document();
	//�÷��׷� ������� ������ ǥ���Ѵ�. 
	this->isSaved = FALSE; //->notepad->SetWindowText(windowTitle);
	//������ ������� �ʾ����� ǥ���Ѵ�.
	this->documentUploaded = FALSE;
//#endif

#if 0
	//�׽�Ʈ�� ���� //H://�� ����̺�//(((Notepad)))/��� �׽�Ʈ��
	//string tempPath = "H://�� ����̺�//(((Notepad)))/��� �׽�Ʈ��";//����ũž ���
	string tempPath = "G://�� ����̺�//(((Notepad)))//��� �׽�Ʈ��"; //��Ʈ�� ���
	string tempName = "�����ٶ󸶹ٻ�";
	this->document = new Document(tempPath, tempName);
	this->paper = this->document->Load();
	this->isSaved = TRUE;
	this->documentUploaded = FALSE;
#endif


	CString windowTitle;
	windowTitle.Format("%s - Windows �޸���", this->document->GetName().c_str());
	this->notepad->SetWindowText(windowTitle);

	//�÷��׷� ������� ������ ǥ���Ѵ�. 
	this->hasChanged = FALSE;

	//�۲��� ����� //�̰� �⺻ �۲��� ����� ����
	//this->GetDC()->GetCurrentFont()->GetLogFont(&logFont);
	this->font = new Font("����", 36);
	//�۲��� �ٲ۴�. //�׽�Ʈ�� �ڵ� // �����ձ۾� �ƺ��۾� // �ü�ü // �ü� // ���� ��� //����

	//Ŭ���̾�Ʈ ������ ���Ѵ�.
	this->zoomer = new Zoomer(100);

	//���� ��Ʈ����Ʋ �����. 
	this->characterMatrix = new CharacterMatrix(this);

	//ĳ���� �����
	this->caret = new Caret(this);

	//��Ŭ����Ʈ ĳ���� �����.
	this->caret->Create(2, this->characterMatrix->height);

	//���� Ŭ������ �����.
	this->select = new Select(this);

	//Ŭ������ Ŭ������ �����. 
	this->clipboard = new Clipboard(this);

	//��ũ�� Ŀ��� Ŭ������ �����.
	this->macroCommand = new MacroCommand();

	//�˻���� Ŭ������ �����.
	this->resultFound = new ResultFound("");
	//ã�� Ŭ������ �����. 
	this->finder = new Finder(this);
	//�ٲٴ� Ŭ������ �����. 
	this->replacer = new Replacer(this);
	//������ ������ �Ѵ�
	this->pageSetting = new PageSetting(this);


	//Ŭ���̾�Ʈ�� ������ �����Ѵ�. //OnSize
	if (this->clientMatrix == NULL) {
		this->clientMatrix = new ClientMatrix(this);
	}
	//������ ����ũ�⸦ ����Ѵ�.
	this->documentVirtualSize = new DocumentVirtualSize(this);

	//Ŭ���̾�Ʈ ������ǥ�� �ʱ⼳���Ѵ�. 
	this->clientLocation = new ClientLocation(this);

	//��ũ���� �����Ѵ�.
	this->scroll = new Scroll(this);
	//��ũ���� ���̰� �Ѵ�.
	this->ShowScrollBar(SB_BOTH);
	//this->ShowScrollBar(SB_VERT);
	//this->ShowScrollBar(SB_HORZ);
	this->EnableScrollBar(SB_BOTH, ESB_DISABLE_BOTH);



	//��Ʈ�� //CONTROL
	//�ڵ��ٹٲ� ��Ʈ���� ����� �ִ´�. 
	Observer* lineWrapControl = new LineWrapControl(this);
	this->AttachObserver(lineWrapControl);

	//���� ����ũ�� ��Ʈ���� ����� �ִ´�. 
	Observer* documentVirtualSizeControl = new DocumentVirtualSizeControl(this);
	this->AttachObserver(documentVirtualSizeControl);

	//��ũ�� ���� ��Ʋ���� ����� �ִ´�.
	Observer* scrollControl = new ScrollInfoControl(this);
	this->AttachObserver(scrollControl);

	//�ڵ� Ŭ���̾�Ʈ ��ġ���� ��Ʈ���� �ִ´�.
	Observer* autoScrollPositionControl = new AutoScrollPositionControl(this);
	this->AttachObserver(autoScrollPositionControl);

	//ĳ�� ��Ʈ���� ����� �ִ´�.
	Observer* caretControl = new CaretControl(this);
	this->AttachObserver(caretControl);

	//����ǥ���� ��Ʈ���� ����� �ִ´�.
	Observer* statusBarControl = new StatusBarControl(this);
	this->AttachObserver(statusBarControl);

	//�ʱ⼳��
	//�� ������ �̵��Ѵ�. 
	lineOrder = this->paper->Move(0); //Last();
	currentLine = this->paper->GetAt(lineOrder);
	currentLine->Move(-1);
	//Ŭ���̾�Ʈ ��ǥ�� �� ������ �����Ѵ�. 
	this->clientLocation->Move(0, lineOrder);

#if 0
	//�����ϱ� �׽�Ʈ
	this->isSelected = TRUE;
	delete this->select;
	this->select = new Select(1, 4, 3, 5);

	this->select->MoveCurrent(-1, 1);
	//�����ϱ� �׽�Ʈ
	string tempString = "�׽�Ʈ �����Դϴ�1234.";
	this->clipboard->Copy(tempString);

	CPrintDialogEx temp(PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_HIDEPRINTTOFILE | PD_NOSELECTION | PD_NOCURRENTPAGE, this);
	temp.DoModal();
	CDC* tempDC;
	tempDC = temp.GetDC();
#endif

	return 0;
}

/*
* �Լ���Ī:OnPaint
* ���:�����찡 ���ŵɶ��� �̺�Ʈ�� �����Ѵ�.
*/
void Notepannel::OnPaint() {
	CPaintDC cPaintDC(this); //�г��� DC�� ���Ѵ�. 
	CBitmap* previousBitmap = 0;
	CString name;
	int height;
	Long bold = 400;
	BOOL italic;
	CFont cFont;
	LOGFONT logFont;
	COLORREF rgbWhite = 0x00FFFFFF;
	CRect rect;

	//ȭ���� ũ�⸦ ���Ѵ�. 
	this->GetClientRect(&rect);

	//���� ���۸� ����
	if (!(this->tempDC.GetSafeHdc())) {
		//ȣȯ�Ǵ� DC�� �����
		this->tempDC.CreateCompatibleDC(&cPaintDC);

		if (this->currentBitmap.GetSafeHandle()) {
			this->currentBitmap.DeleteObject();
		}
		//DC�� ȣȯ�Ǵ� �̹����� �����. 
		this->currentBitmap.CreateCompatibleBitmap(&cPaintDC, rect.Width(), rect.Height());
	}
	//ȣȯ DC�� ȣȯ �̹����� �����ϰ� �����̹����� ��ȯ�޴´�. 
	previousBitmap = this->tempDC.SelectObject(&(this->currentBitmap));



	//������ ���� �ۼ� 
	//Child Ŭ���������� Invalidate�� WM_ERASEBKGND�� �ȸ����Ƿ� ����� ����� ������ �ִ´�. 
	this->tempDC.FillSolidRect(rect, rgbWhite);
	//���� ������ �ý��� �⺻ �۲��� �����´�. 
	cPaintDC.GetCurrentFont()->GetLogFont(&logFont);
	//�ٲ� �۲��� ��Ÿ���� �����´�. //Font�� ���������ڴ� �� ���ش�. 
	name = this->font->name;
	height = this->characterMatrix->height;
	if (this->font->bold == TRUE) {
		bold = 800;
	}
	italic = this->font->italic;
	//�ٲܱ۲ÿ� �°� �۲��� �����Ѵ�. 
	cFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
		italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
		logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);
	//�ٲ� �۲��� �����Ѵ�.
	this->tempDC.SelectObject(&cFont);
	//�湮�� Ŭ�������� ������ ������ �ۼ��Ѵ�. 
	PaintVisitor paintVisitor(this, &(this->tempDC));
	this->paper->Accept(&paintVisitor);

	//������۸� �Ĺݺ�
	//ȣȯDC�� �� ȭ���� �г�DC�� ����Ѵ�. 
	cPaintDC.BitBlt(0, 0, rect.Width(), rect.Height(), &(this->tempDC), 0 , 0, SRCCOPY); //SRCCOPY�����߿�!!!!!
	
	//cPaintDC.BitBlt(0, 0, rect.right, rect.bottom, &tempDC, rect.left , rect.top, SRCCOPY);
	//cPaintDC.BitBlt(0, 0, rect.right / 2, rect.bottom, &tempDC, rect.left , rect.top, BLACKNESS);
	//cPaintDC.BitBlt(0, 0, rect.right, rect.bottom, &tempDC, rect.left, rect.top, SRCAND);
	//cPaintDC.StretchBlt(0, 0, rect.right, rect.bottom, &tempDC, rect.left, rect.top, SRCAND);
	//cPaintDC.SelectObject(&currentBitmap);
	
	//ȣȯDC���� ���� �̹����� �����Ѵ�. 
	tempDC.SelectObject(&previousBitmap);
	//�̹����� �����Ѵ�.
	currentBitmap.DeleteObject();
	//ȣȯDC�� �����Ѵ�. 
	tempDC.DeleteDC();
	
	//ReleaseDC(&this->tempDC);
	
#if 0
	//ȣȯDC Ȯ�ο� �̹��� ���� ���/����
	CImage tempImage;
	CDC* tempDC2 = 0;

	tempImage.Create(rect.Width(), rect.Height(), cPaintDC.GetDeviceCaps(BITSPIXEL));
	tempDC2 = CDC::FromHandle(tempImage.GetDC());
	tempDC2->BitBlt(0, 0, rect.right, rect.bottom, &cPaintDC, rect.left, rect.top, SRCCOPY);
	tempImage.ReleaseDC();
	tempImage.Save(TEXT("AAAAAAAAA.png"), Gdiplus::ImageFormatPNG);
#endif
}



/*
* �Լ���Ī:OnChar
* ���:�̱۹���Ʈ ���ڸ� �Է��������� �̺�Ʈ�� �����Ѵ�.
*/
void Notepannel::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CommandCreator commandCreator(this);
	Command* command = NULL;

	//GlyphCreater glyphCreater;
	//Glyph* line = NULL;
	//Glyph* currentLine = NULL;
	//Glyph* character = NULL;
	//Glyph* newLine = NULL;
	//Long lineOrder = -1;
	//Long charIndex = -2;
	//Long last = -2;
	//Long i = 0;
	//char charArray[2];
	//charArray[0] = nChar;
	//charArray[1] = '\0';

	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);

	KeyActionCreator keyActionCreator(this);
	KeyAction* keyAction = NULL;

	if (!(ctrlKeyState & 0x8000) && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != 15 && nChar != 19) {

		command = commandCreator.Create(nChar, nRepCnt, nFlags);
		if (command != NULL) {
			command->Execute();
		}
		this->macroCommand->Add(command, 1);

#if 0
		//���̿��� ���� ���� ��ġ�� �����´�.
		lineOrder = this->paper->GetCurrent();
		//���̿��� ���� ��ġ�� �ִ� ���� �����´�.
		currentLine = this->paper->GetAt(lineOrder);

		switch (nChar) {
		case VK_RETURN: //����Ű�� ��������
			//�ٿ��� ���� ��ġ�� �����´�.
			charIndex = currentLine->GetCurrent();
			//�� ���� �����.
			newLine = glyphCreater.Create("\r\n");
			last = currentLine->Last();
			charIndex = currentLine->Move(charIndex);
			while (i < (last - charIndex)) {//���� ���� ������ �ݺ��Ѵ�.
				//���� ���� ���� ��ġ�� ���� ������ �ܾ �����´�.
				character = currentLine->GetAt(charIndex + 1);
				//���� �ܾ �� �ٿ� �Űܾ���.
				newLine->Add(character->Clone());
				//�Űܾ� �ܾ �����.
				currentLine->Remove(charIndex + 1);
				i++;
			}
			//���̿� �Űܾ� ���� ���� ��ġ�� ������ ���´�.
			lineOrder = this->paper->Add(newLine);
			//���� �ٿ��� �� ������ �̵��Ѵ�.
			currentLine = this->paper->GetAt(lineOrder);
			currentLine->First();
			break;
		case VK_BACK: // �齺���̽��� Ű�׼ǿ��� ������ ���߱⿡ ���Ƶд�. 
			break;
			//case 0x01:
				//break;
			//case 0x03:
				//break;

		//case VK_F16: //ctrl backspace�� ���
		//	break;
		case VK_ESCAPE: //esc�� ���Ƶд�.
			break;
			//case 0x41:
				//break;
		default: //�̱۹���Ʈ ���ڸ� �Է�������


			//�� ���� ���
			character = glyphCreater.Create(charArray);
			currentLine->Add(character);
			//line = this->paper->GetAt(this->paper->GetCurrent());
			break;
		}
#endif

		//������ ������ ����Ǿ��ٴ� �÷��׸� ����. 
		this->documentUploaded = TRUE;
		//�ڵ��̵� üũ �÷��׸� ����. 
		this->clientMoveCheck = TRUE;

		//������ ��Ʈ�� ȣ��
		this->Notify();

		//OnPaint�� ��ȣ���ϱ� ���� Invalidate�Լ� �̰��� true�� �ϸ� ��ü�� �����ٰ� �ٽ� �Է��ϰԵȴ�. 
		//Invalidate�� FALSE�� �ϸ� ������ �۵������� ������� �����̶� �׳� TRUE�� �ߴ�. 
		this->Invalidate(TRUE);

		//����� ������ ����Ǿ��ٴ� �÷��׸� ����.
		this->hasChanged = TRUE;

		//�������� ������ �����Ѵ�.
		CString windowTitle;
		windowTitle.Format("*%s - Windows �޸���", this->document->GetName().c_str());
		this->notepad->SetWindowText(windowTitle);

		//ĳ���� ���δ�.
		this->caret->ShowCaret();
	}
}


/*
* �Լ���Ī:OnStartComposition
* ���:�������Ʈ ������ �Է½����������� �̺�Ʈ�� �����Ѵ�
*/
LRESULT Notepannel::OnStartComposition(WPARAM wParam, LPARAM lParam) { // �������Ʈ ���ڸ� �Է¹޾�����

	return 0;
}

/*
* �Լ���Ī:OnImeComposition
* ���:�������Ʈ ������ ���� �� �϶��� �̺�Ʈ�� �����Ѵ�.
*/
LRESULT Notepannel::OnImeComposition(WPARAM wParam, LPARAM lParam) { // �������Ʈ ���ڸ� �Է����϶�
	GlyphCreater glyphCreater;
	Glyph* line = NULL;
	Glyph* character = NULL;
	char letter[3];

	CommandCreator commandCreator(this);
	Command* command = NULL;

	if (this->isSelected == TRUE) { //���õǾ�����
			//�����Ѵ�. 
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		if (command != NULL) {
			command->Execute();
			this->macroCommand->Add(command);
		}
	}

	//�Էµ� ���ڸ� �д´�.
	letter[0] = HIBYTE(wParam);
	letter[1] = LOBYTE(wParam);
	letter[2] = '\0';

	//���� ���� �����´� 
	line = this->paper->GetAt(this->paper->GetCurrent());

	//�������Ʈ �Է����̸� ���� ���ڸ� �����. 
	if (this->isComposing == TRUE) {
		line->Remove(line->GetCurrent());
	}

	//���� ���ڰ� ������ ���� ��ġ�� �������Ʈ ���ڸ� ���´�. 
	if (letter[0] != '\0') {
		character = glyphCreater.Create(letter);
		line->Add(character);
		//�÷��׸� �ø���. 
		this->isComposing = TRUE;
	}
	else { //���� ���ڰ� ������ �÷��׸� ������.
		this->isComposing = FALSE;
	}
	//�÷��׸� �ø���. 
	//this->isComposing = TRUE;

	//������ ����Ǿ��ٴ� �÷��׸� ����.
	this->hasChanged = TRUE;
	//�������� ������ �����Ѵ�.
	CString windowTitle;
	windowTitle.Format("*%s - Windows �޸���", this->document->GetName().c_str());
	this->notepad->SetWindowText(windowTitle);

	//������ ������ ����Ǿ��ٴ� �÷��׸� ����. 
	this->documentUploaded = TRUE;
	//��ũ�� ��ġ�� Ȯ���϶�� �÷��׸� ����. 
	this->clientMoveCheck = TRUE;

	//ĳ�� ��Ʈ�� ȣ��
	this->Notify();

	//WM_PAINT�޼����� ȣ���Ѵ�. 
	this->Invalidate(TRUE);

	//ĳ���� ����Ѵ�.
	this->caret->ShowCaret();

	return DefWindowProc(WM_IME_COMPOSITION, wParam, lParam); // �̺κп� ���� ���� ����
}

/*
* �Լ���Ī:OnImeChar
* ���:�������Ʈ ������ ����� �ϼ��Ǿ������� �̺�Ʈ�� �����Ѵ�.
*/
LRESULT Notepannel::OnImeChar(WPARAM wParam, LPARAM lParam) { //�������Ʈ ���ڸ� �ϼ�������
	CommandCreator commandCreator(this);
	Command* command = NULL;
	GlyphCreater glyphCreater;
	Glyph* line = NULL;
	Glyph* character = NULL;
	//char letter[3];

	//�÷��׸� ������. 
	this->isComposing = FALSE;



#if 0
	//�Էµ� ���ڸ� �д´�.
	letter[0] = HIBYTE(wParam);
	letter[1] = LOBYTE(wParam);
	letter[2] = '\0';
#endif
	//���� ���ڸ� �����. 
	line = this->paper->GetAt(this->paper->GetCurrent());
	line->Remove(line->GetCurrent());
#if 0
	//�ۿ� ���ڸ� ���´�. 
	character = glyphCreater.Create(letter);
	line->Add(character);
#endif
	command = commandCreator.Create(wParam, lParam);
	if (command != NULL) {
		command->Execute();
	}
	this->macroCommand->Add(command, 1);

	//������ ����Ǿ��ٴ� �÷��׸� ����.
	this->hasChanged = TRUE;

	//�������� ������ �����Ѵ�.
	CString windowTitle;
	windowTitle.Format("*%s - Windows �޸���", this->document->GetName().c_str());
	this->notepad->SetWindowText(windowTitle);

	//������ ������ ����Ǿ��ٴ� �÷��׸� ����. 
	this->documentUploaded = TRUE;
	//ĳ�� ��Ʈ�� ȣ��
	this->Notify();

	//WM_PAINT�޼����� ȣ���Ѵ�. 
	this->Invalidate(TRUE);

	//ĳ���� ����Ѵ�.
	this->caret->ShowCaret();

	return 0;
}

/*
* �Լ���Ī:OnSetFocus
* ���:�Է���Ŀ���� ��������� ����� �����Ѵ�.
*/
void Notepannel::OnSetFocus(CWnd* pOldWnd) {

	//ĳ���� ���̰� �Ѵ�. 
	this->caret->ShowCaret();
	this->Notify();

}

/*
* �Լ���Ī:OnKillFocus
* ���:�Է���Ŀ���� �б� ������ ȣ���ϴ� �Լ�
*/
void Notepannel::OnKillFocus(CWnd* pNewWnd) {

	//ĳ���� �Ⱥ��̰� �Ѵ�. 
	this->caret->HideCaret();
}

/*
* �Լ���Ī:OnKeyDown
* ���:��ý���Ű�� ������ ȣ��Ǵ� �Լ�
*/
void Notepannel::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	KeyActionCreator keyActionCreator(this);
	KeyAction* keyAction = NULL;

	keyAction = keyActionCreator.Create(nChar, nRepCnt, nFlags);
	if (keyAction != NULL) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
	}
	delete keyAction;
}

/*
* �Լ���Ī:OnKeyUp
* ���:��ý���Ű�� �����ɶ� ȣ��Ǵ� �Լ�
*/
void Notepannel::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_SHIFT) {
		this->isSelecting = FALSE;
	}
}




/*
* �Լ���Ī:OnLButtonDown
* ���: ���콺 ���� ��ư�� Ŭ���������� �̺�Ʈ�� �����Ѵ�.
*/
void Notepannel::OnLButtonDown(UINT nFlags, CPoint point) {//Ŭ���� ��ġ�� �д´�.
	Glyph* currentLine = NULL;
	Long lineOrder;
	Long charIndex;
	int previousSelectXIndex = this->select->currentXIndex;
	int previousSelectLineOrder = this->select->currentLineOrder;
	SHORT shiftKeyState = GetKeyState(VK_SHIFT);

	//���콺Ŭ ĸ���Ѵ�. 
	this->SetCapture();

	//Ŭ���� ������ġ�� ������ ���� ã�´�.
	lineOrder = this->characterMatrix->FindNearHeightPosition(point.y);
	//Ŭ���̾�Ʈ ��ġ�� �ݿ��Ѵ�.
	lineOrder = lineOrder + this->clientLocation->lineOrder;
	//ã�� �ٷ� �̵��Ѵ�.
	lineOrder = this->paper->Move(lineOrder);
	//ã�� ���� �����´�.
	currentLine = this->paper->GetAt(lineOrder);
	//ã�� �ٿ��� ������ġ�� ������ �ܾ ã�´�.
	point.x = point.x + this->clientLocation->x;
	charIndex = this->characterMatrix->FindNearWidthPosition(currentLine, point.x);
	//ã�� �ܾ�� �̵��Ѵ�.
	currentLine->Move(charIndex);

	if (this->isSelecting == FALSE) { //shiftŰ�� Ŭ������ �ʾ�����
		//���� Ŭ������ �Ҵ������Ѵ�.
		delete this->select;
		//������ ���� ��ġ�� �����ϱ��� ���� ��ġ�� ������ ���� Ŭ������ �����. 
		this->select = new Select(this, charIndex, lineOrder, charIndex, lineOrder);
	}
	else if ((shiftKeyState & 0x8000)) { //shiftŰ�� ������ ������
		//�����ϱ��� ���� ��ġ�� �����Ѵ�.
		this->select->MoveCurrent(charIndex, lineOrder);
	}
	//Ŭ���ߴٴ� �÷��׸� ����.
	this->hasClicked = TRUE;
	//������Ʈ�� ȣ���Ѵ�. 
	this->clientMoveCheck = TRUE;
	this->Notify();
	//Ŭ���̾�Ʈ�� �����Ѵ�.
	this->Invalidate(FALSE);
	//ĳ���� ���̰� �Ѵ�.
	this->caret->ShowCaret();
}

/*
* �Լ���Ī:OnLButtonUp
* ���: ���콺 ���� ��ư�� �������� �̺�Ʈ�� �����Ѵ�.
*/
void Notepannel::OnLButtonUp(UINT nFlags, CPoint point) {
	if (nFlags != MK_SHIFT) { //shiftŰ�� ������ �ʾ�����
		//�������̶�� ǥ�ø� ������.
		this->isSelecting = FALSE;
	}
	//Ŭ���ߴٴ� �÷��׸� ������.
	this->hasClicked = FALSE;

	//���콺�� ĸ�ĸ� �����Ѵ�.
	ReleaseCapture();
}

/*
* �Լ���Ī:OnMouseMove
* ���: ���콺 ��ư�� �� ���� �̺�Ʈ�� �����Ѵ�.
*/
void Notepannel::OnMouseMove(UINT nFlags, CPoint point) {
	VerticalScrollAction* vertical = NULL;
	VerticalScrollActionCreator verticalCreator(this);
	HorizontalScrollAction* horizontal = NULL;
	HorizontalScrollActionCreator horizontalCreator(this);
	Glyph* currentLine = NULL;
	Long lineOrder;
	Long charIndex;
	Long previousLineOrder;
	Long previousCharIndex;
	int clientYMoveLocation;
	int clientXMoveLocation;

	lineOrder = this->paper->GetCurrent();
	currentLine = this->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	previousLineOrder = lineOrder;
	previousCharIndex = charIndex;

	CPoint scrollPoint = point;

	if (nFlags == MK_LBUTTON && this->hasClicked == TRUE && this->hasLoaded == FALSE && this->hasOnSized == FALSE) { //���콺�� Ŭ�����̸�
		//Ŭ���� ������ġ�� ������ ���� ã�´�.
		lineOrder = this->characterMatrix->FindNearHeightPosition(point.y);
		//Ŭ���̾�Ʈ ��ġ�� �ݿ��Ѵ�.
		lineOrder = lineOrder + this->clientLocation->lineOrder;
		//ã�� �ٷ� �̵��Ѵ�.
		lineOrder = this->paper->Move(lineOrder);
		//ã�� ���� �����´�.
		currentLine = this->paper->GetAt(lineOrder);
		//ã�� �ٿ��� ������ġ�� ������ �ܾ ã�´�.
		point.x = point.x + this->clientLocation->x;
		charIndex = this->characterMatrix->FindNearWidthPosition(currentLine, point.x);
		//ã�� �ܾ�� �̵��Ѵ�.
		charIndex = currentLine->Move(charIndex);

		//�����ϱ��� ������ġ�� �����Ѵ�
		this->select->MoveCurrent(charIndex, lineOrder);


		//Ŭ���̾�Ʈ�� �̵� ��輱�� ����Ѵ�.
		clientYMoveLocation = (this->clientMatrix->lineNumberInPage - 1) * this->characterMatrix->height;
		clientXMoveLocation = this->clientMatrix->width - 15;
		if (scrollPoint.y < 0) { //Ŀ���� Y��ġ�� �����̸�
			//���� ���� �̵��Ѵ�.
			vertical = verticalCreator.Create(SB_LINEUP, 0, 0);
			vertical->OnVScroll(0, 0, 0);
		}
		else if (scrollPoint.y > clientYMoveLocation) { //Ŀ���� Y��ġ�� Ŭ���̾�Ʈ �̵���� �Ʒ��̸�
			//���� �Ʒ��� �̵��Ѵ�.
			vertical = verticalCreator.Create(SB_LINEDOWN, 0, 0);
			vertical->OnVScroll(0, 0, 0);
		}

		if (scrollPoint.x < 0) { //Ŀ���� X��ġ�� �����̸�
			//�������� �� ������ ��ũ���Ѵ�.
			horizontal = horizontalCreator.Create(SB_LINELEFT, 0, 0);
			horizontal->OnHScroll(0, 0, 0);
		}
		else if (scrollPoint.x > clientXMoveLocation) { //Ŀ���� X��ġ�� Ŭ���̾�Ʈ �̵���� �������̸�
			//���������� �� ������ ��ũ���Ѵ�.
			horizontal = horizontalCreator.Create(SB_LINERIGHT, 0, 0);
			horizontal->OnHScroll(0, 0, 0);
		}
		//�Ҵ������Ѵ�.
		delete vertical;
		delete horizontal;

		//������Ʈ�� �Ѵ�.
		this->Notify();
		if (this->paper->IsNotEqual(previousLineOrder, previousCharIndex)) { //���콺�� ��� ���õǾ����� 
			//Ŭ���̾�Ʈ�� �����Ѵ�
			this->Invalidate(FALSE);
		}
		//ĳ���� ���δ�.
		this->caret->ShowCaret();
	}
	this->hasLoaded = FALSE;
	this->hasOnSized = FALSE;

}

/*
* �Լ���Ī:OnLButtonDblClk
* ���:���콺 ���� ��ư�� ����Ŭ������ ���� �̺�Ʈ�� �����Ѵ�.
*/
void Notepannel::OnLButtonDblClk(UINT nFlags, CPoint point) {
	Glyph* currentLine = NULL;
	int lineOrder = -1;
	int charIndex = -2;
	int previousSelectXIndex = this->select->previousXIndex;
	int previousSelectLineOrder = this->select->previousLineOrder;
	int previousCharIndex;

	lineOrder = this->paper->GetCurrent();
	currentLine = this->paper->GetAt(lineOrder);
	charIndex = currentLine->GetCurrent();
	//���� ��ġ�� ����Ѵ�. 
	previousCharIndex = charIndex;
	//���� �ٿ��� ���� �ܾ�� �̵��Ѵ�.
	charIndex = currentLine->PreviousWord();

	if (this->isSelecting == FALSE) {//���� ���� �ƴϸ�
		//�����ϱ� Ŭ������ �Ҵ������Ѵ�.
		delete this->select;
		//�����ϱ� Ŭ�������� ���� ��ġ�� ������ġ�� �����ؼ� �Ҵ��Ѵ�.
		this->select = new Select(this, charIndex, lineOrder, charIndex, lineOrder);
		//���� �ܾ�� �̵��Ѵ�.
		charIndex = currentLine->NextWord();
		//�����ϱ⿡�� ������ġ�� �����Ѵ�.
		this->select->MoveCurrent(charIndex, lineOrder);

	}
	else { //���� ���̸�
		if (previousSelectLineOrder > lineOrder) {//�����ϱ��� ��ġ�� ���� ��ġ���� ���̸� ������ġ(�ܾ��)�� �̵��Ѵ�.
			this->select->MoveCurrent(charIndex, lineOrder);
		}
		else if (previousSelectLineOrder == lineOrder && previousSelectXIndex > previousCharIndex) {
			this->select->MoveCurrent(charIndex, lineOrder);
		}
		else {//������ ��ġ�� ���� ��ġ�� ���̸�
			//�����ܾ�� �̵��Ѵ�.
			charIndex = currentLine->NextWord();
			//�����ϱ⿡�� �̵��Ѵ�.
			this->select->MoveCurrent(charIndex, lineOrder);
		}

	}
	//������Ʈ�� �Ѵ�.
	this->Notify();
	//Ŭ���̾�Ʈ�� �����Ѵ�
	this->Invalidate(TRUE);
	//ĳ���� ���δ�.
	this->caret->ShowCaret();
}


/*
* �Լ���Ī:OnMouseWheel
* ���:���콺 ���� �������� �̺�Ʈ
*/
BOOL Notepannel::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	MouseWheelActionCreator mouseWheelActionCreator(this);
	MouseWheelAction* mouseWheelAction = NULL;
	BOOL ret = FALSE;

	mouseWheelAction = mouseWheelActionCreator.Create(nFlags, zDelta, pt);
	if (mouseWheelAction != NULL) {
		ret = mouseWheelAction->OnMouseWheel(nFlags, zDelta, pt);
	}
	delete mouseWheelAction;

	return ret;
}

/*
* �Լ���Ī:OnVScroll
* ���:���� ��ũ���� �̺�Ʈ�� �����ϴ� �Լ�
*/
void Notepannel::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) { //��ũ���� ��ġ�� �д´�.
	VerticalScrollAction* verticalScrollAction = 0;
	VerticalScrollActionCreator verticalScrollActionCreator(this);

	verticalScrollAction = verticalScrollActionCreator.Create(nSBCode, nPos, pScrollBar);

	if (verticalScrollAction != NULL) {
		verticalScrollAction->OnVScroll(nSBCode, nPos, pScrollBar);
	}

	delete verticalScrollAction;
}

/*
* �Լ���Ī:OnHScroll
* ���:���� ��ũ���� �̺�Ʈ�� �����ϴ� �Լ�
*/
void Notepannel::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) { //��ũ���� ��ġ�� �д´�.
	HorizontalScrollAction* horizontalScrollAction = 0;
	HorizontalScrollActionCreator horizontalScrollActionCreator(this);

	horizontalScrollAction = horizontalScrollActionCreator.Create(nSBCode, nPos, pScrollBar);

	if (horizontalScrollAction != NULL) {
		horizontalScrollAction->OnHScroll(nSBCode, nPos, pScrollBar);
	}

	delete horizontalScrollAction;
}

/*
* �Լ���Ī:OnSize
* ���:������ ũ�Ⱑ �ִ�ȭ�ɶ�, �ִ�ȭ���� �Ϲ�ȭ �ɶ��� �̺�Ʈ�� ó���Ѵ�.
*/
void Notepannel::OnSize(UINT nType, int cx, int cy) {
	if (this->isUpdating == FALSE && this->notepad->nType == SIZE_MAXIMIZED) { //�ִ�ȭ ��ư�� Ŭ������ ��
		this->OnSizing(0, 0);

		this->isMaximixed = TRUE;
	}
	else if (this->isUpdating == FALSE && this->notepad->nType == SIZE_RESTORED) { // && this->isMaximixed == TRUE) { //�ִ�ȭ���¿��� �Ϲ�ȭ �ɶ�
		this->OnSizing(0, 0);


		this->isMaximixed = FALSE;
	}
	//else if(this->isUpdating == FALSE && )
	//this->notepad->statusBarCtrl.ShowWindow(SW_SHOW);

}

/*
* �Լ���Ī:OnSizing
* ���:����ڰ� ������ ũ�⸦ �����Ҷ��� �̺�Ʈ�� �����Ѵ�.
*/
void Notepannel::OnSizing(UINT nSide, LPRECT lpRect) {
	Glyph* currentLine = NULL;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long lineLocation = -1;
	Long charLocation = -2;

	WINDOWINFO windowInfo{ 0, };
	CRect windowRect; 
	CRect pannelRect;

	UINT statusBarState = -1;

	if (this->notepad->hasStarted == FALSE &&this->isUpdating == FALSE && this->isScrollSetting == FALSE) {
		//Ŭ���̾�Ʈ�� ũ�� Ŭ������ ���� �������ش�.
		if (this->clientMatrix != NULL) {
			delete this->clientMatrix;
		}
		this->clientMatrix = new ClientMatrix(this);
		//Ŭ���̾�Ʈ�� ��ġ�� �д´�.
		this->notepad->GetWindowInfo(&windowInfo);
		windowRect = windowInfo.rcClient;
		//�޴����� ����ǥ���� �׸��� üũ�Ǿ����� Ȯ���Ѵ�. 
		statusBarState = this->notepad->cMenu.GetMenuState(IDM_FORMAT_STATUSBAR, MF_BYCOMMAND);
		if (statusBarState == MF_CHECKED) { //����ǥ���� �޴��� üũ�Ǿ�������
			//����ǥ������ �����Ѵ�.
			this->notepad->statusBar->UpdateStatusBar();

			//Ŭ���̾�Ʈ ũ�⿡ �°� �г� ũ�⸦ �����Ѵ�.
			pannelRect = { 0,0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top - this->notepad->statusBar->heigth };
			this->MoveWindow(&pannelRect);
		}
		else if (statusBarState == MF_UNCHECKED) { //����ǥ���� �޴��� üũ�Ǿ����� ������
			//Ŭ���̾�Ʈ ũ�⿡ �°� �г� ũ�⸦ �����Ѵ�.
			pannelRect = { 0,0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };
			this->MoveWindow(&pannelRect);
		}
		//�г��� ��Ŀ�� �Ѵ�. 
		this->SetFocus();


		this->tempDC.DeleteDC();
		this->currentBitmap.DeleteObject();

		//������Ʈ �Լ��� ȣ�����ش�
		this->documentUploaded = TRUE;
		//this->clientMoveCheck = TRUE;
		this->isUpdating = TRUE;
		this->Notify();
		//Ŭ���̾�Ʈ�� �����Ѵ�.
		this->Invalidate(TRUE);
		//������Ʈ�� �������� ǥ���Ѵ�.
		this->isUpdating = FALSE;
		//ĳ���� ǥ���Ѵ�.
		this->ShowCaret();

		//â ũ�Ⱑ �ٲ���ٴ� �÷��׸� �ø���.
		this->hasOnSized = TRUE;
	}
}

/*
* �Լ���Ī:OnFindReplace
* ���:ã�� �ٲٱ� ��ȭ������ �̺�Ʈ�� �����ϴ� ���
*/
LONG Notepannel::OnFindReplace(WPARAM wParam, LPARAM lParam) {
	Glyph* currentLine = 0;
	Glyph* clone = 0;
	Long lineOrder = -1;
	Long charIndex = -2;
	Long currentLineOrder = -1;
	Long currentCharIndex = -2;
	Long count;
	Long indexNear;
	Long repete;
	Long i = 0;
	//�÷���
	BOOL replaceAll;
	BOOL replaceCurrent;
	BOOL findNext;
	BOOL isTerminating;
	//ù �˻��� ���� ����
	GlyphCreater glyphCreater;
	Glyph* tempPaper;

	//��ã���� ��
	CString message;
	//�ڵ�����
	CommandCreator commandCreater(this);
	Command* command = NULL;
	UINT lineWrapState = -1;
	lineWrapState = this->notepad->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);


	//���ִ� ������ ���´�. (Finder)
	delete this->finder;
	this->finder = new Finder(this, wParam, lParam);
	delete this->replacer;
	this->replacer = new Replacer(this, wParam, lParam);


	//AfxMessageBox(_T(this->finder->find.c_str())); //ã�� ���� 

	//�÷���
	replaceAll = this->replacer->replaceAll;
	replaceCurrent = this->replacer->replaceCurrent;
	findNext = this->finder->findNext;
	isTerminating = this->finder->isTerminating;

	//���� �޼����� �����. 
	message.Format("'%s'��(��) ã�� �� �����ϴ�.", this->finder->find.c_str());

	//�ڵ������� �Ǿ������� ��������Ѵ�. 
	if (isTerminating == FALSE && lineWrapState == MF_CHECKED) {
		command = commandCreater.Create(IDM_FORMAT_LINEWRAP);
		command->UnExecute();
		delete command;
	}

	if (findNext == TRUE) {//���� ã�⸦ Ŭ���߰ų� �˻� ����� ���� ���¿��� �ٲٱ� ��ư�� Ŭ���ߴµ�

		//���̿��� ���� ��ġ�� �д´�.
		lineOrder = this->paper->GetCurrent();
		currentLine = this->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();
		//���� ��ġ�� ����Ѵ�. 
		currentLineOrder = lineOrder;
		currentCharIndex = charIndex;
		//�Է°��� �°� ã�´�.
		count = this->finder->Find();

		if (count <= 0) {//ã�� ������ ������ �޽����� ����.
			//������Ʈ�� �Ѵ�.(��ġ)
			this->clientMoveCheck = TRUE;
			this->documentUploaded = TRUE;
			this->Notify();
			//Ŭ���̾�Ʈ�� �����Ѵ�.
			this->Invalidate(TRUE);

			AfxMessageBox(message);
			//���� ��ġ�� �̵��Ѵ�. 
			lineOrder = this->paper->Move(currentLineOrder);
			currentLine = this->paper->GetAt(lineOrder);
			currentLine->Move(currentCharIndex);
		}
		else if (count > 0) {//������ ã������
			//��� ���� ���� ��ġ ��ó�� ã�´�. 
			indexNear = this->finder->SearchNear(currentLineOrder, currentCharIndex);
			if (indexNear < count && indexNear >= 0) { //��ó ���� ������
				this->finder->SelectResult(indexNear);
			}
			else { //ã�� �������� �޽����� ����Ѵ�. 
				//������Ʈ�� �Ѵ�.(��ġ)
				this->clientMoveCheck = TRUE;
				this->documentUploaded = TRUE;
				this->Notify();
				//Ŭ���̾�Ʈ�� �����Ѵ�.
				this->Invalidate(TRUE);

				AfxMessageBox(message);
				//���� ��ġ�� �̵��Ѵ�. 
				lineOrder = this->paper->Move(currentLineOrder);
				currentLine = this->paper->GetAt(lineOrder);
				currentLine->Move(currentCharIndex);
			}
		}
		//ĳ���� �����.
		this->caret->HideCaret();
	}
	else if (replaceCurrent == TRUE) { //�˻������ �������� �� �ٲٱ� ��ư�� Ŭ��������
		
		//���� �Էµ� �˻�� ���̷� ġȯ�Ѵ�.
		tempPaper = glyphCreater.Create((string)(CFindReplaceDialog::GetNotifier(lParam)->GetFindString()));
		
		if (this->isSelected == TRUE && this->resultFound->paperToFind != 0 && this->select->IsEqual(this->resultFound->paperToFind) == TRUE) {
			//�̹� �˻��� �ѹ� ������
			//���� ���õ� ������ �ٲ۴�. 
			this->replacer->ReplaceCurrent();
		}
		else if (this->isSelected == TRUE && this->resultFound->paperToFind == 0 && this->select->IsEqual(tempPaper) == TRUE) {
			//ù �˻��̸�
			//���� ���õ� ������ �ٲ۴�. 
			this->replacer->ReplaceCurrent();
		}
		//���̸� �Ҵ������Ѵ�. 
		delete tempPaper;


		//���� ��ġ�� ����Ѵ�. 
		lineOrder = this->paper->GetCurrent();
		currentLine = this->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();

		//���� ��ġ�� �������� �˻��� �ѹ� �� �Ѵ�. 
		count = this->finder->Find();
		//����� ������ ��ó�� ã�� ������ �ִ��� Ȯ���Ѵ�. 
		if (count > 0) {
			//��� ���� ���� ��ġ ��ó�� ã�´�. 

			indexNear = this->finder->SearchNear(lineOrder, charIndex);
			if (indexNear < count && indexNear >= 0) { //��ó ���� ������
				this->finder->SelectResult(indexNear);
			}
			else { //ã�� �������� �޽����� ����Ѵ�. 
				//������Ʈ�� �Ѵ�.(��ġ)
				this->clientMoveCheck = TRUE;
				this->documentUploaded = TRUE;
				this->Notify();
				//Ŭ���̾�Ʈ�� �����Ѵ�.
				this->Invalidate(TRUE);

				AfxMessageBox(message);
				//���� ��ġ�� �̵��Ѵ�. 
				lineOrder = this->paper->Move(lineOrder);
				currentLine = this->paper->GetAt(lineOrder);
				currentLine->Move(charIndex);
			}
		}
		else if (count <= 0) {//ã�� ������ ������ �޽����� ����.
			//������Ʈ�� �Ѵ�.(��ġ)
			this->clientMoveCheck = TRUE;
			this->documentUploaded = TRUE;
			this->Notify();
			//Ŭ���̾�Ʈ�� �����Ѵ�.
			this->Invalidate(TRUE);

			AfxMessageBox(message);
			//���� ��ġ�� �̵��Ѵ�. 
			lineOrder = this->paper->Move(lineOrder);
			currentLine = this->paper->GetAt(lineOrder);
			currentLine->Move(charIndex);
		}
		//ĳ���� �����.
		this->caret->HideCaret();
	}
	else if (replaceAll == TRUE) { //��� �ٲٱ� ��ư�� Ŭ��������
		//�˻�� ã�´�.
		count = this->finder->Find();
		if (count > 0) {//������ ã������
			//�� ó������ �̵��Ѵ�. 
			lineOrder = this->paper->First();
			currentLine = this->paper->GetAt(lineOrder);
			charIndex = currentLine->First();
			//���� ��ġ�� ã�´�. 
			indexNear = this->finder->SearchNear(lineOrder, charIndex);
			repete = count;
			while (indexNear >= 0 && indexNear < count && i < repete) { //��ó ���� ������
				//ã�� ����� �����Ѵ�. 
				this->finder->SelectResult(indexNear);
				//���� ��ġ�� ����Ѵ�. 
				lineOrder = this->select->endLineOrder;
				charIndex = this->select->endXIndex;
				//���� ���õ� ������ �ٲ۴�. 
				this->replacer->ReplaceCurrent();
				this->macroCommand->FlagDown();
				//�˻�� ã�´�.
				count = this->finder->Find();
				if (count > 0) {
					//ã���� ���� ��ġ�� ã�´�. 
					indexNear = this->finder->SearchNear(lineOrder, charIndex);
				}
				else {
					//ã�� ���ϸ� 
					indexNear = -1;
				}
				i++;
			}
			this->macroCommand->FlagUp();
		}
		//ĳ���� �����.
		this->caret->HideCaret();
	}
	else if (isTerminating == TRUE) {//ã�� �ٲٱ� ��ȭ���ڸ� �ݾ����� 
		//ĳ���� ǥ���Ѵ�.
		this->caret->ShowCaret();
	}
	//������Ʈ�� �Ѵ�.(��ġ)
	this->clientMoveCheck = TRUE;
	this->documentUploaded = TRUE;
	this->Notify();
	//Ŭ���̾�Ʈ�� �����Ѵ�.
	this->Invalidate(TRUE);

	return 0;
}



#if 0
#endif




LRESULT CALLBACK SaveMessageBoxProc(int nCode, WPARAM wParam, LPARAM lParam) {
	HWND hChildWnd;

	CString msg;

	if (nCode == HCBT_ACTIVATE) {
		hChildWnd = (HWND)wParam;
		if (GetDlgItem(hChildWnd, IDYES) != NULL) {
			msg = "����(&S)";
			SetWindowText(GetDlgItem(hChildWnd, IDYES), msg);
		}

		if (GetDlgItem(hChildWnd, IDNO) != NULL) {
			msg = "���� �� ��(&N)";
			SetWindowText(GetDlgItem(hChildWnd, IDNO), msg);
		}
		UnhookWindowsHookEx(hSaveMessageBoxHook);
	}

	return 0;
}




int SaveMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT nType) {
	hSaveMessageBoxHook = SetWindowsHookEx(WH_CBT, &SaveMessageBoxProc, 0, GetCurrentThreadId());

	return MessageBox(hWnd, lpText, lpCaption, nType);
}
