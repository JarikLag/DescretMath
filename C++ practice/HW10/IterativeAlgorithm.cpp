#include "IterativeAlgorithm.h"

IterativeAlgorithm::~IterativeAlgorithm() {}

Route IterativeAlgorithm::calculateRoute(const std::vector<Point>& points, int bound, const MetricI* metric) const {
	assert(metric != nullptr);

	std::vector<int> currentPermutation(points.size()), answerPermutation(points.size());
	Route result;
	double length = INFINITY;
	int sizeOfCurrentPath = 1;
	for (int i = 0; i < points.size(); ++i) {
		currentPermutation[i] = i;
	}

	do {
		double currentLength = 0;
		for (int i = 0; i < currentPermutation.size() - 1; ++i) {
			if (sizeOfCurrentPath == bound) {
				sizeOfCurrentPath = 1;
				continue;
			}
			++sizeOfCurrentPath;
			currentLength += metric->calculateDistance(points[currentPermutation[i]], points[currentPermutation[i + 1]]);
		}
		if (length > currentLength) {
			length = currentLength;
			answerPermutation = currentPermutation;
		}
		sizeOfCurrentPath = 1;
	} while (std::next_permutation(currentPermutation.begin(), currentPermutation.end()));

	sizeOfCurrentPath = 0;
	Path path;
	for (int i = 0; i < answerPermutation.size(); ++i) {
		if (sizeOfCurrentPath == bound) {
			result.push_back(path);
			path.clear();
			sizeOfCurrentPath = 0;
		}
		++sizeOfCurrentPath;
		path.push_back(points[answerPermutation[i]]);
	}
	if (path.size() > 0) {
		result.push_back(path);
	}
	return result;
}