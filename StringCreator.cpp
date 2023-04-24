#include "StringCreator.h"
#include "MyString.h"
#include <iostream>
#pragma warning(disable : 4996)

void StringCreator::resize() {
	_capacity *= 2;

	StringPiece* temp = new StringPiece[_capacity];

	for(size_t i = 0; i < _length; i++) {
		temp[i] = _pieces[i];
	}
	free();

	_pieces = temp;
}

StringCreator::StringCreator(size_t capacity) : _capacity(capacity) {
	_pieces = new StringPiece[_capacity];
}

StringCreator::StringCreator(const StringCreator& other) {
	copyFrom(other);
}

StringCreator& StringCreator::operator=(const StringCreator& other) {
	if(this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

StringCreator::~StringCreator() {
	free();
}

void StringCreator::free() {
	delete[] _pieces;
	_pieces = nullptr;
}

void StringCreator::copyFrom(const StringCreator& other) {
	_capacity = other._capacity;
	_pieces = new StringPiece[_capacity];

	while (_length < other._length) {
		_pieces[_length] = other._pieces[_length];
		_length++;
	}
}

void StringCreator::addPiece() {
	if (_length == _capacity)
		resize();

	_length++;
}


void StringCreator::addPiece(const char* str) {
	if (str == nullptr || strlen(str) > maxChars)
		throw std::invalid_argument("Invalid argument");

	if (_length == _capacity)
		resize();

	_pieces[_length++] = StringPiece(str);
}

void StringCreator::addPiece(const char* str, size_t index) {
	if (str == nullptr || strlen(str) > maxChars)
		throw std::invalid_argument("Invalid argument");
	if(index > _length)
		throw std::out_of_range("index out of range");

	if (index == _length)
		addPiece(str);
	else
		_pieces[index] = StringPiece(str);
}


void StringCreator::swap(size_t first, size_t second) const{
	if(first >= _length || second >= _length) 
		throw std::out_of_range("index out of range");

	StringPiece temp = _pieces[first];
	_pieces[first] = _pieces[second];
	_pieces[second] = temp;
}

void StringCreator::remove(size_t index) {
	if(index > _length) 
		throw std::out_of_range("index out of range");

	if (index == _length) {
		_length--;
		return;
	}

	_pieces[index].deletePiece();
}

unsigned StringCreator::getStrLen() const { // O(n), n = number of StringPieces
	size_t len = 0;						// we could store the len and make it O(1) but the optimization wont have a significant impact and 
											// will add complexity in a lot of functions making the code much less maintainable
	for (size_t i = 0; i < _length; i++)
		len += (_pieces[i].isDeleted() ? 20 : _pieces[i].getLen());

	return len;
}

MyString StringCreator::getString() const { // not returning by & because the string dies at the end of the function scope
	size_t len = getStrLen();
	char* str = new char[len + 1]{'\0'};

	for(size_t i = 0; i < _length; i++)
		strcat(str, (_pieces[i].isDeleted() ? "                    " : _pieces[i].getString().c_str())); // sorry xd
	
	MyString result = MyString(str);
	delete[] str;
	return result;
}

StringPiece& StringCreator::operator[](size_t index) {
	return _pieces[index];
}

StringPiece StringCreator::operator[](size_t index) const {
	return _pieces[index];
}



