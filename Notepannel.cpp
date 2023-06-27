//Notepannel.cpp
/*
* 파일명칭:Notepannel.cpp
* 기능:메모장의 클라이언트 영역에 출력을 하는 패널
* 작성자:허지욱
* 작성일자:2022/12/20
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

//#include <atlimage.h> // CImage용

#include <string>
using namespace std;

//옵저버 클래스
#include "LineWrapControl.h"
#include "DocumentVirtualSizeControl.h"
#include "ScrollInfoControl.h"
#include "CaretControl.h"
#include "AutoScrollPositionControl.h"
#include "StatusBarControl.h"

//전역변수 선언
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
* 함수명칭:Notepannel
* 기능:생성자
*/
Notepannel::Notepannel(Notepad* notepad) :notepad(notepad) {
	//관계 클래스를 초기화한다.
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

	//속성을 초기화한다.
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
* 함수명칭:~Notepannel
* 기능:소멸자
*/
Notepannel::~Notepannel() {
	Observer* observer = 0;


	//관계 클래스의 메모리를 할당해제한다.
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


	//옵저버 클래스들을 할당해제한다.
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
* 함수명칭:OnCreate
* 기능:윈도우가 생성될때의 이벤트를 실행한다.
*/
int Notepannel::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct); //오버라이딩

	GlyphCreater glyphCreater;
	Glyph* line = NULL;
	Glyph* currentLine = 0;
	Long lineOrder = -1;
	Long indexLine = -1;

//#if 0
	//종이를 만든다.
	this->paper = glyphCreater.Create("");
	//종이에 줄을 삽입한다.
	line = glyphCreater.Create("\r\n");
	indexLine = this->paper->Add(line);

	//문서를 만든다. 
	this->document = new Document();
	//플래그로 저장되지 않음을 표시한다. 
	this->isSaved = FALSE; //->notepad->SetWindowText(windowTitle);
	//문서가 변경되지 않았음을 표시한다.
	this->documentUploaded = FALSE;
//#endif

#if 0
	//테스트용 문서 //H://내 드라이브//(((Notepad)))/기능 테스트용
	//string tempPath = "H://내 드라이브//(((Notepad)))/기능 테스트용";//데스크탑 경로
	string tempPath = "G://내 드라이브//(((Notepad)))//기능 테스트용"; //노트북 경로
	string tempName = "가나다라마바사";
	this->document = new Document(tempPath, tempName);
	this->paper = this->document->Load();
	this->isSaved = TRUE;
	this->documentUploaded = FALSE;
#endif


	CString windowTitle;
	windowTitle.Format("%s - Windows 메모장", this->document->GetName().c_str());
	this->notepad->SetWindowText(windowTitle);

	//플래그로 변경되지 않음을 표시한다. 
	this->hasChanged = FALSE;

	//글꼴을 만든다 //이건 기본 글꼴을 만드는 과정
	//this->GetDC()->GetCurrentFont()->GetLogFont(&logFont);
	this->font = new Font("돋움", 36);
	//글꼴을 바꾼다. //테스트용 코드 // 나눔손글씨 아빠글씨 // 궁서체 // 궁서 // 맑은 고딕 //굴림

	//클라이언트 배율을 정한다.
	this->zoomer = new Zoomer(100);

	//문자 매트릭스틀 만든다. 
	this->characterMatrix = new CharacterMatrix(this);

	//캐럿을 만든다
	this->caret = new Caret(this);

	//싱클바이트 캐럿을 만든다.
	this->caret->Create(2, this->characterMatrix->height);

	//선택 클래스를 만든다.
	this->select = new Select(this);

	//클립보드 클래스를 만든다. 
	this->clipboard = new Clipboard(this);

	//매크로 커멘드 클래스를 만든다.
	this->macroCommand = new MacroCommand();

	//검색결과 클래스를 만든다.
	this->resultFound = new ResultFound("");
	//찾다 클래스를 만든다. 
	this->finder = new Finder(this);
	//바꾸다 클래스를 만든다. 
	this->replacer = new Replacer(this);
	//페이지 설정을 한다
	this->pageSetting = new PageSetting(this);


	//클라이언트의 정보를 갱신한다. //OnSize
	if (this->clientMatrix == NULL) {
		this->clientMatrix = new ClientMatrix(this);
	}
	//문서의 가상크기를 계산한다.
	this->documentVirtualSize = new DocumentVirtualSize(this);

	//클라이언트 가상좌표를 초기설정한다. 
	this->clientLocation = new ClientLocation(this);

	//스크롤을 세팅한다.
	this->scroll = new Scroll(this);
	//스크롤을 보이게 한다.
	this->ShowScrollBar(SB_BOTH);
	//this->ShowScrollBar(SB_VERT);
	//this->ShowScrollBar(SB_HORZ);
	this->EnableScrollBar(SB_BOTH, ESB_DISABLE_BOTH);



	//컨트롤 //CONTROL
	//자동줄바꿈 컨트롤을 만들어 넣는다. 
	Observer* lineWrapControl = new LineWrapControl(this);
	this->AttachObserver(lineWrapControl);

	//문서 가상크기 컨트롤을 만들어 넣는다. 
	Observer* documentVirtualSizeControl = new DocumentVirtualSizeControl(this);
	this->AttachObserver(documentVirtualSizeControl);

	//스크롤 정보 컨틀롤을 만들어 넣는다.
	Observer* scrollControl = new ScrollInfoControl(this);
	this->AttachObserver(scrollControl);

	//자동 클라이언트 위치조정 컨트롤을 넣는다.
	Observer* autoScrollPositionControl = new AutoScrollPositionControl(this);
	this->AttachObserver(autoScrollPositionControl);

	//캐럿 컨트롤을 만들어 넣는다.
	Observer* caretControl = new CaretControl(this);
	this->AttachObserver(caretControl);

	//상태표시줄 컨트롤을 만들어 넣는다.
	Observer* statusBarControl = new StatusBarControl(this);
	this->AttachObserver(statusBarControl);

	//초기설정
	//맨 앞으로 이동한다. 
	lineOrder = this->paper->Move(0); //Last();
	currentLine = this->paper->GetAt(lineOrder);
	currentLine->Move(-1);
	//클라이언트 좌표를 맨 앞으로 조정한다. 
	this->clientLocation->Move(0, lineOrder);

#if 0
	//선택하기 테스트
	this->isSelected = TRUE;
	delete this->select;
	this->select = new Select(1, 4, 3, 5);

	this->select->MoveCurrent(-1, 1);
	//복사하기 테스트
	string tempString = "테스트 문구입니다1234.";
	this->clipboard->Copy(tempString);

	CPrintDialogEx temp(PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_HIDEPRINTTOFILE | PD_NOSELECTION | PD_NOCURRENTPAGE, this);
	temp.DoModal();
	CDC* tempDC;
	tempDC = temp.GetDC();
#endif

	return 0;
}

