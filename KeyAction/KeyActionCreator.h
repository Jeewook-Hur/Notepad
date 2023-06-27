//KeyActionCreator.h
/*
* ���ϸ�Ī:KeyActionCreator.h
* ���:Ű�׼� ���� ���丮�� ���
* �ۼ���:������
* �ۼ�����:20220826
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
