#include "Quaternion.hpp"

Quaternion::Quaternion() : mRealPart(0) {
	mImaginaryPart[0] = mImaginaryPart[1] = mImaginaryPart[2] = 0;
}

Quaternion::Quaternion(double a) : mRealPart(a) {
	mImaginaryPart[0] = mImaginaryPart[1] = mImaginaryPart[2] = 0;
}

Quaternion::Quaternion(double a, double i, double j, double k) : mRealPart(a) {
	mImaginaryPart[0] = i;
	mImaginaryPart[1] = j;
	mImaginaryPart[2] = k;
}

Quaternion::Quaternion(const Quaternion& q) : mRealPart(q.mRealPart) {
	mImaginaryPart[0] = q.mImaginaryPart[0];
	mImaginaryPart[1] = q.mImaginaryPart[1];
	mImaginaryPart[2] = q.mImaginaryPart[2];
}

Quaternion::Quaternion(double a, const double(&v)[3]) : mRealPart(a) {
	mImaginaryPart[0] = v[0];
	mImaginaryPart[1] = v[1];
	mImaginaryPart[2] = v[2];
}

Quaternion::Quaternion(const double(&v)[4]) : mRealPart(v[0]) {
	mImaginaryPart[0] = v[1];
	mImaginaryPart[1] = v[2];
	mImaginaryPart[2] = v[3];
}

Quaternion::Quaternion(double a, const std::vector<double> &v) : mRealPart(a) {
	mImaginaryPart[0] = v[0];
	mImaginaryPart[1] = v[1];
	mImaginaryPart[2] = v[2];
}

Quaternion::Quaternion(const std::vector<double> &v) : mRealPart(v[0]) {
	mImaginaryPart[0] = v[1];
	mImaginaryPart[1] = v[2];
	mImaginaryPart[2] = v[3];
}

Quaternion Quaternion::operator()(const std::vector<double>& v) const {
	Quaternion t(0, v);
	t = (*this) * t * (!(*this));
	return t;
}

Quaternion Quaternion::operator()(const double(&v)[3]) const {
	Quaternion t(0, v);
	t = (*this) * t * (!(*this));
	return t;
}

Quaternion::~Quaternion() {}

void swap(Quaternion& a, Quaternion& b) {
	std::swap(a.mRealPart, b.mRealPart);
	std::swap(a.mImaginaryPart, b.mImaginaryPart);
}

double Quaternion::operator[](const size_t index) const {
	if (index < 0 || index > 3) {
		throw std::runtime_error("Quaternion subscript out or range");
	}
	else {
		if (index == 0) {
			return mRealPart;
		}
		else {
			return mImaginaryPart[index - 1];
		}
	}
}

double& Quaternion::operator[](const size_t index) {
	if (index < 0 || index > 3) {
		throw std::runtime_error("Quaternion subscript out or range");
	}
	else {
		if (index == 0) {
			return mRealPart;
		}
		else {
			return mImaginaryPart[index - 1];
		}
	}
}

Quaternion& Quaternion::operator=(const Quaternion& q) {
	if (this != &q) {
		Quaternion tmp(q);
		swap(tmp, *this);
	}
	return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& q) {
	for (int i = 0; i < 4; ++i) {
		(*this)[i] += q[i];
	}
	return *this;
}

Quaternion& Quaternion::operator++() {
	++mRealPart;
	return *this;
}

Quaternion Quaternion::operator++(int) {
	Quaternion q(*this);
	++(*this);
	return q;
}

Quaternion& Quaternion::operator+() {
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& q) {
	for (int i = 0; i < 4; ++i) {
		(*this)[i] -= q[i];
	}
	return *this;
}

Quaternion& Quaternion::operator--() {
	--mRealPart;
	return *this;
}

Quaternion Quaternion::operator--(int) {
	Quaternion q(*this);
	--(*this);
	return q;
}

