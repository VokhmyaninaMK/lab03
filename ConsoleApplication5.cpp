#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include<string.h>
#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <stdio.h>
#include "histogram.h"
#include "svg.h"
using namespace std;


vector<double> input_numbers(size_t count) {
	vector<double> result(count);
	for (size_t i = 0; i < count; i++) {
		cin >> result[i];
	}
	return result;
}



vector<size_t> make_histogram(const vector<double>& numbers, size_t& bin_count)
{
	double min, max;
	find_minmax(numbers, min, max);
	vector<size_t> bins(bin_count);
	size_t number_count = numbers.size();
	double bin_size = (max - min) / bin_count;
	for (size_t i = 0; i < number_count; i++) {
		bool found = false;
		for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
			auto lo = min + j * bin_size;
			auto hi = min + (j + 1) * bin_size;
			if ((lo <= numbers[i]) && (numbers[i] < hi)) {
				bins[j]++;
				found = true;
			}
		}
		if (!found) {
			bins[bin_count - 1]++;
		}
	}
	return bins;
}
void show_histogram_text(vector<size_t> bins)
{
	size_t bin_count = bins.size();
	size_t max_count = bins[0];
	for (size_t x : bins) {
		if (x > max_count)
			max_count = x;
	}
	for (size_t i = 0; i < bin_count; i++) {
		if (bins[i] < 100)
			cout << ' ';
		if (bins[i] < 10)
			cout << ' ';
		cout << bins[i] << '|';
		size_t height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
		if (max_count <= MAX_ASTERISK)
			height = bins[i];
		for (size_t j = 0; j < height; j++)
			cout << '*';
		cout << '\n';
	}
}
void show_division_scale(vector<size_t> bins, size_t& interval)
{
	size_t max_count = bins[0];
	for (size_t x : bins) {
		if (x > max_count)
			max_count = x;
	}
	if (max_count > MAX_ASTERISK)
		max_count = MAX_ASTERISK;
	const size_t count_int = ceil(static_cast<double>(max_count) / interval);
	cout << "   |";
	for (size_t i = 0; i < count_int; i++) {
		for (size_t j = 0; j < interval - 1; j++)
			cout << '-';
		cout << '|';
	}
	cout << "\n   " << 0;
	for (size_t i = 0; i < count_int; i++) {
		for (size_t j = 0; j < interval - 1; j++)
			cout << ' ';
		if (i == 0 || i == count_int - 1)
			cout << (i + 1) * interval;
		else
			cout << ' ';
	}
}




int main()
{
	size_t number_count;
	cin >> number_count;
	const auto numbers = input_numbers(number_count);
	size_t bin_count;
	cin >> bin_count;
	size_t interval;
	cin >> interval;
	input_interval(interval);

	const auto bins = make_histogram(numbers, bin_count);
	show_histogram_svg(bins, interval);
}