/*
* 함수명칭:OnPaint
* 기능:윈도우가 갱신될때의 이벤트를 실행한다.
*/
void Notepannel::OnPaint() {
	CPaintDC cPaintDC(this); //패널의 DC를 구한다. 
	CBitmap* previousBitmap = 0;
	CString name;
	int height;
	Long bold = 400;
	BOOL italic;
	CFont cFont;
	LOGFONT logFont;
	COLORREF rgbWhite = 0x00FFFFFF;
	CRect rect;

	//화면의 크기를 구한다. 
	this->GetClientRect(&rect);

	//더블 버퍼링 과정
	if (!(this->tempDC.GetSafeHdc())) {
		//호환되는 DC를 만든다
		this->tempDC.CreateCompatibleDC(&cPaintDC);

		if (this->currentBitmap.GetSafeHandle()) {
			this->currentBitmap.DeleteObject();
		}
		//DC와 호환되는 이미지를 만든다. 
		this->currentBitmap.CreateCompatibleBitmap(&cPaintDC, rect.Width(), rect.Height());
	}
	//호환 DC에 호환 이미지를 선택하고 이전이미지를 반환받는다. 
	previousBitmap = this->tempDC.SelectObject(&(this->currentBitmap));



	//기존의 내용 작성 
	//Child 클래스에서는 Invalidate의 WM_ERASEBKGND가 안먹히므로 배경을 지우는 과정을 넣는다. 
	this->tempDC.FillSolidRect(rect, rgbWhite);
	//현재 설정된 시스템 기본 글꼴을 가져온다. 
	cPaintDC.GetCurrentFont()->GetLogFont(&logFont);
	//바꿀 글꼴의 스타일을 가져온다. //Font의 접근제한자는 다 없앤다. 
	name = this->font->name;
	height = this->characterMatrix->height;
	if (this->font->bold == TRUE) {
		bold = 800;
	}
	italic = this->font->italic;
	//바꿀글꼴에 맞게 글꼴을 설정한다. 
	cFont.CreateFontA(height, 0, logFont.lfEscapement, logFont.lfOrientation, bold,
		italic, logFont.lfUnderline, logFont.lfStrikeOut, logFont.lfCharSet, logFont.lfOutPrecision,
		logFont.lfClipPrecision, logFont.lfQuality, logFont.lfPitchAndFamily, name);
	//바꾼 글꼴을 갱신한다.
	this->tempDC.SelectObject(&cFont);
	//방문자 클래스에서 문서의 내용을 작성한다. 
	PaintVisitor paintVisitor(this, &(this->tempDC));
	this->paper->Accept(&paintVisitor);

	//더블버퍼링 후반부
	//호환DC에 쓴 화면을 패널DC에 출력한다. 
	cPaintDC.BitBlt(0, 0, rect.Width(), rect.Height(), &(this->tempDC), 0 , 0, SRCCOPY); //SRCCOPY정말중요!!!!!
	
	//cPaintDC.BitBlt(0, 0, rect.right, rect.bottom, &tempDC, rect.left , rect.top, SRCCOPY);
	//cPaintDC.BitBlt(0, 0, rect.right / 2, rect.bottom, &tempDC, rect.left , rect.top, BLACKNESS);
	//cPaintDC.BitBlt(0, 0, rect.right, rect.bottom, &tempDC, rect.left, rect.top, SRCAND);
	//cPaintDC.StretchBlt(0, 0, rect.right, rect.bottom, &tempDC, rect.left, rect.top, SRCAND);
	//cPaintDC.SelectObject(&currentBitmap);
	
	//호환DC에서 이전 이미지를 선택한다. 
	tempDC.SelectObject(&previousBitmap);
	//이미지를 제거한다.
	currentBitmap.DeleteObject();
	//호환DC를 제거한다. 
	tempDC.DeleteDC();
	
	//ReleaseDC(&this->tempDC);
	
#if 0
	//호환DC 확인용 이미지 파일 출력/저장
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
* 함수명칭:OnChar
* 기능:싱글바이트 문자를 입력했을때의 이벤트를 실행한다.
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
		//종이에서 현재 줄의 위치를 가져온다.
		lineOrder = this->paper->GetCurrent();
		//종이에서 현재 위치에 있는 줄을 가져온다.
		currentLine = this->paper->GetAt(lineOrder);

		switch (nChar) {
		case VK_RETURN: //엔터키를 눌렀을때
			//줄에서 현재 위치를 가져온다.
			charIndex = currentLine->GetCurrent();
			//빈 줄을 만든다.
			newLine = glyphCreater.Create("\r\n");
			last = currentLine->Last();
			charIndex = currentLine->Move(charIndex);
			while (i < (last - charIndex)) {//현재 줄의 끝까지 반복한다.
				//현재 줄의 현재 위치의 다음 순서의 단어를 가져온다.
				character = currentLine->GetAt(charIndex + 1);
				//현재 단어를 빈 줄에 옮겨쓴다.
				newLine->Add(character->Clone());
				//옮겨쓴 단어를 지운다.
				currentLine->Remove(charIndex + 1);
				i++;
			}
			//종이에 옮겨쓴 줄을 현재 위치에 다음에 적는다.
			lineOrder = this->paper->Add(newLine);
			//적은 줄에서 맨 앞으로 이동한다.
			currentLine = this->paper->GetAt(lineOrder);
			currentLine->First();
			break;
		case VK_BACK: // 백스페이스는 키액션에서 전략을 취했기에 막아둔다. 
			break;
			//case 0x01:
				//break;
			//case 0x03:
				//break;

		//case VK_F16: //ctrl backspace의 경우
		//	break;
		case VK_ESCAPE: //esc를 막아둔다.
			break;
			//case 0x41:
				//break;
		default: //싱글바이트 문자를 입력했을때


			//그 외의 경우
			character = glyphCreater.Create(charArray);
			currentLine->Add(character);
			//line = this->paper->GetAt(this->paper->GetCurrent());
			break;
		}
#endif

		//문서의 내용이 변경되었다는 플래그를 띄운다. 
		this->documentUploaded = TRUE;
		//자동이동 체크 플래그를 띄운다. 
		this->clientMoveCheck = TRUE;

		//옵저버 컨트롤 호출
		this->Notify();

		//OnPaint를 재호출하기 위한 Invalidate함수 이것을 true로 하면 전체를 지웠다가 다시 입력하게된다. 
		//Invalidate를 FALSE로 하면 여전히 작동하지만 덮어쓰기의 개념이라 그냥 TRUE로 했다. 
		this->Invalidate(TRUE);

		//저장된 내용이 변경되었다는 플래그를 띄운다.
		this->hasChanged = TRUE;

		//윈도우의 제목을 갱신한다.
		CString windowTitle;
		windowTitle.Format("*%s - Windows 메모장", this->document->GetName().c_str());
		this->notepad->SetWindowText(windowTitle);

		//캐럿을 보인다.
		this->caret->ShowCaret();
	}
}


