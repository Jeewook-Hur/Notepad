//Clipboard.cpp
/*
* ���ϸ�Ī:Clipboard.cpp
* ���:������ Ŭ�����带 ��ȸ�Ͽ� ���� �ٿ��ֱ� ����� �����Ѵ�. 
* �ۼ���:������
* �ۼ�����:2022/11/19
*/
#include "Clipboard.h"
//#include <WinUser.h>
#include "Notepannel.h"
#include<string>
using namespace std;

/*
* �Լ���Ī:Clipboard
* ���:������
*/
Clipboard::Clipboard(Notepannel* notepannel):notepannel(notepannel) {
}

/*
* �Լ���Ī:~Clipboard
* ���:�Ҹ���
*/
Clipboard::~Clipboard() {
}

/*
* �Լ���Ī:Copy
* ���:Ŭ�����忡 �Է¹��� ���ڿ��� �Է��Ѵ�. 
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
* �Լ���Ī:GetData
* ���:Ŭ�����忡 �ؽ�Ʈ�� ������� �ؽ�Ʈ �����͸� �а� ��ȯ�Ѵ�. 
*/
string Clipboard::GetData() {
    HGLOBAL hGlob;
    SIZE_T size;
    string clipboardString = "";
    SIZE_T i = 0;

    if (!(this->notepannel->OpenClipboard())) { //�޸��� Ŭ���̾�Ʈ���� Ŭ�����带 ����. 
        AfxMessageBox(_T("Cannot open the Clipboard"));
    }
    //Ŭ�������� ����Ʈ �ڵ��� �ؽ�Ʈ�� �����´�. 
    hGlob = GetClipboardData(CF_TEXT);
    if (hGlob != 0) {
        //������ �ڵ��� ���̸� ���Ѵ�. 
        size = GlobalSize(hGlob);

        while (i < size) { //�ٿ��� �ؽ�Ʈ�� ���̸�ŭ �ݺ��Ѵ�. 
            clipboardString = clipboardString + ((char*)hGlob)[i];
            i++;
        }
    }
    CloseClipboard();

    return clipboardString; //���ڿ��� ��ȯ�Ѵ�.
}

/*
* �Լ���Ī:Check
* ���:Ŭ�����忡 ������ �ִ��� Ȯ���Ѵ�. 
*/
BOOL Clipboard::Check() {
    BOOL ret = FALSE;
    HGLOBAL hGlob;

    if (!(this->notepannel->OpenClipboard())) { //�޸��� Ŭ���̾�Ʈ���� Ŭ�����带 ����. 
        AfxMessageBox(_T("Cannot open the Clipboard"));
    }
    //Ŭ�������� ����Ʈ �ڵ��� �ؽ�Ʈ�� �����´�. 
    hGlob = GetClipboardData(CF_TEXT);
    //������ �ڵ��� ���̸� ���Ѵ�. 
    if (hGlob != 0) {
        ret = TRUE;
    }
    CloseClipboard();

    return ret;
}
