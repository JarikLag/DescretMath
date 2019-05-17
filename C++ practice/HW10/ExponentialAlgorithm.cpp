#include "ExponentialAlgorithm.h"

ExponentialAlgorithm::~ExponentialAlgorithm() {}

Route ExponentialAlgorithm::calculateRoute(const std::vector<Point>& points, int bound, const MetricI* metric) const {
	assert(metric != nullptr);

	std::vector<int> currentPermutation;
	int numberOfSets = 1, sizeOfCurrentPath = 0;
	for (int i = 0; i < points.size(); ++i) {
		if (sizeOfCurrentPath == bound) {
			sizeOfCurrentPath = 0;
			++numberOfSets;
		}
		currentPermutation.push_back(numberOfSets);
		++sizeOfCurrentPath;
	}

	Route result, current(numberOfSets);
	double length = INFINITY, currentLength = 0;
	int index = 0;
	do {
		std::vector<bool> update(numberOfSets, false);
		std::vector<std::vector<int>> setsOfIndexes(numberOfSets);
		for (int i = 0; i < currentPermutation.size(); ++i) {
			if (i >= index) {
				update[currentPermutation[i] - 1] = true;
			}
			setsOfIndexes[currentPermutation[i] - 1].push_back(i);
		}
		for (int i = 0; i < update.size(); ++i) {
			if (update[i]) {
				current[i] = findHamiltonPath(setsOfIndexes[i], points, metric);
			}
		}
		for (int i = 0; i < current.size(); ++i) {
			for (int j = 0; j < current[i].size() - 1; ++j) {
				currentLength += metric->calculateDistance(current[i][j], current[i][j + 1]);
			}
		}
		if (length > currentLength) {
			length = currentLength;
			result = current;
		}
		index = nextMultiPermutation(currentPermutation);
		currentLength = 0;
	} while (currentPermutation[0] != 0);

	return result;
}

std::vector<Point> ExponentialAlgorithm::findHamiltonPath(const std::vector<int>& indexes, const std::vector<Point>& points, const MetricI* metric) const {
	int size = indexes.size();
	std::vector<std::vector<double>> dp(1 << (size + 1), std::vector<double>(size + 1, INFINITY));
	std::vector<std::vector<bool>> used(1 << (size + 1), std::vector<bool>(size + 1, false));
	std::vector<std::vector<double>> graph(size + 1, std::vector<double>(size + 1, 0));
	std::vector<Point> result;
	std::function <double(int, int, int)> calc = [&](int mask, int v, int last) {
		if (dp[mask][v] != INFINITY)
			return dp[mask][v];
		for (int u = 0; u <= size; ++u) {
			if (u != v && u != last) {
				if (mask & (1 << u)) {
					if (used[mask & ~(1 << u)][u]) {
						dp[mask][v] = std::min(dp[mask][v], dp[mask & ~(1 << u)][u] + graph[v][u]);
					}
					else {
						dp[mask][v] = std::min(dp[mask][v], calc(mask & ~(1 << u), u, v) + graph[v][u]);
					}
				}
			}
		}
		used[mask][v] = true;
		return dp[mask][v];
	};

	if (indexes.size() == 1) {
		result.push_back(points[indexes[0]]);
		return result;
	}

	for (int i = 0; i <= size; ++i) {
		for (int j = 0; j <= size; ++j) {
			if (i != 0 && j != 0) {
				graph[i][j] = graph[j][i] = metric->calculateDistance(points[indexes[i - 1]], points[indexes[j - 1]]);
			}
		}
	}
	dp[0][0] = 0;
	used[0][0] = true;
	calc((1 << (size + 1)) - 1, 0, 0);
	int ind = 0, mask = (1 << (size + 1)) - 1;
	std::vector<int> path;
	path.push_back(ind);
	while (mask != 0) {
		for (int i = 0; i <= size; i++) {
			if ((mask & (1 << i)) && (dp[mask][ind] == dp[mask & ~(1 << i)][i] + graph[ind][i])) {
				path.push_back(i);
				ind = i;
				mask -= (1 << i);
				continue;
			}
		}
	}
	for (int i = 0; i < path.size() - 1; i++) {
		if (path[i] != 0)
			result.push_back(points[indexes[path[i] - 1]]);
	}
	return result;
}

int ExponentialAlgorithm::nextMultiPermutation(std::vector<int>& permutation) const {
	int ind = -1, n = permutation.size();
	std::vector<int> result;
	for (int i = n - 2; i >= 0; i--) {
		if (permutation[i] < permutation[i + 1]) {
			ind = i;
			break;
		}
	}
	if (ind == -1) {
		for (int i = 0; i < n; i++) {
			result.push_back(0);
		}
		std::swap(result, permutation);
		return -1;
	}
	else {
		int min = 1e9, minInd = -1;
		for (int i = ind + 1; i < n; i++) {
			if (permutation[i] > permutation[ind] && min > permutation[i]) {
				minInd = i;
				min = permutation[i];
			}
		}
		std::swap(permutation[ind], permutation[minInd]);
		std::vector<int> tmp;
		for (int i = n - 1; i > ind; i--) {
			tmp.push_back(permutation[i]);
		}
		sort(tmp.begin(), tmp.end());
		for (int i = 0; i <= ind; i++) {
			result.push_back(permutation[i]);
		}
		for (int i = 0; i < tmp.size(); i++) {
			result.push_back(tmp[i]);
		}
		std::swap(result, permutation);
		return ind;
	}
}
