#include "sort_algorithms.h"


/**************
*             *
* MERGE SORT  *
*             *
**************/
void merge_em(int *tab, int *tmp, int left, int midd, int right)
{
	for (int i = left; i <= right; i++)
        tmp[i] = tab[i];

	int i = left;
	int j = midd + 1;
	int q = left;

	while (i <= midd && j <= right)
	{
		if (tmp[i] < tmp[j])
			tab[q++] = tmp[i++];

		else
			tab[q++] = tmp[j++];
	}

	while (i <= midd)
		tab[q++] = tmp[i++];
}


void mergesort(int *tab, int *tmp, int left, int right)
{
	if (left < right)
	{
		int midd = (left + right) / 2;
		mergesort(tab, tmp, left, midd);
		mergesort(tab, tmp, midd + 1, right);
		merge_em(tab, tmp, left, midd, right);
	}
}


/**************
*             *
* QUICK SORT  *
*             *
**************/
void quicksort(int *tab, int left, int right)
{
	int i = left;
	int j = right;
	int bound = tab[(left + right) / 2];

	do
	{
		while (tab[i] < bound) i++;

		while (tab[j] > bound) j--;

		if (i <= j)
            std::swap(tab[i++], tab[j--]);

	} while (i <= j);

	if (j > left)
        quicksort(tab, left, j);

	if (i < right)
        quicksort(tab, i, right);
}

/**************
*             *
* INTRO SORT  *
*             *
**************/
void insertionsort(int *tab, int n)
{
	int j, key;
	for (int i = 1; i < n; i++)
	{
		key = tab[i];
		for (j = i; j > 0 && key < tab[j - 1]; j--)
			tab[j] = tab[j - 1];
		tab[j] = key;
	}
}


void heapify(int *tab, int left, int n)
{
	while (left <= n / 2)
	{
		int child = 2 * left;

		if ((child + 1 <= n) && (tab[child + 1] > tab[child]))
			child++;

		if (tab[left] < tab[child])
			std::swap(tab[left], tab[child]);

		else
            break;
		left = child;
	}
}


void heapsort(int *tab, int n)
{
	for (int i = n / 2; i > 0; i--)
		heapify(tab - 1, i, n);

	for (int i = n - 1; i > 0; i--)
	{
		std::swap(tab[0], tab[i]);
		heapify(tab - 1, 1, i);
	}
}

void median_of_three(int *tab, int &left, int &right)
{
	if (tab[left++ - 1] > tab[right--])
		std::swap(tab[left - 1], tab[right]);

	if (tab[left - 1] > tab[right / 2])
		std::swap(tab[left - 1], tab[right / 2]);

	if (tab[left / 2] > tab[right])
		std::swap(tab[right / 2], tab[right]);

	std::swap(tab[right / 2], tab[right - 1]);
}


int part_em(int *tab, int left, int right)
{
	int i, j;

	if (right >= 3)
		median_of_three(tab, left, right);

	for (i = left, j = right - 2; ; )
	{
		while (tab[i] < tab[right - 1])
			i++;

		while (j >= left && tab[j] > tab[right - 1])
			j--;

		if (i < j)
			std::swap(tab[i++], tab[j--]);

		else
			break;
	}

	std::swap(tab[i], tab[right - 1]);
	return i;
}


void intro_rec(int *tab, int n, int depth)
{
	if (depth <= 0)
	{
		heapsort(tab, n);
		return;
	}

	int i = part_em(tab, 0, n);

	if (i > 16)
        intro_rec(tab, i, depth - 1);

	if (n - 1 - i > 9)
		intro_rec(tab + i + 1, n - 1 - i, depth - 1);
}


void introsort(int *tab, int n)
{
	intro_rec(tab, n, (int)floor(2 * log(n) / M_LN2));
	insertionsort(tab, n);
}

