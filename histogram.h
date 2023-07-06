#pragma once
#include <vector>
#include <iostream>
#include <string>

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

void find_minmax(const vector<double> numbers, double& min, double& max);

void svg_begin(double width, double height);

void svg_end();

void svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
void show_division_scale_svg(vector<size_t> bins, size_t interval, size_t top);

void show_histogram_svg(const vector<size_t>& bins, size_t interval);