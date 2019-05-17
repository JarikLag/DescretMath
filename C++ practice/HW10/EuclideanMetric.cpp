#include "EuclideanMetric.h"

EuclideanMetric::~EuclideanMetric() {}

double EuclideanMetric::calculateDistance(const Point& begin, const Point& end) const {
	return std::sqrt((end.first - begin.first) * (end.first - begin.first) + (end.second - begin.second) * (end.second - begin.second));
}
