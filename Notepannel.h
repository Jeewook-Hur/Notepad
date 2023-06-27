//Notepannel.h
/*
* 파일명칭:Notepannel.h
* 기능:메모장의 클라이언트 영역에 출력을 하는 패널의 헤더
* 작성자:허지욱
* 작성일자:2022/12/20
*/
#ifndef _NOTEPANNEL_H
#define _NOTEPANNEL_H
#include<afxwin.h>
#include "Subject.h"

typedef signed long int Long;
class Glyph;
class Caret;
class Font;
class CharacterMatrix;
class Document;
class DocumentVirtualSize;
class ClientLocation;
class ClientMatrix;
class Scroll;
class Zoomer;
class Select;
class Paint;
class Clipboard;
class MacroCommand;
class Finder;
class ResultFound;
class Replacer;
class PageSetting;

class Notepad;
class Notepannel : public CWnd, public Subject {
public:
	Notepannel(Notepad* notepad);
	~Notepannel();

	Glyph* paper;
	Caret* caret;
	Font* font;
	CharacterMatrix* characterMatrix;
	Document* document;
	DocumentVirtualSize* documentVirtualSize;
	ClientLocation* clientLocation;
	ClientMatrix* clientMatrix;
	Scroll* scroll;
	Zoomer* zoomer;
	Select* select;
	Clipboard* clipboard;
	MacroCommand* macroCommand;
	Finder* finder;
	ResultFound* resultFound;
	Replacer* replacer;
	PageSetting* pageSetting;

	BOOL isComposing;
	BOOL isSaved;
	BOOL hasChanged; // 저장을 위한 확인
	BOOL documentUploaded; // 문서를 작성중인지 그 외 기능(이동)인지 구분
	BOOL isLineWraping; //자동개행중인지 표시하는 플래그
	BOOL clientMoveCheck; //클라이언트를 자동이동시켜야 하는지 표시
	BOOL isCalledFromMenu; //메뉴에서 클릭한건지 확인하는 불리언
	BOOL isUpdating; //Notify로 중복 업데이트를 하는 경우를 방지하기 위한 조치
	BOOL isMaximixed;
	BOOL isSelected; //클라이언트 갱신시 표시를 위한 기능
	BOOL isSelecting; //shift키와 마우스 클릭 드래그의 공통 기능
	BOOL hasLoaded;
	BOOL hasOnSized;
	BOOL hasClicked;
	BOOL isScrollSetting;

	Notepad* notepad;
	CDC tempDC;
	CBitmap currentBitmap;


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
	
	afx_msg LONG OnFindReplace(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//함수 선언
LRESULT CALLBACK SaveMessageBoxProc(int nCode, WPARAM wParam, LPARAM lParam);
int SaveMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT nType);

#endif // !_NOTEPANNEL_H
