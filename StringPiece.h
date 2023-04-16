#pragma once

const unsigned maxChars = 16;

class StringPiece {
private:
	char _data[maxChars + 1]{'\0'};
	unsigned _len = 0;

public:
	const char* getData() const;
	void setData(const char* data);

	void removeAtStart(unsigned k);
	void removeAtEnd(unsigned k);

	void changeAt(unsigned index, char ch);

	friend StringPiece& operator<<(StringPiece& sp, const char* str);
	friend StringPiece& operator>>(const char* str, StringPiece& sp);
};