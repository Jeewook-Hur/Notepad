//NotepadApp.h
/*
* 파일명칭:NotepadApp.h
* 기능:메모장을 실행시키는 파일의 헤더
* 작성자:허지욱
* 작성일자:2022/7/18
*/
#ifndef _NOTEPADAPP_H
#define _NOTEPADAPP_H
#include <afxwin.h>

class NotepadApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

#endif // !_NOTEPADAPP_H