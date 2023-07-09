#include "histogram.h"

void find_minmax(const vector<double> numbers, double& min, double& max) {
	min = max = numbers[0];
	for (double x : numbers) {
		if (x < min) {
			min = x;
		}
		else if (x > max) {
			max = x;
		}
	}
}
