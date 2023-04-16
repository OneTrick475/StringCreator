#include "StringPiece.h"
#include <iostream>
#pragma warning(disable : 4996)

const char* StringPiece::getData() const {
	return _data;
}

void StringPiece::setData(const char* data) {
	if (data == nullptr || strlen(data) > maxChars)
		throw std::invalid_argument("invalid argument");

	strcpy(_data, data);

	_len = strlen(data);
}

void StringPiece::removeAtStart(unsigned k) { //if k is more than the number of symbols, all symbols are removed.
	k = k > _len ? _len : k;

	for (unsigned i = 0; i <= _len - k; i++)
		_data[i] = _data[i + k];

	_len -= k;
}

void StringPiece::removeAtEnd(unsigned k) { //if k is more than the number of symbols, all symbols are removed.
	k = k > _len ? _len : k;

	_len -= k;

	_data[_len] = '\0';
}

void StringPiece::changeAt(unsigned index, char ch) {
	if (index >= _len)
		throw std::out_of_range("index out of range");

	_data[index] = ch;
}

StringPiece& operator<<(StringPiece& sp, const char* str) {
	if (str == nullptr || strlen(str) + sp._len > maxChars)
		throw std::invalid_argument("Invalid argument");

	strcat(sp._data, str);

	sp._len += strlen(str);

	return sp;
}

StringPiece& operator>>(const char* str, StringPiece& sp) {
	if (str == nullptr || strlen(str) + sp._len > maxChars)
		throw std::invalid_argument("Invalid argument");

	char temp[maxChars + 1];
	strcpy(temp, str);
	strcat(temp, sp._data);
	
	strcpy(sp._data, temp);

	sp._len += strlen(str);

	return sp;
}
