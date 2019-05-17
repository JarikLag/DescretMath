#include "RecursiveAlgorithm.h"

RecursiveAlgorithm::~RecursiveAlgorithm() {}

Route RecursiveAlgorithm::calculateRoute(const std::vector<Point>& points, int bound, const MetricI* metric) const {
	assert(metric != nullptr);

	Route result, current;
	std::vector<bool> used(points.size(), false);
	double length = INFINITY;
	
	std::function <void(int, double)> recursion = [&] (int sizeOfCurrentPath, double currentLength) {
		if (sizeOfCurrentPath == points.size()) {
			if (length >= currentLength) {
				result = current;
				length = currentLength;
			}
			return;
		}
		if (sizeOfCurrentPath % bound == 0) {
			current.push_back({});
		}		
		for (int i = 0; i < points.size(); ++i) {
			if (used[i]) {
				continue;
			}
			double newCurrentLength = currentLength;
			if (current.back().size() > 0) {
				newCurrentLength += metric->calculateDistance(current.back().back(), points[i]);
			}
			current.back().push_back(points[i]);
			used[i] = true;
			recursion(sizeOfCurrentPath + 1, newCurrentLength);
			current.back().pop_back();
			used[i] = false;
		}
		if (sizeOfCurrentPath % bound == 0) {
			current.pop_back();
		}
	};

	recursion(0, 0);
	return result;
}
