#pragma once

#include "Animal.h"

class Bear : public Animal {
public:
	Bear(size_t id, size_t hp);

	std::string roar() const;
};
