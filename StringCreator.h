#pragma once
#include "MyString.h"
#include "StringPiece.h"

class StringCreator {
private:
	StringPiece* _pieces = nullptr;
	size_t _capacity = 0;
	size_t _length = 0;

	void copyFrom(const StringCreator& other);
	void free();

	void resize();

public:
	StringCreator() = delete;
	StringCreator(size_t capacity);
	StringCreator(const StringCreator& other);
	StringCreator& operator=(const StringCreator& other);
	~StringCreator();

	void addPiece();
	void addPiece(const char* str);
	void addPiece(const char* str, size_t index);
	void swap(size_t first, size_t second) const;
	void remove(size_t index);
	unsigned getStrLen() const;
	MyString getString() const;

	StringPiece& operator[](size_t index);
	StringPiece operator[](size_t index) const;
};