#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <algorithm>


void merge(int *tab, int *tmp, int left, int midd, int right);

void mergesort(int *tab, int *tmp, int left, int right);

int partition(int *tab, int left, int right);

void quicksort(int *tab, int left, int right);

void insertionsort(int *tab, int left, int right);

void heapsort(int *left, int *right);

void introsort(int *tab, int *left, int *right, int maxdepth);

void introWrap(int *tab, int *tmp, int left, int right, int maxdepth);

void quickWrap(int *tab, int *tmp, int left, int right, int maxdepth);

void mergeWrap(int *tab, int *tmp, int left, int right, int maxdepth);

#endif

