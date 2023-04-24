#include "StringPiece.h"
#include <iostream>
#include <sstream>
#pragma warning(disable : 4996)

void StringPiece::checkDeleted() const {
	if (isDeleted())
		throw std::exception("The piece at this index is deleted. Add a new piece at this index first");
}


MyString StringPiece::getString() const {
	checkDeleted();

	char temp[17]{ '\0' };

	size_t index = _start;

	for (size_t i = 0; i < getLen(); i++) {
		if (index >= 16)
			index -= 16;
		temp[i] = _data[index++];
	}
	return MyString(temp);
}

void StringPiece::setData(const char* data) {
	checkDeleted();

	if (data == nullptr || strlen(data) > maxChars)
		throw std::invalid_argument("invalid argument");

	strcpy(_data, data);

	_end += strlen(data);
}

void StringPiece::removeAtStart(size_t k) { //if k is more than the number of symbols, all symbols are removed.
	checkDeleted();

	k = k > getLen() ? getLen() : k;

	_start += k;
}

void StringPiece::removeAtEnd(size_t k) { //if k is more than the number of symbols, all symbols are removed.
	checkDeleted();

	k = k > getLen() ? getLen() : k;

	_end -= k;
}

size_t StringPiece::getIndex(size_t index) const {
	checkDeleted();

	return (_start + index) % 16;
}

void StringPiece::changeAt(size_t index, char ch) {
	checkDeleted();

	if (getIndex(index) >= getLen())
		throw std::out_of_range("index out of range");

	_data[getIndex(index)] = ch;
}

StringPiece& operator<<(StringPiece& sp, const char* str) {
	sp.checkDeleted();

	if (str == nullptr || strlen(str) + sp.getLen() > maxChars)
		throw std::invalid_argument("Invalid argument");

	for (size_t i = 0; i < strlen(str); i++)
		sp._data[++sp._end] = str[i];

	return sp;
}

StringPiece& operator<<(StringPiece& sp, int n) {
	sp.checkDeleted();

	std::stringstream ss;

	ss << n;

	char buff[12]; // max num of nums in int with a - and '\0'

	ss >> buff;

	return operator<<(sp, buff);
}

StringPiece& operator>>(const char* str, StringPiece& sp) {
	sp.checkDeleted();

	if (str == nullptr || strlen(str) + sp.getLen() > maxChars)
		throw std::invalid_argument("Invalid argument");

	for (int i = strlen(str) - 1; i >= 0; i--)
		sp._data[--sp._start] = str[i];

	return sp;
}

StringPiece& operator>>(int n, StringPiece& sp) {
	sp.checkDeleted();

	std::stringstream ss;

	ss << n;

	char buff[12]; // max num of nums in int with a - and '\0'

	ss >> buff;

	return operator>>(buff, sp);
}

StringPiece::StringPiece(const char* str) {
	setData(str);
}

size_t StringPiece::getLen() const {
	checkDeleted();

	return 16 - (_start - _end - 1);
}

void StringPiece::deletePiece() {
	_start = _end = 17;
}

bool StringPiece::isDeleted() const {
	return _start == 17;
}

