#pragma once

#include "MetricI.h"

class EuclideanMetric :	public MetricI {
public:
	virtual ~EuclideanMetric();

	virtual double calculateDistance(const Point&, const Point&) const;
};