/*
* 함수명칭:OnStartComposition
* 기능:더블바이트 문자을 입력시작했을때의 이벤트를 수행한다
*/
LRESULT Notepannel::OnStartComposition(WPARAM wParam, LPARAM lParam) { // 더블바이트 문자를 입력받았을때

	return 0;
}

/*
* 함수명칭:OnImeComposition
* 기능:더블바이트 문자의 조립 중 일때의 이벤트를 수행한다.
*/
LRESULT Notepannel::OnImeComposition(WPARAM wParam, LPARAM lParam) { // 더블바이트 문자를 입력중일때
	GlyphCreater glyphCreater;
	Glyph* line = NULL;
	Glyph* character = NULL;
	char letter[3];

	CommandCreator commandCreator(this);
	Command* command = NULL;

	if (this->isSelected == TRUE) { //선택되었으면
			//삭제한다. 
		command = commandCreator.Create(IDM_FORMAT_DELETE);
		if (command != NULL) {
			command->Execute();
			this->macroCommand->Add(command);
		}
	}

	//입력된 글자를 읽는다.
	letter[0] = HIBYTE(wParam);
	letter[1] = LOBYTE(wParam);
	letter[2] = '\0';

	//현재 줄을 가져온다 
	line = this->paper->GetAt(this->paper->GetCurrent());

	//더블바이트 입력중이면 현재 글자를 지운다. 
	if (this->isComposing == TRUE) {
		line->Remove(line->GetCurrent());
	}

	//읽은 글자가 있으면 현재 위치에 더블바이트 문자를 적는다. 
	if (letter[0] != '\0') {
		character = glyphCreater.Create(letter);
		line->Add(character);
		//플래그를 올린다. 
		this->isComposing = TRUE;
	}
	else { //읽은 글자가 없으면 플래그를 내린다.
		this->isComposing = FALSE;
	}
	//플래그를 올린다. 
	//this->isComposing = TRUE;

	//내용이 변경되었다는 플래그를 띄운다.
	this->hasChanged = TRUE;
	//윈도우의 제목을 갱신한다.
	CString windowTitle;
	windowTitle.Format("*%s - Windows 메모장", this->document->GetName().c_str());
	this->notepad->SetWindowText(windowTitle);

	//문서의 내용이 변경되었다는 플래그를 띄운다. 
	this->documentUploaded = TRUE;
	//스크롤 위치를 확인하라는 플래그를 띄운다. 
	this->clientMoveCheck = TRUE;

	//캐럿 컨트롤 호출
	this->Notify();

	//WM_PAINT메세지를 호출한다. 
	this->Invalidate(TRUE);

	//캐럿을 출력한다.
	this->caret->ShowCaret();

	return DefWindowProc(WM_IME_COMPOSITION, wParam, lParam); // 이부분에 대한 이해 부족
}

