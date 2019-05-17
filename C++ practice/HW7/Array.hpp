#include "Array.h"

template<typename T>
Array<T>::Array(size_t size, const T& value) : mSize(size) {
	mData = static_cast<T*>(operator new[](size * sizeof(T)));
	for (size_t i = 0; i < mSize; ++i) {
		new (mData + i) T(value);
	}
}

template<typename T>
Array<T>::Array() : mSize(0), mData(0) {}

template<typename T>
Array<T>::Array(Array&& arr) : Array() {
	swap(arr);
}

template<typename T>
Array<T>::~Array() {
	for (size_t i = 0; i < mSize; ++i) {
		mData[i].~T();
	}
	operator delete[] (mData);
}

template<typename T>
Array<T>::Array(const Array& arr) : mSize(arr.mSize) {
	mData = static_cast<T*>(operator new[](mSize * sizeof(T)));
	for (size_t i = 0; i < mSize; ++i) {
		new (mData + i) T(arr[i]);
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& arr) {
	if (&arr != this) {
		Array(arr).swap(*this);
	}
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& arr) {
	swap(arr);
	return *this;
}

template<typename T>
size_t Array<T>::size() const {
	return mSize;
}

template<typename T>
T& Array<T>::operator[](size_t index) {
	if (index >= mSize) {
		throw std::runtime_error("Array subscript out of range");
		return mData[0];
	}
	else {
		return mData[index];
	}
}

template<typename T>
const T& Array<T>::operator[](size_t index) const {
	if (index >= mSize) {
		throw std::runtime_error("Array subscript out of range");
		return mData[0];
	}
	else {
		return mData[index];
	}
}

template<typename T>
void Array<T>::swap(Array& arr) {
	std::swap(mData, arr.mData);
	std::swap(mSize, arr.mSize);
}