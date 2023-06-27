//PreviewPage.h
/*
* 파일명칭:PreviewPage.h
* 기능:미리보기 프레임 윈도우의 헤더
* 작성자:허지욱
* 작성일자:2022/12/16
*/
#ifndef _PreviewPage_H
#define _PreviewPage_H
#include <afxwin.h>
#include <afxext.h>
#include <string>
using namespace std;

class Notepannel;
class Glyph;
class PreviewPage : public CFrameWnd {
public:
	PreviewPage(Notepannel* notepannel);
	~PreviewPage();

	CReBar reBar;
	CDialogBar dialogBar;
	int dialogHeight;

	BOOL isCreating;

	void Print(HDC hPrinter);

	Glyph* paperPreview;
	int lineNumberInPage;
	int pageNumber;
	int currentPage;

	int marginLeftStart;
	int marginTopStart;
	int marginRightEnd;
	int headerPoint;
	int marginBottomEnd;
	int footerPoint;
	int textHeigth;

	int widthToCutInPoint;

	BOOL isMaximixed;

private:
	Notepannel* notepannel;
protected:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
	//다이얼로그 바 관련
	afx_msg void OnUpdateCmdUIFirstButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCmdUIPreviousButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCmdUINextButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCmdUILastButton(CCmdUI* pCmdUI);
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	DECLARE_MESSAGE_MAP()
};

#endif // !_PreviewPage_H
