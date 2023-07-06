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
void svg_begin(double width, double height) {
	cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
	cout << "<svg ";
	cout << "width='" << width << "' ";
	cout << "height='" << height << "' ";
	cout << "viewBox='0 0 " << width << " " << height << "' ";
	cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
	cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {
	cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
	cout << "<rect x='" << x << "' y='" << y <<
		"' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>\n";
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
	show_division_scale_svg(bins, interval, BIN_HEIGHT * bins.size());
	svg_end();
}