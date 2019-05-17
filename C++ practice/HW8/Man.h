#pragma once

#include "Unit.h"

class Man : public virtual Unit {
public:
	Man(size_t id, size_t hp, size_t iq);

	const std::string say() const;

	size_t iq() const;
private:
	size_t mIq;
};