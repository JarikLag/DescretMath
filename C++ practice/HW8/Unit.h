#pragma once

#include <string>

class Unit {
public:
	Unit(size_t id, size_t hp);

	size_t id() const;
	size_t hp() const;
private:
	size_t mId;
	size_t mHp;
};