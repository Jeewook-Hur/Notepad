//Document.h
/*
* ���ϸ�Ī:Document.h
* ���:�Է¹��� ������ �����ϴ� ������ ���
* �ۼ���:������
* �ۼ�����:20220819
*/
#ifndef _DOCUMENT_H
#define _DOCUMENT_H
#include <string>
using namespace std;

class Glyph;
class Document {
public:
	Document(string path = "", string name = "���� ����", string extention = "txt");
	Document(const Document& source);
	~Document();
	Glyph* Load();
	void Save(Glyph* paper);
	string GetPath() const;
	string GetName() const;
	string GetExtention() const;
private:
	string path;
	string name;
	string extention;
};

inline string Document::GetPath() const {
	return this->path;
}

inline string Document::GetName() const {
	return this->name;
}

inline string Document::GetExtention() const {
	return this->extention;
}

#endif // !_DOCUMENT_H
