#include "StringPiece.h"
#include <iostream>
#include <sstream>
#pragma warning(disable : 4996)

MyString StringPiece::getString() const {
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
	if (data == nullptr || strlen(data) > maxChars)
		throw std::invalid_argument("invalid argument");

	strcpy(_data, data);

	_end += strlen(data);
}

void StringPiece::removeAtStart(size_t k) { //if k is more than the number of symbols, all symbols are removed.
	k = k > getLen() ? getLen() : k;

	_start += k;
}

void StringPiece::removeAtEnd(size_t k) { //if k is more than the number of symbols, all symbols are removed.
	k = k > getLen() ? getLen() : k;

	_end -= k;
}

size_t StringPiece::getIndex(size_t index) const {
	return (_start + index) % 16;
}

void StringPiece::changeAt(size_t index, char ch) {
	if (getIndex(index) >= getLen())
		throw std::out_of_range("index out of range");

	_data[getIndex(index)] = ch;
}

StringPiece& operator<<(StringPiece& sp, const char* str) {
	if (str == nullptr || strlen(str) + sp.getLen() > maxChars)
		throw std::invalid_argument("Invalid argument");

	for (size_t i = 0; i < strlen(str); i++)
		sp._data[++sp._end] = str[i];

	return sp;
}

StringPiece& operator<<(StringPiece& sp, int n) {
	std::stringstream ss;

	ss << n;

	char buff[12]; // max num of nums in int with a - and '\0'

	ss >> buff;

	return operator<<(sp, buff);
}

StringPiece& operator>>(const char* str, StringPiece& sp) {
	if (str == nullptr || strlen(str) + sp.getLen() > maxChars)
		throw std::invalid_argument("Invalid argument");

	for (int i = strlen(str) - 1; i >= 0; i--)
		sp._data[--sp._start] = str[i];

	return sp;
}

StringPiece& operator>>(int n, StringPiece& sp) {
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
	return 16 - (_start - _end - 1);
}

void StringPiece::deletePiece() {
	_start = _end = 17;
}

bool StringPiece::isDeleted() const {
	return _start == 17;
}