/*
* 함수명칭:OnImeChar
* 기능:더블바이트 문자의 기능이 완성되었을때의 이벤트를 수행한다.
*/
LRESULT Notepannel::OnImeChar(WPARAM wParam, LPARAM lParam) { //더블바이트 문자를 완성했을때
	CommandCreator commandCreator(this);
	Command* command = NULL;
	GlyphCreater glyphCreater;
	Glyph* line = NULL;
	Glyph* character = NULL;
	//char letter[3];

	//플래그를 내린다. 
	this->isComposing = FALSE;



#if 0
	//입력된 문자를 읽는다.
	letter[0] = HIBYTE(wParam);
	letter[1] = LOBYTE(wParam);
	letter[2] = '\0';
#endif
	//현재 글자를 지운다. 
	line = this->paper->GetAt(this->paper->GetCurrent());
	line->Remove(line->GetCurrent());
#if 0
	//글에 글자를 적는다. 
	character = glyphCreater.Create(letter);
	line->Add(character);
#endif
	command = commandCreator.Create(wParam, lParam);
	if (command != NULL) {
		command->Execute();
	}
	this->macroCommand->Add(command, 1);

	//내용이 변경되었다는 플래그를 띄운다.
	this->hasChanged = TRUE;

	//윈도우의 제목을 갱신한다.
	CString windowTitle;
	windowTitle.Format("*%s - Windows 메모장", this->document->GetName().c_str());
	this->notepad->SetWindowText(windowTitle);

	//문서의 내용이 변경되었다는 플래그를 띄운다. 
	this->documentUploaded = TRUE;
	//캐럿 컨트롤 호출
	this->Notify();

	//WM_PAINT메세지를 호출한다. 
	this->Invalidate(TRUE);

	//캐럿을 출력한다.
	this->caret->ShowCaret();

	return 0;
}

/*
* 함수명칭:OnSetFocus
* 기능:입력포커스를 얻었을때의 기능을 수행한다.
*/
void Notepannel::OnSetFocus(CWnd* pOldWnd) {

	//캐럿을 보이게 한다. 
	this->caret->ShowCaret();
	this->Notify();

}

/*
* 함수명칭:OnKillFocus
* 기능:입력포커스를 읽기 직전에 호출하는 함수
*/
void Notepannel::OnKillFocus(CWnd* pNewWnd) {

	//캐럿을 안보이게 한다. 
	this->caret->HideCaret();
}

/*
* 함수명칭:OnKeyDown
* 기능:비시스템키를 누를때 호출되는 함수
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
* 함수명칭:OnKeyUp
* 기능:비시스템키가 해제될때 호출되는 함수
*/
void Notepannel::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_SHIFT) {
		this->isSelecting = FALSE;
	}
}




