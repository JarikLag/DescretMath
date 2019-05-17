#include "Bear.h"

Bear::Bear(size_t id, size_t hp) : Unit(id, hp), Animal("bear", id, hp) {}

std::string Bear::roar() const {
	return "Roar";
}
