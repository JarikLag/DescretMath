#include "String.h"

String::String() {
	mSize = 0;
	mData = new char[1];
	mData[0] = '\0';
}

String::String(const char* str) {
	size_t sz = strlen(str);
	mSize = sz;
	mData = new char[sz + 1];
	strncpy(mData, str, sz);
	mData[sz] = '\0';
}

String::String(const char ch) : mSize(1), mData(new char[2]) {
	mData[0] = ch;
	mData[1] = '\0';
}

String::String(const String& str) : mSize(str.getSize()), mData(new char[str.getSize() + 1]) {
	strcpy(mData, str.mData);
}

String::String(size_t size, char character) : mSize(size), mData(new char[size + 1]) {
	for (int i = 0; i < size; ++i) {
		mData[i] = character;
	}
	mData[size] = '\0';
}

String::~String() {
	delete[] mData;
}

size_t String::getSize() const {
	return mSize;
}

void String::swap(String& str) {
	std::swap(mSize, str.mSize);
	std::swap(mData, str.mData);
}

const char* String::c_str() const {
	return mData;
}

void String::append(const String& str) {
	*this += str;
}

void String::insert(size_t pos, const String& str) {
	if (pos > mSize) {
		throw std::runtime_error("String subscript out of range");
	}
	else {
		size_t tmpSize = str.mSize + mSize;
		char* tmpData = new char[tmpSize + 1];
		strncpy(tmpData, mData, pos);
		strncpy(tmpData + pos, str.mData, str.mSize);
		strncpy(tmpData + pos + str.mSize, mData + pos, mSize - pos);
		tmpData[tmpSize] = '\0';
		delete[] mData;
		mSize = tmpSize;
		mData = tmpData;
	}
}

void String::clear() {
	*this = "";
}

bool String::isEmpty() const {
	return mSize > 0;
}

void String::erase(size_t pos, size_t len) {
	if (pos + len > mSize) {
		throw std::runtime_error("Attempt to erase non-existent characters");
	}
	else {
		char* tmpData = new char[mSize - len + 1];
		strncpy(tmpData, mData, pos);
		strncpy(tmpData + pos, mData + pos + len, mSize - pos - len);
		tmpData[mSize - len] = '\0';
		std::swap(mData, tmpData);
		mSize -= len;
		delete[] tmpData;
	}
}

String String::substr(size_t pos, size_t len) const {
	if (pos + len >= mSize) {
		throw std::runtime_error("Attempt to create substring from non-existent characters");
	}
	else {
		char* tmpData = new char[len + 1];
		tmpData[len] = '\0';
		for (int i = 0; i < len; ++i) {
			tmpData[i] = mData[i + pos];
		}
		String res(tmpData);
		delete[] tmpData;
		return res;
	}
}

String& String::operator=(const String& str) {
	if (this != &str) {
		String(str).swap(*this);
	}
	return *this;
}

char& String::operator[](size_t index) {
	if (index >= mSize) {
		throw std::runtime_error("String subscript out of range");
		return mData[0];
	}
	else {
		return mData[index];
	}
}

char String::operator[](size_t index) const {
	if (index >= mSize) {
		throw std::runtime_error("String subscript out of range");
		return mData[0];
	}
	else {
		return mData[index];
	}
}

String operator+(String res, const String& str) {
	return res += str;
}

String& String::operator+=(const String& str) {
	size_t tmpSize = mSize + str.mSize;
	char* tmpData = new char[tmpSize + 1];
	std::strncpy(tmpData, mData, mSize);
	std::strncpy(tmpData + mSize, str.mData, str.mSize);
	tmpData[tmpSize] = '\0';
	delete[] mData;
	mData = tmpData;
	mSize = tmpSize;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
	out << str.c_str();
	return out;
}

std::istream& operator>>(std::istream& in, String& str) {
	str.clear();
	char* tmpData = new char[String::sizeOfBuffer + 1];
	tmpData[String::sizeOfBuffer] = '\0';
	char c;
	int i = 0;
	while (1) {
		in.get(c);
		if (c == ' ' || c == '\n' || c == '\r' || c == '\r\n') {
			tmpData[i] = '\0';
			str += tmpData;
			break;
		}
		tmpData[i] = c;
		++i;
		if (i == String::sizeOfBuffer) {
			str += tmpData;
			i = 0;
		}
	}
	delete[] tmpData;
	return in;
}