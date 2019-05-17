#include "BritishRailMetric.h"

BritishRailMetric::~BritishRailMetric() {}

double BritishRailMetric::calculateDistance(const Point& begin, const Point& end) const {
	return std::sqrt(begin.first * begin.first + begin.second * begin.second) + std::sqrt(end.first * end.first + end.second * end.second);
}