/*
* 함수명칭:OnLButtonDown
* 기능: 마우스 왼쪽 버튼을 클릭했을때의 이벤트를 실행한다.
*/
void Notepannel::OnLButtonDown(UINT nFlags, CPoint point) {//클릭한 위치를 읽는다.
	Glyph* currentLine = NULL;
	Long lineOrder;
	Long charIndex;
	int previousSelectXIndex = this->select->currentXIndex;
	int previousSelectLineOrder = this->select->currentLineOrder;
	SHORT shiftKeyState = GetKeyState(VK_SHIFT);

	//마우스클 캡쳐한다. 
	this->SetCapture();

	//클릭한 세로위치에 근접한 줄을 찾는다.
	lineOrder = this->characterMatrix->FindNearHeightPosition(point.y);
	//클라이언트 위치를 반영한다.
	lineOrder = lineOrder + this->clientLocation->lineOrder;
	//찾은 줄로 이동한다.
	lineOrder = this->paper->Move(lineOrder);
	//찾은 줄을 가져온다.
	currentLine = this->paper->GetAt(lineOrder);
	//찾은 줄에서 가로위치에 근접한 단어를 찾는다.
	point.x = point.x + this->clientLocation->x;
	charIndex = this->characterMatrix->FindNearWidthPosition(currentLine, point.x);
	//찾은 단어로 이동한다.
	currentLine->Move(charIndex);

	if (this->isSelecting == FALSE) { //shift키를 클릭하지 않았으면
		//선택 클래스를 할당해제한다.
		delete this->select;
		//문서의 현재 위치를 선택하기의 이전 위치로 지정된 선택 클래스를 만든다. 
		this->select = new Select(this, charIndex, lineOrder, charIndex, lineOrder);
	}
	else if ((shiftKeyState & 0x8000)) { //shift키를 누르고 있으면
		//선택하기의 현재 위치를 갱신한다.
		this->select->MoveCurrent(charIndex, lineOrder);
	}
	//클릭했다는 플래그를 띄운다.
	this->hasClicked = TRUE;
	//업데이트를 호출한다. 
	this->clientMoveCheck = TRUE;
	this->Notify();
	//클라이언트를 갱신한다.
	this->Invalidate(FALSE);
	//캐럿을 보이게 한다.
	this->caret->ShowCaret();
}

/*
* 함수명칭:OnLButtonUp
* 기능: 마우스 왼쪽 버튼을 뗏을때의 이벤트를 실행한다.
*/
void Notepannel::OnLButtonUp(UINT nFlags, CPoint point) {
	if (nFlags != MK_SHIFT) { //shift키를 누르지 않았으면
		//선택중이라는 표시를 내린다.
		this->isSelecting = FALSE;
	}
	//클릭했다는 플래그를 내린다.
	this->hasClicked = FALSE;

	//마우스의 캡쳐를 해제한다.
	ReleaseCapture();
}

