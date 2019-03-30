#include "tests.h"


void print_table(int *tab, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << tab[i] << " ";
}


int *create_table(int n)
{
	return new int[n];
}


void kill_table(int *table)
{
	delete[] table;
}


void fill_random(int *tab, int n)
{
	for (int i = 0; i < n; i++)
		tab[i] = rand() % 100000 + 1;
}


void sort_percent(int *tab, int n, double percent)
{
    if (percent == 100)
    {
        std::sort(tab, tab + n, std::greater<int>());
        return;
    }

	std::sort(tab, tab + (int)((n*percent) / 100));
}


bool check_if_sorted(int *tab, int n)
{
    for (int i = 0; i < n - 1 ; i++)
    {
        if(tab[i] > tab[i + 1])
        {
            std::cout << "Table not sorted!";
            std::cin.get();
            return false;
        }
    }
    return true;
}


void test()
{
    std::ofstream file("Results.txt");

     if (!file.is_open())
     {
        std::cout << "File is not open!";
        std::cin.get();
        return;
     }

	int loops = 100;
	int ntab[5] = {10000, 50000, 100000, 500000, 1000000};
	double percenttab[8] = {0, 25, 50, 75, 95, 99, 99.7, 100};

	double intro = 0, mergy = 0, quick = 0;

	std::cout << "QUICK SORT" << std::endl;
	for (double percent : percenttab)
	{
        for (int n : ntab)
        {
            int *tab = create_table(n);

            for (int i = 0; i < loops; i++)
            {
                fill_random(tab, n);
                sort_percent(tab, n, percent);

                auto t_start = std::chrono::high_resolution_clock::now();
                quicksort(tab, 0, n-1);
                auto t_end = std::chrono::high_resolution_clock::now();
                if(!check_if_sorted(tab, n))
                    return;
                quick += std::chrono::duration<double, std::milli>(t_end - t_start).count();
                std::cout << i << "%" << "\r";
            }
            kill_table(tab);
            std::cout << n << " table sorted!" << std::endl;
            file << quick / loops << " ";
            quick = 0;
        }
        std::cout << percent << " % done!" << std::endl;
	}


    file << "\n";
	std::cout << "MERGE SORT" << std::endl;
	for (double percent : percenttab)
	{
        for (int n : ntab)
        {
            int *tab = create_table(n);
            int *tmp = create_table(n);

            for (int i = 0; i < loops; i++)
            {
                fill_random(tab, n);
                sort_percent(tab, n, percent);

                auto t_start = std::chrono::high_resolution_clock::now();
                mergesort(tab, tmp, 0, n - 1);
                auto t_end = std::chrono::high_resolution_clock::now();
                if(!check_if_sorted(tab, n))
                    return;
                mergy += std::chrono::duration<double, std::milli>(t_end - t_start).count();
                std::cout << i << "%" << "\r";
            }
            kill_table(tab);
            kill_table(tmp);
            std::cout << n << " table sorted!" << std::endl;
            file << mergy / loops << " ";
            mergy = 0;
        }
        std::cout << percent << " % done!" << std::endl;
	}

    file << "\n";
	std::cout << "INTRO SORT" << std::endl;
	for (double percent : percenttab)
	{
        for (int n : ntab)
        {
            int *tab = create_table(n);

            for (int i = 0; i < loops; i++)
            {
                fill_random(tab, n);
                sort_percent(tab, n, percent);

                auto t_start = std::chrono::high_resolution_clock::now();
                introsort(tab, n);
                auto t_end = std::chrono::high_resolution_clock::now();
                if(!check_if_sorted(tab, n))
                    return;
                intro += std::chrono::duration<double, std::milli>(t_end - t_start).count();
                std::cout << i << "%" << "\r";
            }
            kill_table(tab);
            std::cout << n << " table sorted!" << std::endl;
            file << intro / loops << " ";
            intro = 0;
        }
        std::cout << percent << " % done!" << std::endl;
	}

	std::cin.get();
	file.close();
}
