#pragma once

#include "MetricI.h"

class ManhattanMetric :	public MetricI {
public:
	virtual ~ManhattanMetric();

	virtual double calculateDistance(const Point&, const Point&) const;
};

