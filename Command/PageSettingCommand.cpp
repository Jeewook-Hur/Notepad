//PageSettingCommand.cpp
/*
* ���ϸ�Ī:PageSettingCommand.cpp
* ���:���������� Ŀ���
* �ۼ���:������
* �ۼ�����:2022/12/16
*/
#include "PageSettingCommand.h"
#include "Notepannel.h"
#include "PreviewPage.h"
#include "PageSettingForm.h"

/*
* �Լ���Ī:PageSettingCommand
* ���:������
*/
PageSettingCommand::PageSettingCommand(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* �Լ���Ī:~PageSettingCommand
* ���:�Ҹ���
*/
PageSettingCommand::~PageSettingCommand() {
}

/*
* �Լ���Ī:Execute
* ���:Ŀ��带 �����ϴ�
*/
void PageSettingCommand::Execute() {
	PageSettingForm pageSettingForm(this->notepannel, this->notepannel);
	pageSettingForm.DoModal();
#if 0
	PreviewPage* previewPage = new PreviewPage(this->notepannel); 
	RECT pageSize = { 0, 0, 700, 950 };
	//�̸����� �����츦 �����
	previewPage->Create(NULL, "������ �̸�����", WS_OVERLAPPEDWINDOW, pageSize, this->notepannel);
	//�̸����� �����츦 ����. 
	previewPage->ShowWindow(SW_SHOW);//MAXIMIZED);
	previewPage->UpdateWindow();
#endif
}