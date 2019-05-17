#include "ManBearPig.h"

ManBearPig::ManBearPig(size_t id, size_t hp, size_t iq) : Unit(id, hp), Man(id, hp, iq), Bear(id, hp), Pig(id, hp) {}