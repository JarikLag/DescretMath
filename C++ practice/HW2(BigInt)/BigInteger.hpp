#pragma once

#include <fstream>
#include <vector>

class BigInteger {
public:
	explicit BigInteger(long long val = 0);
	explicit BigInteger(const std::string & s);

	BigInteger(const BigInteger &);
	BigInteger(BigInteger &&);

	BigInteger& operator=(BigInteger &val);
	bool operator<(const BigInteger &val) const;
	bool operator>(const BigInteger &val) const;
	bool operator<=(const BigInteger & v) const;
	bool operator>=(const BigInteger & v) const;
	bool operator==(const BigInteger & v) const;
	bool operator!=(const BigInteger & v) const;
	BigInteger abs() const;

	BigInteger & operator +=(const BigInteger &val);
	BigInteger operator +(const BigInteger &val) const;
	BigInteger & operator -=(const BigInteger &val);
	BigInteger operator-() const;
	BigInteger operator+() const;
	BigInteger operator -(const BigInteger &val) const;
private:
	friend std::ostream & operator <<(std::ostream &stream, const BigInteger &num);
	friend std::istream & operator >>(std::istream &stream, BigInteger &num);

	void trim();
	void read(const std::string & s);

	std::vector<int> data;
	int sign;
};

std::ostream & operator <<(std::ostream &, const BigInteger &);
std::istream & operator >>(std::istream &, BigInteger &);