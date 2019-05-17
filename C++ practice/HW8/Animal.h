#pragma once

#include <string>
#include "Unit.h"

class Animal : public virtual Unit {
public:
	Animal(const std::string& name, size_t id, size_t hp);

	const std::string& name() const;
private:
	std::string mName;
};