/*
* 함수명칭:OnMouseMove
* 기능: 마우스 버튼을 끌 때의 이벤트를 실행한다.
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

	if (nFlags == MK_LBUTTON && this->hasClicked == TRUE && this->hasLoaded == FALSE && this->hasOnSized == FALSE) { //마우스를 클릭중이면
		//클릭한 세로위치에 근접한 줄을 찾는다.
		lineOrder = this->characterMatrix->FindNearHeightPosition(point.y);
		//클라이언트 위치를 반영한다.
		lineOrder = lineOrder + this->clientLocation->lineOrder;
		//찾은 줄로 이동한다.
		lineOrder = this->paper->Move(lineOrder);
		//찾은 줄을 가져온다.
		currentLine = this->paper->GetAt(lineOrder);
		//찾은 줄에서 가로위치에 근접한 단어를 찾는다.
		point.x = point.x + this->clientLocation->x;
		charIndex = this->characterMatrix->FindNearWidthPosition(currentLine, point.x);
		//찾은 단어로 이동한다.
		charIndex = currentLine->Move(charIndex);

		//선택하기의 현재위치를 갱신한다
		this->select->MoveCurrent(charIndex, lineOrder);


		//클라이언트의 이동 경계선을 계산한다.
		clientYMoveLocation = (this->clientMatrix->lineNumberInPage - 1) * this->characterMatrix->height;
		clientXMoveLocation = this->clientMatrix->width - 15;
		if (scrollPoint.y < 0) { //커서의 Y위치가 음수이면
			//한줄 위로 이동한다.
			vertical = verticalCreator.Create(SB_LINEUP, 0, 0);
			vertical->OnVScroll(0, 0, 0);
		}
		else if (scrollPoint.y > clientYMoveLocation) { //커서의 Y위치가 클라이언트 이동경계 아래이면
			//한줄 아래로 이동한다.
			vertical = verticalCreator.Create(SB_LINEDOWN, 0, 0);
			vertical->OnVScroll(0, 0, 0);
		}

		if (scrollPoint.x < 0) { //커서의 X위치가 음수이면
			//왼쪽으로 한 페이지 스크롤한다.
			horizontal = horizontalCreator.Create(SB_LINELEFT, 0, 0);
			horizontal->OnHScroll(0, 0, 0);
		}
		else if (scrollPoint.x > clientXMoveLocation) { //커서의 X위치가 클라이언트 이동경계 오른쪽이면
			//오른쪽으로 한 페이지 스크롤한다.
			horizontal = horizontalCreator.Create(SB_LINERIGHT, 0, 0);
			horizontal->OnHScroll(0, 0, 0);
		}
		//할당해제한다.
		delete vertical;
		delete horizontal;

		//업데이트를 한다.
		this->Notify();
		if (this->paper->IsNotEqual(previousLineOrder, previousCharIndex)) { //마우스를 끌어서 선택되었으면 
			//클라이언트를 갱신한다
			this->Invalidate(FALSE);
		}
		//캐럿을 보인다.
		this->caret->ShowCaret();
	}
	this->hasLoaded = FALSE;
	this->hasOnSized = FALSE;

}

/*
* 함수명칭:OnLButtonDblClk
* 기능:마우스 왼쪽 버튼을 더블클릭했을 때의 이벤트를 실행한다.
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
	//현재 위치를 기억한다. 
	previousCharIndex = charIndex;
	//현재 줄에서 이전 단어로 이동한다.
	charIndex = currentLine->PreviousWord();

	if (this->isSelecting == FALSE) {//선택 중이 아니면
		//선택하기 클래스를 할당해제한다.
		delete this->select;
		//선택하기 클래스에서 현재 위치를 이전위치로 지정해서 할당한다.
		this->select = new Select(this, charIndex, lineOrder, charIndex, lineOrder);
		//다음 단어로 이동한다.
		charIndex = currentLine->NextWord();
		//선택하기에서 현재위치를 갱신한다.
		this->select->MoveCurrent(charIndex, lineOrder);

	}
	else { //선택 중이면
		if (previousSelectLineOrder > lineOrder) {//선택하기의 위치가 현재 위치보다 뒤이면 현재위치(단어앞)로 이동한다.
			this->select->MoveCurrent(charIndex, lineOrder);
		}
		else if (previousSelectLineOrder == lineOrder && previousSelectXIndex > previousCharIndex) {
			this->select->MoveCurrent(charIndex, lineOrder);
		}
		else {//선택한 위치가 현재 위치의 앞이면
			//다음단어로 이동한다.
			charIndex = currentLine->NextWord();
			//선택하기에서 이동한다.
			this->select->MoveCurrent(charIndex, lineOrder);
		}

	}
	//업데이트를 한다.
	this->Notify();
	//클라이언트를 갱신한다
	this->Invalidate(TRUE);
	//캐럿을 보인다.
	this->caret->ShowCaret();
}


/*
* 함수명칭:OnMouseWheel
* 기능:마우스 휠을 굴릴때의 이벤트
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
* 함수명칭:OnVScroll
* 기능:세로 스크롤의 이벤트를 수행하는 함수
*/
void Notepannel::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) { //스크롤의 위치를 읽는다.
	VerticalScrollAction* verticalScrollAction = 0;
	VerticalScrollActionCreator verticalScrollActionCreator(this);

	verticalScrollAction = verticalScrollActionCreator.Create(nSBCode, nPos, pScrollBar);

	if (verticalScrollAction != NULL) {
		verticalScrollAction->OnVScroll(nSBCode, nPos, pScrollBar);
	}

	delete verticalScrollAction;
}

/*
* 함수명칭:OnHScroll
* 기능:가로 스크롤의 이벤트를 수행하는 함수
*/
void Notepannel::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) { //스크롤의 위치를 읽는다.
	HorizontalScrollAction* horizontalScrollAction = 0;
	HorizontalScrollActionCreator horizontalScrollActionCreator(this);

	horizontalScrollAction = horizontalScrollActionCreator.Create(nSBCode, nPos, pScrollBar);

	if (horizontalScrollAction != NULL) {
		horizontalScrollAction->OnHScroll(nSBCode, nPos, pScrollBar);
	}

	delete horizontalScrollAction;
}

/*
* 함수명칭:OnSize
* 기능:윈도우 크기가 최대화될때, 최대화에서 일반화 될때의 이벤트를 처리한다.
*/
void Notepannel::OnSize(UINT nType, int cx, int cy) {
	if (this->isUpdating == FALSE && this->notepad->nType == SIZE_MAXIMIZED) { //최대화 버튼을 클릭했을 때
		this->OnSizing(0, 0);

		this->isMaximixed = TRUE;
	}
	else if (this->isUpdating == FALSE && this->notepad->nType == SIZE_RESTORED) { // && this->isMaximixed == TRUE) { //최대화상태에서 일반화 될때
		this->OnSizing(0, 0);


		this->isMaximixed = FALSE;
	}
	//else if(this->isUpdating == FALSE && )
	//this->notepad->statusBarCtrl.ShowWindow(SW_SHOW);

}

