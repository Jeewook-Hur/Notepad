//CharacterMatrix.h
/*
* ���ϸ�Ī:CharacterMatrix.h
* ���:������ Ư¡�� �����ϴ� ������ ���
* �ۼ���:������
* �ۼ�����:2022/8/5
*/
#ifndef _CHARACTERMATRIX_H
#define _CHARACTERMATRIX_H
#include<afxwin.h>

class Notepannel;
class Glyph;
class CharacterMatrix {
public:
	CharacterMatrix(Notepannel* notepannel);
	CharacterMatrix(const CharacterMatrix& source);
	~CharacterMatrix();
	int GetCharacterWidth(Glyph* character);
	int GetCharacterWidth(Glyph* line, int order);
	int GetDoubleByteWidth();
	int GetLineWidth(Glyph* line);
	int GetLineWidth(Glyph* line, int current);
	int GetLineHeight(int lineOrder);
	int FindNearWidthPosition(Glyph* line, int widthCompare);
	int FindNearWidthPositionDown(Glyph* line, int widthCompare);
	int FindNearHeightPosition(int heightCompare);
	//int CalculateTabWidth(Glyph* line, int order);
	int(*widths);
	int height;
	int averageWidth;
private:
	Notepannel* notepannel;
};


#endif // !_CHARACTERMATRIX_H