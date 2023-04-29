#pragma once
#include "MyString.h"

const unsigned maxChars = 16;

class StringPiece {
private:
	char _data[maxChars];
	int _start = 16; // we dont really need char* here, we can just use indexes
	int _end = -1;

	size_t getIndex(size_t index) const;
	void checkDeleted() const;

public:
	StringPiece() = default;
	StringPiece(const char* str); 

	size_t getLen() const;
	MyString getString() const;
	void setData(const char* data);

	void removeAtStart(size_t k);
	void removeAtEnd(size_t k);

	void changeAt(size_t index, char ch);
	char getAt(size_t index) const;

	void deletePiece();
	bool isDeleted() const;

	friend StringPiece& operator<<(StringPiece& sp, const char* str);
	friend StringPiece& operator<<(StringPiece& sp, int n);
	friend StringPiece& operator>>(const char* str, StringPiece& sp);
	friend StringPiece& operator>>(int n, StringPiece& sp);
};
