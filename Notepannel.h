//Notepannel.h
/*
* ���ϸ�Ī:Notepannel.h
* ���:�޸����� Ŭ���̾�Ʈ ������ ����� �ϴ� �г��� ���
* �ۼ���:������
* �ۼ�����:2022/12/20
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
	BOOL hasChanged; // ������ ���� Ȯ��
	BOOL documentUploaded; // ������ �ۼ������� �� �� ���(�̵�)���� ����
	BOOL isLineWraping; //�ڵ����������� ǥ���ϴ� �÷���
	BOOL clientMoveCheck; //Ŭ���̾�Ʈ�� �ڵ��̵����Ѿ� �ϴ��� ǥ��
	BOOL isCalledFromMenu; //�޴����� Ŭ���Ѱ��� Ȯ���ϴ� �Ҹ���
	BOOL isUpdating; //Notify�� �ߺ� ������Ʈ�� �ϴ� ��츦 �����ϱ� ���� ��ġ
	BOOL isMaximixed;
	BOOL isSelected; //Ŭ���̾�Ʈ ���Ž� ǥ�ø� ���� ���
	BOOL isSelecting; //shiftŰ�� ���콺 Ŭ�� �巡���� ���� ���
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

//�Լ� ����
LRESULT CALLBACK SaveMessageBoxProc(int nCode, WPARAM wParam, LPARAM lParam);
int SaveMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT nType);

#endif // !_NOTEPANNEL_H
