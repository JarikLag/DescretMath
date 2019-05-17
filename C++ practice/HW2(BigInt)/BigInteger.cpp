// BigInteger.cpp: определяет точку входа для консольного приложения.
//

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include "BigInteger.hpp"

const int base = 1000000000;
const int baseNumber = 9;

BigInteger::BigInteger(long long val) {
	if (val < 0) {
		sign = -1;
		val *= -1;
	}
	else {
		sign = 1;
	}
	data.clear();
	for (; val > 0; val /= base) {
		data.push_back(val % base);
	}
}

BigInteger::BigInteger(const std::string &s) {
	read(s);
}

BigInteger::BigInteger(const BigInteger &val) {
	data = val.data;
	sign = val.sign;
}

BigInteger::BigInteger(BigInteger &&val) {
	data = std::move(val.data);
	sign = val.sign;
}

 BigInteger& BigInteger::operator=(BigInteger &val) {
	data = val.data;
	sign = val.sign;
	return *this;
}

BigInteger BigInteger::operator+(const BigInteger &val) const {
	if (sign == val.sign) {
		BigInteger ans = val;
		for (int i = 0, carry = 0; i < int(std::max(val.data.size(), data.size())) || carry; i++) {
			if (i == int(ans.data.size())) {
				ans.data.push_back(0);
			}
			if (i < int(data.size())) {
				ans.data[i] += data[i];
			}
			ans.data[i] += carry;
			if (ans.data[i] >= base) {
				carry = 1;
			}
			else {
				carry = 0;
			}
			if (carry)
				ans.data[i] -= base;
		}
		return ans;
	}
	else {
		return *this - (-val);
	}
}

BigInteger BigInteger::operator-(const BigInteger &val) const {
	if (sign == val.sign) {
		if (abs() >= val.abs()) {
			BigInteger ans = *this;
			for (int i = 0, carry = 0; i < int(val.data.size()) || carry; i++) {
				if (i < int(val.data.size())) {
					ans.data[i] -= val.data[i];
				}
				ans.data[i] -= carry;
				if (ans.data[i] < 0) {
					carry = 1;
				}
				else {
					carry = 0;
				}
				if (carry)
					ans.data[i] += base;
			}
			ans.trim();
			return ans;
		}
		return -(val - *this);
	}
	return *this + (-val);
}

BigInteger & BigInteger::operator+=(const BigInteger &val) {
	*this = *this + val;
	return *this;
}

BigInteger & BigInteger::operator-=(const BigInteger &val) {
	*this = *this - val;
	return *this;
}

BigInteger BigInteger::operator-() const {
	BigInteger res = *this;
	res.sign = -sign;
	return res;
}

BigInteger BigInteger::operator+() const {
	return *this;
}

bool BigInteger::operator<(const BigInteger &val) const {
	if (sign != val.sign)
		return sign < val.sign;
	if (data.size() != val.data.size())
		return data.size() < val.data.size();
	for (int i = int(data.size()) - 1; i >= 0; i--)
		if (data[i] != val.data[i])
			return data[i] * sign < val.data[i] * val.sign;
	return false;
}

bool BigInteger::operator>(const BigInteger &val) const {
	return val < *this;
}
bool BigInteger::operator<=(const BigInteger &val) const {
	return !(val < *this);
}
bool BigInteger::operator>=(const BigInteger &val) const {
	return !(*this < val);
}
bool BigInteger::operator==(const BigInteger &val) const {
	return !(*this < val) && !(val < *this);
}
bool BigInteger::operator!=(const BigInteger &val) const {
	return *this < val || val < *this;
}

BigInteger BigInteger::abs() const {
	BigInteger res = *this;
	res.sign *= res.sign;
	return res;
}

void BigInteger::trim() {
	while (!data.empty() && data.back() == 0) {
		data.pop_back();
	}
	if (data.empty()) {
		sign = 1;
	}
}

void BigInteger::read(const std::string &s) {
	sign = 1;
	data.clear();
	int pos = 0;
	if (s[pos] == '-' || s[pos] == '+') {
		if (s[pos] == '-') {
			sign = -1;
		}
		pos++;
	}
	for (int i = int(s.size()) - 1; i >= pos; i -= baseNumber) {
		int x = 0;
		for (int j = std::max(pos, i - baseNumber + 1); j <= i; j++)
			x = x * 10 + (s[j] - '0');
		data.push_back(x);
	}
	trim();
}

std::ostream & operator<<(std::ostream &stream, const BigInteger &val) {
	if (val.sign == -1) {
		stream << '-';
	}
	if (val.data.empty()) {
		stream << 0;
	}
	else {
		stream << val.data.back();
	}
	for (int i = int(val.data.size()) - 2; i >= 0; i--) {
		stream << std::setw(baseNumber) << std::setfill('0') << val.data[i];
	}
	return stream;
}

std::istream & operator>>(std::istream &stream, BigInteger &val) {
	std::string s;
	stream >> s;
	val.read(s);
	return stream;
}