Quaternion Quaternion::operator-() const {
	Quaternion tmp(*this);
	for (int i = 0; i < 4; ++i) {
		tmp[i] *= -1;
	}
	return tmp;
}

Quaternion& Quaternion::operator*=(const Quaternion& q) {
	Quaternion tmp;
	tmp[0] = (*this)[0] * q[0]
		- (*this)[1] * q[1]
		- (*this)[2] * q[2]
		- (*this)[3] * q[3];
	tmp[1] = (*this)[0] * q[1]
		+ (*this)[1] * q[0]
		+ (*this)[2] * q[3]
		- (*this)[3] * q[2];
	tmp[2] = (*this)[0] * q[2]
		- (*this)[1] * q[3]
		+ (*this)[2] * q[0]
		+ (*this)[3] * q[1];
	tmp[3] = (*this)[0] * q[3]
		+ (*this)[1] * q[2]
		- (*this)[2] * q[1]
		+ (*this)[3] * q[0];
	swap(*this, tmp);
	return *this;
}

Quaternion& Quaternion::operator*=(const double d) {
	for (int i = 0; i < 4; ++i) {
		(*this)[i] *= d;
	}
	return *this;
}

Quaternion Quaternion::operator~() const {
	Quaternion tmp(*this);
	for (int i = 1; i < 4; ++i) {
		tmp[i] *= -1;
	}
	return tmp;
}

double Quaternion::operator*() const {
	return std::sqrt((*this)[0] * (*this)[0]
		+ (*this)[1] * (*this)[1]
		+ (*this)[2] * (*this)[2]
		+ (*this)[3] * (*this)[3]);
}

Quaternion Quaternion::operator!() const {
	return ~(*this) / (*(*this) * *(*this));
}

Quaternion& Quaternion::operator/=(const double d) {
	for (int i = 0; i < 4; ++i) {
		(*this)[i] /= d;
	}
	return *this;
}

Quaternion& Quaternion::operator/=(const Quaternion& q) {
	return *this *= !q;
}

Quaternion& Quaternion::operator%=(const Quaternion& q) {
	(*this) = ~(*this);
	return (*this) *= q;
}

Quaternion& Quaternion::operator&=(const Quaternion& q) {
	*this = ((*this) % q + q % (*this)) / 2;
	return *this;
}

Quaternion& Quaternion::operator|=(const Quaternion& q) {
	*this = ((*this) * q - q * (*this)) / 2;
	return *this;
}

Quaternion& Quaternion::operator^=(const Quaternion& q) {
	*this = ((*this) % q - q % (*this)) / 2;
	return *this;
}

Quaternion& Quaternion::operator<<=(const size_t shift) {
	int realShift = (3 + shift % 3) % 3;
	if (realShift == 1) {
		std::swap((*this)[1], (*this)[2]);
		std::swap((*this)[2], (*this)[3]);
	}
	else if (realShift == 2) {
		std::swap((*this)[1], (*this)[3]);
		std::swap((*this)[2], (*this)[3]);
	}
	return *this;
}

Quaternion Quaternion::operator<<(const size_t shift) {
	Quaternion tmp(*this);
	return tmp <<= shift;
}

Quaternion& Quaternion::operator>>=(const size_t shift) {
	(*this) <<= (3 - shift);
	return *this;
}

Quaternion Quaternion::operator>>(const size_t shift) {
	Quaternion tmp(*this);
	return tmp >>= shift;;
}

bool Quaternion::operator==(const Quaternion& q) const {
	return (std::abs(*(*this) - *q) < EPSILON);
}

bool Quaternion::operator!=(const Quaternion& q) const {
	return !((*this) == q);
}

bool Quaternion::operator<(const Quaternion& q) const {
	return (*(*this) < *q);
}

bool Quaternion::operator<=(const Quaternion& q) const {
	return ((*this) < q || (*this) == q);
}

