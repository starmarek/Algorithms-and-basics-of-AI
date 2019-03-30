#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <iostream>
#include <cmath>
#define M_LN2 0.69314718055994530942


void merge_em(int *tab, int *tmp, int left, int midd, int right);

void mergesort(int *tab, int *tmp, int left, int right);

void quicksort(int *tab, int left, int right);

void insertionsort(int *tab, int n);

void heapify(int *tab, int left, int n);

void heapsort(int *tab, int n);

void median_of_three(int *tab, int &left, int &right);

int part_em(int *tab, int left, int right);

void intro_rec(int *tab, int n, int depth);

void introsort(int *tab, int n);

#endif

