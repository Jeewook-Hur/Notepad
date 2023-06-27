//PrintCommand.cpp
/*
* ���ϸ�Ī:PrintCommand.cpp
* ���:�μ� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/12/19
*/
#include "PrintCommand.h"
#include "Notepannel.h"
#include "PreviewPage.h"
#include <afxdlgs.h>

/*
* �Լ���Ī:PrintCommand
* ���:������
*/
PrintCommand::PrintCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~PrintCommand
* ���:�Ҹ���
*/
PrintCommand::~PrintCommand() {
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����ϴ�
*/
void PrintCommand::Execute() {
	PreviewPage* previewPage;
	HDC hPrinter;
	RECT pageSize = { 0, 0, 700, 950 };
	//�μ��ϱ� �Ϲݴ�ȭ���ڸ� �����.
	CPrintDialogEx printDialogEx(PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS |  PD_NOSELECTION | PD_NOCURRENTPAGE, this->notepannel);
	//�μ��ϱ� �Ϲݴ�ȭ���ڸ� ����. 
	printDialogEx.DoModal();

	if (printDialogEx.m_pdex.dwResultAction == PD_RESULT_PRINT) { //�μ��ϱ⸦ ������ ���
		//�μ⸦ �Ѵ�.
		//�������� ����̽� ���ؽ�Ʈ�� �����´�. 
		hPrinter = printDialogEx.CreatePrinterDC();

		previewPage = new PreviewPage(this->notepannel);

		//�̸����� �������� �����. 
		previewPage->Create(NULL, "������ �̸�����", WS_OVERLAPPEDWINDOW, pageSize, this->notepannel);
		//�μ��Ѵ�. 
		previewPage->Print(hPrinter);
		//�̸����� �����츦 ����. 
		//previewPage->ShowWindow(SW_SHOW);//MAXIMIZED);
		//previewPage->UpdateWindow();
		
		//�μ⸦ ��ġ�� �̸����� Ŭ������ �Ҵ������Ѵ�. 
		//�μ⸦ ��ġ�� �ڵ��� �����Ѵ�.
		DeleteDC(hPrinter);
	}
}