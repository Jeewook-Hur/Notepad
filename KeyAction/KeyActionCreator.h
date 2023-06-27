//KeyActionCreator.h
/*
* 파일명칭:KeyActionCreator.h
* 기능:키액션 생성 팩토리의 헤더
* 작성자:허지욱
* 작성일자:20220826
*/
#ifndef _KEYACTIONCREATOR_H
#define _KEYACTIONCREATOR_H

typedef unsigned int UINT;
class Notepannel;
class KeyAction;
class KeyActionCreator {
public:
	KeyActionCreator(Notepannel* notepannel);
	~KeyActionCreator();
	KeyAction* Create(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	Notepannel* notepannel;
};

#endif // !_KEYACTIONCREATOR_H
