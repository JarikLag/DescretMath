#pragma once

#include <algorithm>

using Point = std::pair<double, double>;

class MetricI {
public:
	virtual ~MetricI();

	virtual double calculateDistance(const Point&, const Point&) const = 0;
};