#include "histogram.h"

#include <cassert>

void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_positive_wrong() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 4);
}

void test_below_zero() {
    double min = 0;
    double max = 0;
    find_minmax({ -1, -2, -3 }, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_empty_array() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 1);
    assert(max == 4);
}

void test_multi_numbers() {
    double min = 0;
    double max = 0;
    find_minmax({ -101, 23, 0 }, min, max);
    assert(min == -101);
    assert(max == 23);
}

void test_same_naumbers() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 1, 1 }, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_one_number() {
    double min = 0;
    double max = 0;
    find_minmax({ 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}


int
main() {
    test_positive();
    test_positive_wrong();
    test_below_zero();
    test_empty_array();
    test_multi_numbers();
    test_same_naumbers();
    test_one_number;
}