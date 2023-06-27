//KeyActionCreator.cpp
/*
* 파일명칭:KeyActionCreator.cpp
* 기능:키액션 생성 팩토리
* 작성자:허지욱
* 작성일자:2022/9/15
*/
#include "KeyActionCreator.h"
#include "Notepannel.h"
#include "UpKey.h"
#include "ShiftUpKey.h"

#include "DownKey.h"
#include "ShiftDownKey.h"

#include "LeftKey.h"
#include "CtrlLeftKey.h"
#include "ShiftLeftKey.h"
#include "CtrlShiftLeftKey.h"

#include "RightKey.h"
#include "CtrlRightKey.h"
#include "ShiftRightKey.h"
#include "CtrlShiftRightKey.h"

#include "HomeKey.h"
#include "ShiftHomeKey.h"
#include "CtrlHomeKey.h"
#include "CtrlShiftHomeKey.h"

#include "EndKey.h"
#include "ShiftEndKey.h"
#include "CtrlEndKey.h"
#include "CtrlShiftEndKey.h"

#include "BackspaceKey.h"
#include "CtrlBackspaceKey.h"
#include "CtrlShiftBackspaceKey.h"
#include "DeleteKey.h"
#include "CtrlDeleteKey.h"
#include "CtrlShiftDeleteKey.h"
#include "SelectDelete.h"

#include "PageUpKey.h"
#include "ShiftPageUpKey.h"
#include "PageDownKey.h"
#include "ShiftPageDownKey.h"
#include "ShiftKey.h"

#include "CtrlAKey.h"
#include "CtrlSKey.h"
#include "CtrlShiftSKey.h"
#include "CtrlNKey.h"
#include "CtrlOKey.h"
#include "CtrlWKey.h"
#include "CtrlPlusKey.h"
#include "CtrlMinusKey.h"
#include "CtrlZeroKey.h"
#include "CtrlCKey.h"
#include "CtrlXKey.h"
#include "CtrlVKey.h"
#include "CtrlZKey.h"
#include "CtrlShiftZKey.h"
#include "CtrlFKey.h"
#include "CtrlHKey.h"
#include "CtrlPKey.h"

#include "F5Key.h"
#include "CtrlGKey.h"


/*
* 함수명칭:KeyActionCreator
* 기능:생성자
*/
KeyActionCreator::KeyActionCreator(Notepannel* notepannel)
	:notepannel(notepannel) {
}

/*
* 함수명칭:~KeyActionCreator
* 기능:소멸자
*/
KeyActionCreator::~KeyActionCreator() {
}

