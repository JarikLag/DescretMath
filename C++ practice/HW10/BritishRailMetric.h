#pragma once

#include "MetricI.h"

class BritishRailMetric : public MetricI {
public:
	virtual ~BritishRailMetric();

	virtual double calculateDistance(const Point&, const Point&) const;
};

