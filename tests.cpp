#include "sort_algorithms.h"
#include <chrono>
#include <fstream>
#include <iostream>

#define DataType int //choose your DataType right there
                    //if you want to use other types then int and double, please add  explicit instantiation at the end of
                    //sort_algorithm.cpp file

template<typename T>
using SortFncPoint = void (*)(T*, T*, int, int, int);


template<typename T>
void print_table(T *tab, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << tab[i] << " ";
}


template<typename T>
T *create_table(int n)
{
	return new T[n];
}


template<typename T>
void kill_table(T *table)
{
	delete[] table;
}


//fills the tab table with n random elements
//using 1 - 100 000 range of numbers
template<typename T>
void fill_random(T *tab, int n)
{
	for (int i = 0; i < n; i++)
		tab[i] = rand() % 100000 + 1;
}


//sorts a given percent of elements in tab table (starting from first element)
template<typename T>
void sort_percent(T *tab, int n, double percent)
{
    if (percent == 100) //then sorts whole table in reverse order
    {
        std::sort(tab, tab + n, std::greater<T>());
        return;
    }
	std::sort(tab, tab + (int)((n*percent) / 100));
}


template<typename T>
void check_if_sorted(T *tab, int n)
{
    for (int i = 0; i < n - 1 ; i++)
    {
        if(tab[i] > tab[i + 1])
        {
            std::cout << "Table not sorted!\nProgram closing...";
            std::cin.get();
            exit(1);
        }
    }
}


void check_if_open (std::ofstream &file)
{
    if (!file.is_open())
     {
        std::cout << "File is not open!\nProgram closing...";
        std::cin.get();
        exit(1);
     }
}


//conduct sorting of tab table using algorithm that is passed by pointer
//it also returns the duration of sorting in milliseconds
template<typename T>
double sort_it(SortFncPoint<DataType> fp, int n, T *tab, T *tmp)
{
    auto t_start = std::chrono::high_resolution_clock::now(); //start clock
    fp(tab, tmp, 0, n-1, log(n) * 2);
    auto t_end = std::chrono::high_resolution_clock::now(); //stop clock

    return std::chrono::duration<double, std::milli>(t_end - t_start).count(); //return the time difference
}


//sorts a specified number of tables using specified algorithms in different conditions
//it also saves each result (time of sorting) in external file
//the function is also interactive with user and prints to std::out actual status of sorting
int main()
{
    std::ofstream file("Results.txt");
    check_if_open(file);

    srand(time(NULL));

	int loops = 1; //number of tables that will be sorted for each configuration
	int ntab[5] = {10000, 50000, 100000, 500000, 1000000}; //first part of configuration -> sizes of data
	double percenttab[8] = {0, 25, 50, 75, 95, 99, 99.7, 100 /*all sorted reverse*/}; //second part -> percent of pre-sorted elements

	SortFncPoint<DataType> mpoint= &mergeWrap, qpoint = &quickWrap, ipoint = &introWrap; //pointers to sort functions
    SortFncPoint<DataType> ptable[3] = {qpoint, mpoint, ipoint};

	double counter = 0;
	int iter = 0;
	std::string sorts[3] = {"QUCIK_SORT", "MERGE_SORT", "INTRO_SORT"};

    for(SortFncPoint<DataType> fp : ptable) //for each sorting function
    {
        std::cout << sorts[iter++] << std::endl;
        for (double percent : percenttab) //for each pre-sorted percent
        {
            for (int n : ntab) // for each data size
            {
                DataType *tab = create_table<DataType>(n);
                DataType *tmp = create_table<DataType>(n);

                for (int i = 0; i < loops; i++) //sort specified number of tables
                {
                    fill_random<DataType>(tab, n);
                    sort_percent<DataType>(tab, n, percent);
                    counter += sort_it<DataType>(fp, n, tab, tmp);
                    check_if_sorted<DataType>(tab, n);

                    std::cout << i << "%" << "\r";
                }
                kill_table<DataType>(tab);
                kill_table<DataType>(tmp);

                std::cout << n << " table sorted!" << std::endl;

                file << counter / loops << " "; //saves the average time spent on sorting a single table
                counter = 0;
            }
            std::cout << percent << " % done!" << std::endl;
        }
        file << "\n";
    }
    std::cout << "END OF SORTING!";
	std::cin.get();
	file.close();

	return 0;
}

