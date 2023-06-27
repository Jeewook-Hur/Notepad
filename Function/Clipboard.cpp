//Clipboard.cpp
/*
* 파일명칭:Clipboard.cpp
* 기능:윈도우 클립보드를 조회하여 복사 붙여넣기 기능을 수행한다. 
* 작성자:허지욱
* 작성일자:2022/11/19
*/
#include "Clipboard.h"
//#include <WinUser.h>
#include "Notepannel.h"
#include<string>
using namespace std;

/*
* 함수명칭:Clipboard
* 기능:생성자
*/
Clipboard::Clipboard(Notepannel* notepannel):notepannel(notepannel) {
}

/*
* 함수명칭:~Clipboard
* 기능:소멸자
*/
Clipboard::~Clipboard() {
}

/*
* 함수명칭:Copy
* 기능:클립보드에 입력받은 문자열을 입력한다. 
*/
BOOL Clipboard::Copy(string stringToCopy) {
    int length;
    BOOL ret = FALSE;

    length = stringToCopy.length() + 1;
    if (length > 0) {
        if (!(this->notepannel->OpenClipboard())) {
            AfxMessageBox(_T("Cannot open the Clipboard"));
            ret = FALSE;
            //return;
        }
        // Remove the current Clipboard contents
        if (!EmptyClipboard()) {
            AfxMessageBox(_T("Cannot empty the Clipboard"));
            ret = FALSE;
            //return;
        }
        // Get the currently selected data
        HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, length);
        if (hGlob != 0) {
            strcpy_s((char*)hGlob, length, stringToCopy.c_str());
        }
        // For the appropriate data formats...
        if (::SetClipboardData(CF_TEXT, hGlob) == NULL) {
            CString msg;
            msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
            AfxMessageBox(msg);
            CloseClipboard();
            GlobalFree(hGlob);
            //return;
            ret = FALSE;
        }
        CloseClipboard();
        ret = TRUE;
    }
    return ret;
}

/*
* 함수명칭:GetData
* 기능:클립보드에 텍스트가 있을경우 텍스트 데이터를 읽고 반환한다. 
*/
string Clipboard::GetData() {
    HGLOBAL hGlob;
    SIZE_T size;
    string clipboardString = "";
    SIZE_T i = 0;

    if (!(this->notepannel->OpenClipboard())) { //메모장 클라이언트에서 클립보드를 연다. 
        AfxMessageBox(_T("Cannot open the Clipboard"));
    }
    //클립보드의 데이트 핸들을 텍스트로 가져온다. 
    hGlob = GetClipboardData(CF_TEXT);
    if (hGlob != 0) {
        //데이터 핸들의 길이를 구한다. 
        size = GlobalSize(hGlob);

        while (i < size) { //붙여쓸 텍스트의 길이만큼 반복한다. 
            clipboardString = clipboardString + ((char*)hGlob)[i];
            i++;
        }
    }
    CloseClipboard();

    return clipboardString; //문자열을 반환한다.
}

/*
* 함수명칭:Check
* 기능:클립보드에 내용이 있는지 확인한다. 
*/
BOOL Clipboard::Check() {
    BOOL ret = FALSE;
    HGLOBAL hGlob;

    if (!(this->notepannel->OpenClipboard())) { //메모장 클라이언트에서 클립보드를 연다. 
        AfxMessageBox(_T("Cannot open the Clipboard"));
    }
    //클립보드의 데이트 핸들을 텍스트로 가져온다. 
    hGlob = GetClipboardData(CF_TEXT);
    //데이터 핸들의 길이를 구한다. 
    if (hGlob != 0) {
        ret = TRUE;
    }
    CloseClipboard();

    return ret;
}
