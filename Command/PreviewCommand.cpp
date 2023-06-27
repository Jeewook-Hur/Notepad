//PreviewCommand.cpp
/*
* ���ϸ�Ī:PreviewCommand.cpp
* ���:�̸����� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/12/16
*/
#include "PreviewCommand.h"
#include "Notepannel.h"
#include "PreviewPage.h"

/*
* �Լ���Ī:PreviewCommand
* ���:������
*/
PreviewCommand::PreviewCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~PreviewCommand
* ���:�Ҹ���
*/
PreviewCommand::~PreviewCommand() {
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����ϴ�
*/
void PreviewCommand::Execute() {
	PreviewPage* previewPage = new PreviewPage(this->notepannel);
	RECT pageSize = { 0, 0, 700, 950 };
	//�̸����� �����츦 �����
	previewPage->Create(NULL, "������ �̸�����", WS_OVERLAPPEDWINDOW, pageSize, this->notepannel);
	//�̸����� �����츦 ����. 
	previewPage->ShowWindow(SW_SHOW);//MAXIMIZED);
	CRect windowSize = { 0,0, 630, 900 };
	previewPage->MoveWindow(&windowSize);
	previewPage->UpdateWindow();
}