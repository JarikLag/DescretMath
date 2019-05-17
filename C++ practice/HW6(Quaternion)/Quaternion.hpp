#pragma once

#include <type_traits>
#include <vector>
#include <string>
#include <exception>

class Quaternion {
public:
	Quaternion();
	Quaternion(double a);
	Quaternion(double a, double i, double j, double k);
	Quaternion(double a, const double(&v)[3]);
	Quaternion(const double(&v)[4]);
	Quaternion(double a, const std::vector<double> &v);
	Quaternion(const std::vector<double> &v);
	Quaternion(const Quaternion &q);
	~Quaternion();

	double operator[](const size_t index) const;
	double& operator[](const size_t index);
	Quaternion& operator=(const Quaternion& q);
	Quaternion& operator+=(const Quaternion& q);
	Quaternion& operator++();
	Quaternion operator++(int);
	Quaternion& operator+();
	Quaternion& operator-=(const Quaternion& q);
	Quaternion& operator--();
	Quaternion operator--(int);
	Quaternion operator-() const;
	Quaternion& operator*=(const Quaternion& q);
	Quaternion& operator*=(const double d);
	Quaternion operator~() const;
	double operator*() const;
	Quaternion operator!() const;
	Quaternion& operator/=(const double d);
	Quaternion& operator/=(const Quaternion& q);
	Quaternion& operator%=(const Quaternion& q);
	Quaternion& operator&=(const Quaternion& q);
	Quaternion& operator|=(const Quaternion& q);
	Quaternion& operator^=(const Quaternion& q);
	Quaternion& operator<<=(const size_t shift);
	Quaternion operator<<(const size_t shift);
	Quaternion& operator>>=(const size_t shift);
	Quaternion operator>>(const size_t shift);
	bool operator==(const Quaternion& q) const;
	bool operator!=(const Quaternion& q) const;
	bool operator<(const Quaternion& q) const;
	bool operator<=(const Quaternion& q) const;
	bool operator>(const Quaternion& q) const;
	bool operator>=(const Quaternion& q) const;
	bool operator&&(const Quaternion& q) const;
	bool operator||(const Quaternion& q) const;
	Quaternion operator->*(const std::vector<bool>& v) const;
	Quaternion operator->*(const bool(&v)[4]) const;
	Quaternion operator()(const double a, const double b, const double c) const;
	Quaternion operator()(const std::vector<double>& v) const;
	Quaternion operator()(const double(&v)[3]) const;

	explicit operator bool() const;
	operator std::string() const;

	friend void swap(Quaternion& a, Quaternion& b);
	friend std::ostream& operator<<(std::ostream& out, const Quaternion& str);
	friend std::istream& operator>>(std::istream& in, Quaternion& str);

	bool isEqual(const Quaternion& q) const;
private:
	const double EPSILON = std::numeric_limits<double>::epsilon();
	double mRealPart;
	double mImaginaryPart[3];
};

Quaternion operator+(Quaternion a, const Quaternion& b);
Quaternion operator-(Quaternion a, const Quaternion& b);
Quaternion operator*(Quaternion a, const Quaternion& b);
Quaternion operator*(Quaternion a, const double d);
Quaternion operator/(Quaternion a, const double d);
Quaternion operator/(Quaternion a, const Quaternion& b);
Quaternion operator%(Quaternion a, const Quaternion& b);
Quaternion operator&(Quaternion a, const Quaternion& b);
Quaternion operator|(Quaternion a, const Quaternion& b);
Quaternion operator^(Quaternion a, const Quaternion& b);