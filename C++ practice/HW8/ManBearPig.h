#pragma once

#include "Man.h"
#include "Bear.h"
#include "Pig.h"

class ManBearPig : public Man, public Bear, public Pig {
public:
	ManBearPig(size_t id, size_t hp, size_t iq);
};