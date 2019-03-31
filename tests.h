#ifndef TESTS_H
#define TESTS_H

#include "sort_algorithms.h"
#include <chrono>
#include <fstream>
#include <iostream>

typedef void(*SortFncPoint)(int*, int*, int, int, int);

void print_table(int *tab, int n);

int *create_table(int n);

void kill_table(int *table);

void fill_random(int *tab, int n);

void sort_percent(int *tab, int n, double percent);

void check_if_sorted(int *tab, int n);

void check_if_open (std::ofstream &file);

double sort_it(SortFncPoint fp, int n, int *tab, int *tmp);

void test();

#endif
