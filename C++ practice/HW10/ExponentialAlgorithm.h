#pragma once

#include "AlgorithmI.h"

class ExponentialAlgorithm : public AlgorithmI {
public:
	virtual ~ExponentialAlgorithm();

	virtual Route calculateRoute(const std::vector<Point>&, int, const MetricI*) const;
private:
	std::vector<Point> findHamiltonPath(const std::vector<int>& indexesOfsubsetOfPoints, const std::vector<Point>& points, const MetricI* metric) const;
	int nextMultiPermutation(std::vector<int>& permutation) const;
};