bool Quaternion::operator>(const Quaternion& q) const {
	return !((*this) <= q);
}

bool Quaternion::operator>=(const Quaternion& q) const {
	return !((*this) < q);
}

bool Quaternion::operator&&(const Quaternion& q) const {
	return bool(*this) && bool(q);
}

bool Quaternion::operator||(const Quaternion & q) const {
	return bool(*this) || bool(q);
}

Quaternion Quaternion::operator->*(const std::vector<bool>& v) const {
	Quaternion t((*this)[0] * v[0], (*this)[1] * v[1], (*this)[2] * v[2], (*this)[3] * v[3]);
	return t;
}

Quaternion Quaternion::operator->*(const bool(&v)[4]) const {
	Quaternion t((*this)[0] * v[0], (*this)[1] * v[1], (*this)[2] * v[2], (*this)[3] * v[3]);
	return t;
}

Quaternion Quaternion::operator()(double a, double b, double c) const {
	Quaternion t(0, a, b, c);
	t = (*this) * t * (!(*this));
	return t;
}

Quaternion::operator bool() const {
	return (*(*this) != 0);
}

Quaternion::operator std::string() const {
	std::string toString = "";
	if (abs((*this)[0]) > EPSILON) {
		toString += std::to_string((*this)[0]);
	}
	if (abs((*this)[1]) > EPSILON) {
		if ((*this)[1] > 0) {
			toString += "+" + std::to_string((*this)[1]) + "i";
		}
		else {
			toString += std::to_string((*this)[1]) + "i";
		}
	}
	if (abs((*this)[2]) > EPSILON) {
		if ((*this)[2] > 0) {
			toString += "+" + std::to_string((*this)[2]) + "j";
		}
		else {
			toString += std::to_string((*this)[2]) + "j";
		}
	}
	if (abs((*this)[3]) > EPSILON) {
		if ((*this)[3] > 0) {
			toString += "+" + std::to_string((*this)[3]) + "k";
		}
		else {
			toString += std::to_string((*this)[3]) + "k";
		}
	}
	if (toString == "") {
		toString = "0";
	}
	if (toString[0] == '+') {
		toString = toString.substr(1);
	}
	return toString;
}

bool Quaternion::isEqual(const Quaternion& q) const {
	bool flag = true;
	if (std::abs((*this)[0] - q[0]) > EPSILON) {
		flag = false;
	} else if (std::abs((*this)[1] - q[1]) > EPSILON) {
		flag = false;
	}
	else if (std::abs((*this)[2] - q[2]) > EPSILON) {
		flag = false;
	}
	else if (std::abs((*this)[3] - q[3]) > EPSILON) {
		flag = false;
	}
	return flag;
}

std::ostream& operator<<(std::ostream& out, const Quaternion& str) {
	out << std::string(str);
	return out;
}

std::istream& operator>>(std::istream& in, Quaternion& str) {
	double a, i, j, k;
	in >> a >> i >> j >> k;
	str = Quaternion(a, i, j, k);
	return in;
}

Quaternion operator+(Quaternion a, const Quaternion& b) {
	return a += b;
}

Quaternion operator-(Quaternion a, const Quaternion& b) {
	return a -= b;
}

Quaternion operator*(Quaternion a, const Quaternion& b) {
	return a *= b;
}

Quaternion operator*(Quaternion a, const double d) {
	return a *= d;
}

Quaternion operator/(Quaternion a, const double d) {
	return a /= d;
}

Quaternion operator/(Quaternion a, const Quaternion& b) {
	return a /= b;
}

Quaternion operator%(Quaternion a, const Quaternion& b) {
	return a %= b;
}

Quaternion operator&(Quaternion a, const Quaternion& b) {
	return a &= b;
}

Quaternion operator|(Quaternion a, const Quaternion& b) {
	return a |= b;
}

Quaternion operator^(Quaternion a, const Quaternion& b) {
	return a ^= b;
}