#pragma once

#include "AlgorithmI.h"

class IterativeAlgorithm :	public AlgorithmI {
public:
	virtual ~IterativeAlgorithm();

	virtual Route calculateRoute(const std::vector<Point>&, int, const MetricI*) const;
};

