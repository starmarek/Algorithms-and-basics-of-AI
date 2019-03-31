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


void check_if_sorted(int *tab, int n)
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


double sort_it(SortFncPoint fp, int n, int *tab, int *tmp)
{
    auto t_start = std::chrono::high_resolution_clock::now();
    fp(tab, tmp, 0, n-1, log(n) * 2);
    auto t_end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(t_end - t_start).count();
}


void test()
{
    std::ofstream file("Results.txt");
    check_if_open(file);

	int loops = 1;
	int ntab[5] = {10000, 50000, 100000, 500000, 1000000};
	double percenttab[8] = {0, 25, 50, 75, 95, 99, 99.7, 100};

	SortFncPoint mpoint= &mergeWrap, qpoint = &quickWrap, ipoint = &introWrap;
    SortFncPoint ptable[3] = {qpoint, mpoint, ipoint};

	double counter = 0;
	int iter = 0;
	std::string sorts[3] = {"QUCIK_SORT", "MERGE_SORT", "INTRO_SORT"};

    for(SortFncPoint fp : ptable)
    {
        std::cout << sorts[iter++] << std::endl;
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
                    counter += sort_it(fp, n, tab, tmp);
                    check_if_sorted(tab, n);

                    std::cout << i << "%" << "\r";
                }
                kill_table(tab);
                kill_table(tmp);

                std::cout << n << " table sorted!" << std::endl;

                file << counter / loops << " ";
                counter = 0;
            }
            std::cout << percent << " % done!" << std::endl;
        }
        file << "\n";
    }
    std::cout << "END OF SORTING!";
	std::cin.get();
	file.close();
}

