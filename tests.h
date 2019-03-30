#ifndef TESTS_H
#define TESTS_H

#include "sort_algorithms.h"
#include <chrono>
#include <algorithm>
#include <fstream>

void print_table(int *tab, int n);

int *create_table(int n);

void kill_table(int *table);

void fill_random(int *tab, int n, double percent);

void sort_percent(int *tab, int n, double percent);

void test();

#endif
