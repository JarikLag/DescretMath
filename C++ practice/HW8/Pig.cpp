#include "Pig.h"

Pig::Pig(size_t id, size_t hp) : Unit(id, hp), Animal("pig", id, hp) {}

std::string Pig::oink() const {
	return "Oink-Oink!";
}
