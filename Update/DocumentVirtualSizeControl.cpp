//DocumentVirtualSizeControl.cpp
/*
* 파일명칭:DocumentVirtualSizeControl.cpp
* 기능:문서의 가상크기를 조정하는 클래스
* 작성자:허지욱
* 작성일자:2022/9/29
*/
#include "DocumentVirtualSizeControl.h"
#include "DocumentVirtualSize.h"
#include "Notepannel.h"

/*
* 함수명칭:DocumentVirtualSizeControl
* 기능:생성자
*/
DocumentVirtualSizeControl::DocumentVirtualSizeControl(Notepannel* notepannel) {
	this->notepannel = notepannel;
}

/*
* 함수명칭:~DocumentVirtualSizeControl
* 기능:소멸자
*/
DocumentVirtualSizeControl::~DocumentVirtualSizeControl() {
}

/*
* 함수명칭:Update
* 기능:입력받은 클래스에 맞는 업데이트를 한다.
*/
void DocumentVirtualSizeControl::Update(Subject* theChangedSubject) {
	this->notepannel->isUpdating = TRUE;
	if (dynamic_cast<Notepannel*>(theChangedSubject)) {//입력받은 클래스가 메모장이면
		if (this->notepannel->documentUploaded == TRUE) {
			delete this->notepannel->documentVirtualSize;
			this->notepannel->documentVirtualSize = new DocumentVirtualSize(this->notepannel);
		}
	}
	this->notepannel->isUpdating = FALSE;
}
