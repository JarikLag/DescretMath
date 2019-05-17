#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>
#include "MetricI.h"

using Point = std::pair<double, double>;
using Path = std::vector<Point>;
using Route = std::vector<Path>;

class AlgorithmI {
public:
	virtual ~AlgorithmI();

	virtual Route calculateRoute(const std::vector<Point>&, int, const MetricI*) const = 0;
};