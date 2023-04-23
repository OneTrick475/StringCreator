#pragma once

const unsigned maxChars = 16;

class StringPiece {
private:
	char _data[maxChars + 1]{ '\0' };
	int _len = 0; // -1 indicated that the piece is deleted

public:
	StringPiece() = default;
	explicit StringPiece(const char* str); // explicit to avoid implicit conversion from nullptr. this is needed for the remove method

	int getLen() const;
	const char* getData() const;
	void setData(const char* data);

	void removeAtStart(size_t k);
	void removeAtEnd(size_t k);

	void changeAt(size_t index, char ch);

	void deletePiece();

	bool isDeleted() const;

	friend StringPiece& operator<<(StringPiece& sp, const char* str);
	friend StringPiece& operator<<(StringPiece& sp, int n);
	friend StringPiece& operator>>(const char* str, StringPiece& sp);
	friend StringPiece& operator>>(int n, StringPiece& sp);
};
