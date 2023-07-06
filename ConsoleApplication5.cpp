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

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
const auto IMAGE_WIDTH = 600;
const auto IMAGE_HEIGHT = 500;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 5;


vector<double> input_numbers(size_t count) {
	vector<double> result(count);
	for (size_t i = 0; i < count; i++) {
		cin >> result[i];
	}
	return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max) {
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

void
svg_begin(double width, double height) {
	cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
	cout << "<svg ";
	cout << "width='" << width << "' ";
	cout << "height='" << height << "' ";
	cout << "viewBox='0 0 " << width << " " << height << "' ";
	cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
	cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text) {
	cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
	cout <<"<rect x='" << x << "' y='" << y <<
	"' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='"<< fill << "'/>\n";
}

void show_division_scale_svg(vector<size_t> bins, size_t interval, size_t top)
{
	size_t max_count = bins[0];
	for (size_t x : bins) {
		if (x > max_count)
			max_count = x;
	}

	if (max_count > MAX_ASTERISK)
		max_count = MAX_ASTERISK;
	const size_t count_int = ceil(static_cast<double>(max_count) / interval);
	string s = "   ";
	s += '|';
	for (size_t i = 0; i < count_int; i++) {
		for (size_t j = 0; j < interval - 1; j++)
			s = s + "-";
		s = s + "|";
	}
	svg_text(TEXT_WIDTH, top + TEXT_BASELINE, s);
	top += BIN_HEIGHT;

	svg_text(TEXT_WIDTH, top + TEXT_BASELINE, "0");
	double lef = TEXT_WIDTH;
	for (size_t i = 0; i < count_int; i++) {
		for (size_t j = 0; j < interval - 1; j++)
			lef += 5;
		if (i == 0 || i == count_int - 1)
			svg_text(lef, top + TEXT_BASELINE, to_string((i + 1) * interval));
		else
			lef += 5;
	}
	svg_text(TEXT_WIDTH, top + TEXT_BASELINE, "0");
}

void
show_histogram_svg(const vector<size_t>& bins, size_t interval) {
	svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
	size_t max_count = bins[0];
	for (size_t x : bins) {
		if (x > max_count)
			max_count = x;
	}
	double top = 0;
	for (size_t bin : bins) {
		string s;

		size_t height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
		if (max_count <= MAX_ASTERISK)
			height = bin;

		const double bin_width = BLOCK_WIDTH * height;

		s += to_string(height);
		svg_text(TEXT_LEFT, top + TEXT_BASELINE, s);
		svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
		top += BIN_HEIGHT;
	}
	show_division_scale_svg(bins, interval, BIN_HEIGHT*bins.size());
	svg_end();
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
	if (interval < 2 || interval > 9) {
		cout << "ERROR";
		return 0;
	}

	const auto bins = make_histogram(numbers, bin_count);
	show_histogram_svg(bins, interval);
}