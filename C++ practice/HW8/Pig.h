#pragma once

#include "Animal.h"

class Pig : public Animal {
public:
	Pig(size_t id, size_t hp);

	std::string oink() const;
};
