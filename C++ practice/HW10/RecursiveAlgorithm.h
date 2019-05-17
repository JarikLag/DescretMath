#pragma once

#include "AlgorithmI.h"

class RecursiveAlgorithm :	public AlgorithmI {
public:
	virtual ~RecursiveAlgorithm();

	virtual Route calculateRoute(const std::vector<Point>&, int, const MetricI*) const;
};

