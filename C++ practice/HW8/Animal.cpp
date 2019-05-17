#include "Animal.h"

Animal::Animal(const std::string& name, size_t id, size_t hp) : Unit(id, hp), mName(name) {}

const std::string& Animal::name() const {
	return mName;
}
