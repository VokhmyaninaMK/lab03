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


using namespace std;


int main()
{
	const size_t SCREEN_WIDTH = 80;
	const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

	size_t number_count, bin_count, interval;
	cerr << "Enter number count: ";
	cin >> number_count;

	vector<double> numbers(number_count);
	for (size_t i = 0; i < number_count; i++)
		cin >> numbers[i];
	cin >> bin_count;

	vector<size_t> bins(bin_count);
	cerr << "Enter the interval: ";
	cin >> interval;

	if (interval < 4 || interval > 9) {
		cout << "ERROR";
		return 0;
	}

	double min = numbers[0];
	double max = numbers[0];
	for (double x : numbers) {
		if (x < min) {
			min = x;
		}
		else if (x > max) {
			max = x;
		}
	}

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
		// цикл по numbers не закончился!

		if (!found) {
			bins[bin_count - 1]++;
		}
	} // конец цикла по numbers

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