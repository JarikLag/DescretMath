#include "ManhattanMetric.h"

ManhattanMetric::~ManhattanMetric() {}

double ManhattanMetric::calculateDistance(const Point& begin, const Point& end) const {
	return std::abs(end.first - begin.first) + std::abs(end.second - begin.second);
}