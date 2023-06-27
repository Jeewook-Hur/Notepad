//Document.cpp
/*
* ���ϸ�Ī:Document.cpp
* ���:�Է¹��� ������ �����ϴ� ������ ���
* �ۼ���:������
* �ۼ�����:20220819
*/
#include "Document.h"
#include "Paper.h"
#include "Line.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "GlyphCreater.h"
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

/*
* �Լ���Ī:Document
* ���:������
*/
Document::Document(string path, string name, string extention)
	:path(path), name(name), extention(extention) {
}
Document::Document(const Document& source) {
	this->path = source.path;
	this->name = source.name;
	this->extention = source.extention;
}

/*
* �Լ���Ī:~Document
* ���:�Ҹ���
*/
Document::~Document() {
}

/*
* �Լ���Ī:Load
* ���:�����ϴ�
*/
Glyph* Document::Load() {
	fstream file;
	string fileName;
	GlyphCreater glyphCreater;
	Glyph* paper = 0;
	Glyph* line = 0;
	Glyph* character = 0;
	char lineLoaded[10000];
	char singleByte[1];
	char doubleByte[2];
	int i;
	
	//���̸� �����. 
	paper = glyphCreater.Create("");

	//��ο� ��ġ�� ������ ����
	fileName = this->path + "//" + this->name + "." + this->extention;
	file.open(fileName, ios::in);

	while (!file.eof()) {//������ ���� �ƴѵ��� �ݺ��Ѵ�. 
		//�������� ���� �д´�. 
		file.getline(lineLoaded, 10000);
		line = glyphCreater.Create("\r\n");
		paper->Add(line);
		i = 0;
		while (lineLoaded[i] != '\0' && i < 10000) {//���� ���̸�ŭ �ݺ��Ѵ�. 
			//�ѱ� ���� ������ �Ѵ�. 
			//(lineLoaded[i] & 0x80)�� TRUE�̸� ���� �ȿ� �����ִٴ� �ǹ��̸� �ƽ�Ű ���� ���̶�� �ǹ��̴�.

			if ((lineLoaded[i] & 0x80) == 0) {//�����̸� ���ڿ� ������ ���´�.
				singleByte[0] = lineLoaded[i];
				character = glyphCreater.Create(singleByte);
			}
			//�ѱ��̸� ��������Ʈ���� �����ؼ� ���ڿ� �ѱ��� ���´�.
			else {
				doubleByte[0] = lineLoaded[i];
				i++; // ���� ���ڷ� �̵��Ѵ�.
				doubleByte[1] = lineLoaded[i];
				character = glyphCreater.Create(doubleByte);
			}
			//���ڸ� �ٿ� ���´�.
			line->Add(character);
			i++; //���� ���ڷ� �̵��Ѵ�. 
		}
		//�������� ���� �д´�. 
		//file.getline(lineLoaded, 1024);
	}
	if (paper->GetLength() == 0) {
		line = glyphCreater.Create("\r\n");
		paper->Add(line);
	}
	file.close();
	return paper;
}

/*
* �Լ���Ī:Save
* ���:�����ϴ�
*/
void Document::Save(Glyph* paper) {
	fstream file;
	Glyph* line = 0;
	string fileName;
	string lineString;
	char lineCharacter[10000];
	int paperLength = -1;
	int charLength = 0;
	int i = 0;
	int j; //�ݺ� ���� ����
	int k; //÷��

	//����� ������ ������ �����
	if (this->path == "") {
		fileName = this->name + "." + this->extention;
	}
	else {
		fileName = this->path + "//" + this->name + "." + this->extention;
	}
	//������ ����
	file.open(fileName, ios::out);
	
	paperLength = paper->GetLength();
	while (i < paperLength) { //������ ���̸�ŭ �ݺ��Ѵ�. 
		//���� ��ġ�� ���� �����´�. 
		line = paper->GetAt(i);
		//���� ������ ������ ���´�. 
		lineString = line->GetExactString();
		//������ ���� �迭�� �Ű����´�. 
		k = 0;
		j = 0;
		charLength = lineString.length();
		while (j < charLength) { //������ ���̸�ŭ �ݺ��Ѵ�. 
			lineCharacter[k] = lineString[k];
			k++;
			j++;
		}
		//���� �迭�� ���Ͽ� ���´�.
		file.write(lineCharacter, charLength);
		if (i < paperLength - 1) {
			//������ ���� �ٲ۴�.
			file << endl;
		}
		i++;
	}
	//������ �ݴ´�.
	file.close();
}

#if 0

#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
	Document* document;
	Glyph* paper;
	Glyph* line = NULL;
	Glyph* character = NULL;
	Long indexLine = -1;
	string paperString;
#if 0
	//���̸� �����.
	paper = new Paper;
	//���̿� ���� �����Ѵ�.
	line = new Line;
	indexLine = paper->Add(line);

	//���̿� '��'�� �����Ѵ�.
	character = new DoubleByteCharacter((char*)"��");
	line = paper->GetAt(indexLine);
	line->Add(character);

	//���̿� 'A'�� �����Ѵ�.
	character = new SingleByteCharacter((char)'A');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//���̿� ���� �����Ѵ�.
	line = new Line;
	indexLine = paper->Add(line);
	//���̿� '��'�� �����Ѵ�.
	character = new DoubleByteCharacter((char*)"��");
	line = paper->GetAt(indexLine);
	line->Add(character);

	//���̿� 'B'�� �����Ѵ�.
	character = new SingleByteCharacter((char)'B');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//���̿� '4'�� �����Ѵ�.
	character = new SingleByteCharacter((char)'4');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//���̿� '5'�� �����Ѵ�.
	character = new SingleByteCharacter((char)'5');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//���̿� ���� �����Ѵ�.
	line = new Line;
	indexLine = paper->Add(line);
	//���̿� '��'�� �����Ѵ�.
	character = new DoubleByteCharacter((char*)"��");
	line = paper->GetAt(indexLine);
	line->Add(character);

	//���̿� 'D'�� �����Ѵ�.
	character = new SingleByteCharacter((char)'D');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//���̿� '7'�� �����Ѵ�.
	character = new SingleByteCharacter((char)'7');
	line = paper->GetAt(indexLine);
	line->Add(character);

	//������ �����. 
	document = new Document();
	//������ �����Ѵ�. 
	document->Save(paper);
	//������ �ҷ��´�. 
	delete paper;
#endif
	//������ �����. 
	document = new Document();

	paper = document->Load();
	
	paperString = paper->GetString();

	cout << static_cast<string>(paperString);

	return 0;
}
#endif