/*
* 함수명칭:Create
* 기능:입력받은 명령에 맞게 함수를 생성한다.
*/
KeyAction* KeyActionCreator::Create(UINT nChar, UINT nRepCnt, UINT nFlags) {
	KeyAction* keyAction = 0;
	SHORT ctrlKeyState = GetKeyState(VK_CONTROL);
	SHORT shiftKeyState = GetKeyState(VK_SHIFT);
	BOOL isSelected = this->notepannel->isSelected;
	//SHORT shiftKeyState = GetKeyState(VK_SHIFT);

	//BOOL ctrlKeyStateClicked = FALSE;
	//ctrlKeyState = GetKeyState(VK_CONTROL);
	//ctrlKeyStateClicked = ctrlKeyState & 0x8000;
	//(GetKeyState(VK_CONTROL) & 0x8000)
	//(ctrlKeyState & 0x8000)
	//ctrlKeyStateClicked = GetKeyState(VK_CONTROL) & 0x8000;

	//!(shiftKeyState & 0x8000)

	if (nChar == VK_UP && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new UpKey(notepannel);
	}
	else if (nChar == VK_UP && !(ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new ShiftUpKey(notepannel);
	}

	else if (nChar == VK_DOWN && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new DownKey(notepannel);
	}
	else if (nChar == VK_DOWN && !(ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new ShiftDownKey(notepannel);
	}

	else if (nChar == VK_LEFT && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new LeftKey(notepannel);
	}
	else if (nChar == VK_LEFT && !(ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new ShiftLeftKey(notepannel);
	}
	else if (nChar == VK_LEFT && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new CtrlLeftKey(notepannel);
	}
	else if (nChar == VK_LEFT && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new CtrlShiftLeftKey(notepannel);
	}

	else if (nChar == VK_RIGHT && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new RightKey(notepannel);
	}
	else if (nChar == VK_RIGHT && !(ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new ShiftRightKey(notepannel);
	}
	else if (nChar == VK_RIGHT && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new CtrlRightKey(notepannel);
	}
	else if (nChar == VK_RIGHT && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new CtrlShiftRightKey(notepannel);
	}
	
	else if (nChar == VK_HOME && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new HomeKey(notepannel);
	}
	else if (nChar == VK_HOME && !(ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new ShiftHomeKey(notepannel);
	}
	else if (nChar == VK_HOME && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new CtrlHomeKey(notepannel);
	}
	else if (nChar == VK_HOME && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new CtrlShiftHomeKey(notepannel);
	}
	
	else if (nChar == VK_END && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new EndKey(notepannel);
	}
	else if (nChar == VK_END && !(ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new ShiftEndKey(notepannel);
	}
	else if (nChar == VK_END && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new CtrlEndKey(notepannel);
	}
	else if (nChar == VK_END && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new CtrlShiftEndKey(notepannel);
	}

	else if (nChar == VK_BACK && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		keyAction = new BackspaceKey(notepannel);
	}
	else if (nChar == VK_BACK && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		keyAction = new BackspaceKey(notepannel);
		//keyAction = new CtrlBackspaceKey(notepannel);
	}
	else if (nChar == VK_BACK && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		keyAction = new BackspaceKey(notepannel);
		//keyAction = new CtrlShiftBackspaceKey(notepannel);
	}
	else if (nChar == VK_BACK && isSelected == TRUE) {
		keyAction = new BackspaceKey(notepannel);
		//keyAction = new SelectDelete(notepannel);
	}
	else if (nChar == VK_DELETE && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		keyAction = new DeleteKey(notepannel);
	}
	else if (nChar == VK_DELETE && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000) && isSelected == FALSE) {
		keyAction = new DeleteKey(notepannel);
		//keyAction = new CtrlDeleteKey(notepannel);
	}
	else if (nChar == VK_DELETE && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000) && isSelected == FALSE) {
		keyAction = new DeleteKey(notepannel);
		//keyAction = new CtrlShiftDeleteKey(notepannel);
	}
	else if (nChar == VK_DELETE && isSelected == TRUE) {
		keyAction = new DeleteKey(notepannel);
		//keyAction = new SelectDelete(notepannel);
	}

	else if (nChar == VK_PRIOR && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new PageUpKey(notepannel);
	}
	else if (nChar == VK_PRIOR && !(ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new ShiftPageUpKey(notepannel);
	}

	else if (nChar == VK_NEXT && !(ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) {
		keyAction = new PageDownKey(notepannel);
	}
	else if (nChar == VK_NEXT && !(ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) {
		keyAction = new ShiftPageDownKey(notepannel);
	}
	else if (nChar == VK_SHIFT) {
		keyAction = new ShiftKey(this->notepannel);
	}
	
	else if (nChar == 0x41 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+A키를 의미한다
		keyAction = new CtrlAKey(this->notepannel);
	}
	else if (nChar == 0x41 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+A키를 의미한다
		keyAction = new CtrlAKey(this->notepannel);
	}
	else if (nChar == 0x53 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+S키를 의미한다
		keyAction = new CtrlSKey(this->notepannel);
	}
	else if (nChar == 0x53 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+S키를 의미한다
		keyAction = new CtrlShiftSKey(this->notepannel);
	}
	else if (nChar == 0x4E && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+N키를 의미한다
		keyAction = new CtrlNKey(this->notepannel);
	}
	else if (nChar == 0x4E && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+Shift+N키를 의미한다
		//keyAction = new CtrlShiftNKey(this->notepannel); //아직 미구현(이중 클라이언트)
	}
	else if (nChar == 0x4F && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+O키를 의미한다
		keyAction = new CtrlOKey(this->notepannel);
	}
	else if (nChar == 0x4F && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+O키를 의미한다
	}
	else if (nChar == 0x57 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+W키를 의미한다
		keyAction = new CtrlWKey(this->notepannel);
	}
	else if (nChar == 0x57 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+W키를 의미한다
	}
	else if (nChar == VK_OEM_PLUS && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+더하기 키를 의미한다
		keyAction = new CtrlPlusKey(this->notepannel);
	}
	else if (nChar == VK_OEM_PLUS && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+더하기 키를 의미한다
	}
	else if (nChar == VK_OEM_MINUS && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+빼기 키를 의미한다
		keyAction = new CtrlMinusKey(this->notepannel);
	}
	else if (nChar == VK_OEM_MINUS && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+빼기 키를 의미한다
	}
	else if (nChar == 0x30 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+0 키를 의미한다
		keyAction = new CtrlZeroKey(this->notepannel);
	}
	else if (nChar == 0x30 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+0 키를 의미한다
	}
	else if (nChar == 0x43 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+C 키를 의미한다
		keyAction = new CtrlCKey(this->notepannel);
	}
	else if (nChar == 0x43 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+C 키를 의미한다
	}
	else if (nChar == 0x58 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+X 키를 의미한다
	keyAction = new CtrlXKey(this->notepannel);
	}
	else if (nChar == 0x58 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+X 키를 의미한다
	}
	else if (nChar == 0x56 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+X 키를 의미한다
		keyAction = new CtrlVKey(this->notepannel);
	}
	else if (nChar == 0x56 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+X 키를 의미한다
	}
	else if (nChar == 0x5A && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+Z 키를 의미한다
		keyAction = new CtrlZKey(this->notepannel);
	}
	else if (nChar == 0x5A && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+Z 키를 의미한다
		keyAction = new CtrlShiftZKey(this->notepannel);
	}
	else if (nChar == 0x46 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+F 키를 의미한다
		keyAction = new CtrlFKey(this->notepannel);
	}
	else if (nChar == 0x46 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+F 키를 의미한다
	}
	else if (nChar == 0x48 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+H 키를 의미한다
		keyAction = new CtrlHKey(this->notepannel);
	}
	else if (nChar == 0x48 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+H 키를 의미한다
	}
	else if (nChar == 0x50 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+P 키를 의미한다
		keyAction = new CtrlPKey(this->notepannel);
	}
	else if (nChar == 0x50 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+P 키를 의미한다
	}
	else if (nChar == VK_F5) {
		keyAction = new F5Key(this->notepannel);
	}
	else if (nChar == 0x47 && (ctrlKeyState & 0x8000) && !(shiftKeyState & 0x8000)) { //Ctrl+G 키를 의미한다
		keyAction = new CtrlGKey(this->notepannel);
	}
	else if (nChar == 0x47 && (ctrlKeyState & 0x8000) && (shiftKeyState & 0x8000)) { //Ctrl+Shift+G 키를 의미한다
	}
#if 0
	else if () {
	}
	else if () {
	}
	else if () {
	}
#endif

	return keyAction;
}