/*
* 함수명칭:OnSizing
* 기능:사용자가 윈도우 크기를 조절할때의 이벤트를 실행한다.
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
		//클라이언트의 크기 클래스를 새로 갱신해준다.
		if (this->clientMatrix != NULL) {
			delete this->clientMatrix;
		}
		this->clientMatrix = new ClientMatrix(this);
		//클라이언트의 위치를 읽는다.
		this->notepad->GetWindowInfo(&windowInfo);
		windowRect = windowInfo.rcClient;
		//메뉴에서 상태표시줄 항목이 체크되었는지 확인한다. 
		statusBarState = this->notepad->cMenu.GetMenuState(IDM_FORMAT_STATUSBAR, MF_BYCOMMAND);
		if (statusBarState == MF_CHECKED) { //상태표시줄 메뉴가 체크되어있으면
			//상태표시줄을 갱신한다.
			this->notepad->statusBar->UpdateStatusBar();

			//클라이언트 크기에 맞게 패널 크기를 갱신한다.
			pannelRect = { 0,0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top - this->notepad->statusBar->heigth };
			this->MoveWindow(&pannelRect);
		}
		else if (statusBarState == MF_UNCHECKED) { //상태표시줄 메뉴가 체크되어있지 않으면
			//클라이언트 크기에 맞게 패널 크기를 갱신한다.
			pannelRect = { 0,0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };
			this->MoveWindow(&pannelRect);
		}
		//패널을 포커스 한다. 
		this->SetFocus();


		this->tempDC.DeleteDC();
		this->currentBitmap.DeleteObject();

		//업데이트 함수를 호출해준다
		this->documentUploaded = TRUE;
		//this->clientMoveCheck = TRUE;
		this->isUpdating = TRUE;
		this->Notify();
		//클라이언트를 갱신한다.
		this->Invalidate(TRUE);
		//업데이트가 끝났음을 표시한다.
		this->isUpdating = FALSE;
		//캐럿을 표시한다.
		this->ShowCaret();

		//창 크기가 바뀌었다는 플래그를 올린다.
		this->hasOnSized = TRUE;
	}
}

/*
* 함수명칭:OnFindReplace
* 기능:찾기 바꾸기 대화상자의 이벤트를 관리하는 모듈
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
	//플래그
	BOOL replaceAll;
	BOOL replaceCurrent;
	BOOL findNext;
	BOOL isTerminating;
	//첫 검색을 위한 변수
	GlyphCreater glyphCreater;
	Glyph* tempPaper;

	//못찾았을 때
	CString message;
	//자동개행
	CommandCreator commandCreater(this);
	Command* command = NULL;
	UINT lineWrapState = -1;
	lineWrapState = this->notepad->cMenu.GetMenuState(IDM_FORMAT_LINEWRAP, MF_BYCOMMAND);


	//써있는 내용을 적는다. (Finder)
	delete this->finder;
	this->finder = new Finder(this, wParam, lParam);
	delete this->replacer;
	this->replacer = new Replacer(this, wParam, lParam);


	//AfxMessageBox(_T(this->finder->find.c_str())); //찾는 문구 

	//플래그
	replaceAll = this->replacer->replaceAll;
	replaceCurrent = this->replacer->replaceCurrent;
	findNext = this->finder->findNext;
	isTerminating = this->finder->isTerminating;

	//오류 메세지를 만든다. 
	message.Format("'%s'을(를) 찾을 수 없습니다.", this->finder->find.c_str());

	//자동개행이 되어있으면 개행취소한다. 
	if (isTerminating == FALSE && lineWrapState == MF_CHECKED) {
		command = commandCreater.Create(IDM_FORMAT_LINEWRAP);
		command->UnExecute();
		delete command;
	}

	if (findNext == TRUE) {//다음 찾기를 클릭했거나 검색 결과가 없는 상태에서 바꾸기 버튼을 클릭했는데

		//종이에서 현재 위치를 읽는다.
		lineOrder = this->paper->GetCurrent();
		currentLine = this->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();
		//현재 위치를 기억한다. 
		currentLineOrder = lineOrder;
		currentCharIndex = charIndex;
		//입력값에 맞게 찾는다.
		count = this->finder->Find();

		if (count <= 0) {//찾은 내용이 없으면 메시지를 띄운다.
			//업데이트를 한다.(위치)
			this->clientMoveCheck = TRUE;
			this->documentUploaded = TRUE;
			this->Notify();
			//클라이언트를 갱신한다.
			this->Invalidate(TRUE);

			AfxMessageBox(message);
			//현재 위치로 이동한다. 
			lineOrder = this->paper->Move(currentLineOrder);
			currentLine = this->paper->GetAt(lineOrder);
			currentLine->Move(currentCharIndex);
		}
		else if (count > 0) {//내용을 찾았으면
			//결과 값중 현재 위치 근처를 찾는다. 
			indexNear = this->finder->SearchNear(currentLineOrder, currentCharIndex);
			if (indexNear < count && indexNear >= 0) { //근처 값이 있으면
				this->finder->SelectResult(indexNear);
			}
			else { //찾지 못했으면 메시지를 출력한다. 
				//업데이트를 한다.(위치)
				this->clientMoveCheck = TRUE;
				this->documentUploaded = TRUE;
				this->Notify();
				//클라이언트를 갱신한다.
				this->Invalidate(TRUE);

				AfxMessageBox(message);
				//현재 위치로 이동한다. 
				lineOrder = this->paper->Move(currentLineOrder);
				currentLine = this->paper->GetAt(lineOrder);
				currentLine->Move(currentCharIndex);
			}
		}
		//캐럿을 숨긴다.
		this->caret->HideCaret();
	}
	else if (replaceCurrent == TRUE) { //검색결과를 선택중일 때 바꾸기 버튼을 클릭했으면
		
		//현재 입력된 검색어를 종이로 치환한다.
		tempPaper = glyphCreater.Create((string)(CFindReplaceDialog::GetNotifier(lParam)->GetFindString()));
		
		if (this->isSelected == TRUE && this->resultFound->paperToFind != 0 && this->select->IsEqual(this->resultFound->paperToFind) == TRUE) {
			//이미 검색을 한번 했으면
			//현재 선택된 내용을 바꾼다. 
			this->replacer->ReplaceCurrent();
		}
		else if (this->isSelected == TRUE && this->resultFound->paperToFind == 0 && this->select->IsEqual(tempPaper) == TRUE) {
			//첫 검색이면
			//현재 선택된 내용을 바꾼다. 
			this->replacer->ReplaceCurrent();
		}
		//종이를 할당해제한다. 
		delete tempPaper;


		//현재 위치를 기억한다. 
		lineOrder = this->paper->GetCurrent();
		currentLine = this->paper->GetAt(lineOrder);
		charIndex = currentLine->GetCurrent();

		//현재 위치를 기준으로 검색을 한번 더 한다. 
		count = this->finder->Find();
		//결과가 나오면 근처에 찾는 내용이 있는지 확인한다. 
		if (count > 0) {
			//결과 값중 현재 위치 근처를 찾는다. 

			indexNear = this->finder->SearchNear(lineOrder, charIndex);
			if (indexNear < count && indexNear >= 0) { //근처 값이 있으면
				this->finder->SelectResult(indexNear);
			}
			else { //찾지 못했으면 메시지를 출력한다. 
				//업데이트를 한다.(위치)
				this->clientMoveCheck = TRUE;
				this->documentUploaded = TRUE;
				this->Notify();
				//클라이언트를 갱신한다.
				this->Invalidate(TRUE);

				AfxMessageBox(message);
				//현재 위치로 이동한다. 
				lineOrder = this->paper->Move(lineOrder);
				currentLine = this->paper->GetAt(lineOrder);
				currentLine->Move(charIndex);
			}
		}
		else if (count <= 0) {//찾은 내용이 없으면 메시지를 띄운다.
			//업데이트를 한다.(위치)
			this->clientMoveCheck = TRUE;
			this->documentUploaded = TRUE;
			this->Notify();
			//클라이언트를 갱신한다.
			this->Invalidate(TRUE);

			AfxMessageBox(message);
			//현재 위치로 이동한다. 
			lineOrder = this->paper->Move(lineOrder);
			currentLine = this->paper->GetAt(lineOrder);
			currentLine->Move(charIndex);
		}
		//캐럿을 숨긴다.
		this->caret->HideCaret();
	}
	else if (replaceAll == TRUE) { //모두 바꾸기 버튼을 클릭했으면
		//검색어를 찾는다.
		count = this->finder->Find();
		if (count > 0) {//내용을 찾았으면
			//맨 처음으로 이동한다. 
			lineOrder = this->paper->First();
			currentLine = this->paper->GetAt(lineOrder);
			charIndex = currentLine->First();
			//다음 위치를 찾는다. 
			indexNear = this->finder->SearchNear(lineOrder, charIndex);
			repete = count;
			while (indexNear >= 0 && indexNear < count && i < repete) { //근처 값이 있으면
				//찾은 결과를 선택한다. 
				this->finder->SelectResult(indexNear);
				//현재 위치를 기억한다. 
				lineOrder = this->select->endLineOrder;
				charIndex = this->select->endXIndex;
				//현재 선택된 내용을 바꾼다. 
				this->replacer->ReplaceCurrent();
				this->macroCommand->FlagDown();
				//검색어를 찾는다.
				count = this->finder->Find();
				if (count > 0) {
					//찾으면 다음 위치를 찾는다. 
					indexNear = this->finder->SearchNear(lineOrder, charIndex);
				}
				else {
					//찾지 못하면 
					indexNear = -1;
				}
				i++;
			}
			this->macroCommand->FlagUp();
		}
		//캐럿을 숨긴다.
		this->caret->HideCaret();
	}
	else if (isTerminating == TRUE) {//찾기 바꾸기 대화상자를 닫았으면 
		//캐럿을 표시한다.
		this->caret->ShowCaret();
	}
	//업데이트를 한다.(위치)
	this->clientMoveCheck = TRUE;
	this->documentUploaded = TRUE;
	this->Notify();
	//클라이언트를 갱신한다.
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
			msg = "저장(&S)";
			SetWindowText(GetDlgItem(hChildWnd, IDYES), msg);
		}

		if (GetDlgItem(hChildWnd, IDNO) != NULL) {
			msg = "저장 안 함(&N)";
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
