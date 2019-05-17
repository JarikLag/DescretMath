#include "Man.h"

Man::Man(size_t id, size_t hp, size_t iq) : Unit(id, hp), mIq(iq) {}

const std::string Man::say() const {
	return "I'm human being";
}

size_t Man::iq() const {
	return mIq;
}