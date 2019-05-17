#include "Unit.h"

Unit::Unit(size_t id, size_t hp) : mId(id), mHp(hp) {}

size_t Unit::id() const {
	return mId;
}

size_t Unit::hp() const {
	return mHp;
}