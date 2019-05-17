#include <cstdio>
#include <algorithm>
#include <stdexcept>

#ifndef TEMPLATE_ARRAY_H
#define TEMPLATE_ARRAY_H

template <typename T>
class Array {
public:
	explicit Array(size_t size, const T& value = T());
	Array();
	Array(Array&&);  //from #9
	Array(const Array&);
	~Array();

	Array& operator=(const Array&);
	Array& operator=(Array&&); //from #9
	size_t size() const;

	T& operator[](size_t);
	const T& operator[](size_t) const;
private:
	size_t mSize;
	T* mData;
	void swap(Array&);
};

#include "Array.hpp"
#endif //TEMPLATE_ARRAY_H