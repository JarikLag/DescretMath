#pragma once

#include <iostream>

template <typename Tx>
struct TestClass {
	explicit TestClass(Tx x) {
		this->x = new Tx();
		*(this->x) = x;
	}
	TestClass(const TestClass& inX) {
		this->x = new Tx();
		*this->x = *inX.x;
	}
	~TestClass() { 
		delete this->x;
	}
	Tx get() const {
		return *x;
	}
	void set(Tx i) {
		*(this->x) = i;
	}
private:
	TestClass& operator=(const TestClass& inX);
	Tx *x;
};