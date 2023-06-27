//LineWrapper.h
/*
* ���ϸ�Ī:LineWrapper.h
* ���:�Է¹��� ���̸� �ڵ������ϰ� ��ġ�� �����ϴ� �Լ��� ���
* �ۼ���:������
* �ۼ�����:2022/12/19
*/
#ifndef _LINEWRAPPER_H
#define _LINEWRAPPER_H

class Notepannel;
class Glyph;
class LineWrapper {
public:
	LineWrapper(Notepannel* notepannel);
	~LineWrapper();
	void Warp(Glyph* paper, int width);
	void UnWarp(Glyph* paper);
private:
	Notepannel* notepannel;
};

#endif // !_LINEWRAPPER_H

