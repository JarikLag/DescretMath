#pragma once

#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>

class String {
public:
	String();
	String(const char* str);
	String(const char ch);
	String(const String& str);
	String(size_t size, char character);
	~String();

	size_t getSize() const;
	void swap(String& str);
	const char* c_str() const;
	void append(const String& str);
	void insert(size_t pos, const String& str);
	void clear();
	bool isEmpty() const;
	void erase(size_t pos, size_t len);
	String substr(size_t pos, size_t len) const;

	String& operator=(const String& str);
	char& operator[](size_t index);
	char operator[](size_t index) const;
	String& operator+=(const String& str);

	friend std::ostream& operator<<(std::ostream& out, const String& str);
	friend std::istream& operator>>(std::istream& in, String& str);
private:
	static const size_t sizeOfBuffer = 1 << 16;
	size_t mSize;
	char* mData;
};

String operator+(String res, const String& str);