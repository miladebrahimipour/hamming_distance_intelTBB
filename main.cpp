#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <random>
#include <bitset>
#include <algorithm>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>

#define SIZE_OF_ARRAY  100000
#define NUM_BITS  31
#define MAX_RAND_VAL     (1<<NUM_BITS)

int minHammingDistanceSerial(const std::vector<unsigned int>&);
int minHammingDstanceParallel(const std::vector<unsigned int>&);
int main()
{
    // Generate an Array of Random Numbers
    std::vector<unsigned int> random_numbers (SIZE_OF_ARRAY);
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<unsigned int> distribution (0, MAX_RAND_VAL);


    /*std::vector<unsigned int> random_numbers;
    random_numbers.push_back(0);
    random_numbers.push_back(1);
    random_numbers.push_back(2);*/

    tbb::parallel_for(tbb::blocked_range<unsigned int>(0, random_numbers.size()), [&](tbb::blocked_range<unsigned int> r)
    {
        for (int i=r.begin(); i<r.end(); ++i)
        {
            random_numbers[i] = distribution(generator);
        }
    });

    std::cout << "Serial Execution..." << std::endl;
    auto start = std::chrono::steady_clock::now();
    int min_ham = minHammingDistanceSerial(random_numbers);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Hamming Distance = " << min_ham << std::endl;
    std::cout << "Serial Execution took: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "seconds to run" << std::endl;

    std::cout << std::endl << "------------------------------------------------------------------------------------" << std::endl;

    std::cout << "Parallel Execution..." << std::endl;
    auto start1 = std::chrono::steady_clock::now();
    min_ham = minHammingDstanceParallel(random_numbers);
    auto end1 = std::chrono::steady_clock::now();
    std::cout << "Hamming Distance = " << min_ham << std::endl;
    std::cout << "Parallel Execution took: " << std::chrono::duration_cast<std::chrono::seconds>(end1 - start1).count() << "seconds to run" << std::endl;
}


int minHammingDistanceSerial(const std::vector<unsigned int>& tab)
{
    int min_hamming = NUM_BITS;
    for(int i = 0; i < tab.size(); i++)
    {
        for(int j = i+1; j < tab.size(); j++)
        {
            std::bitset<NUM_BITS> res {tab[i] ^ tab[j]};
            min_hamming = (min_hamming > res.count()) ? res.count() : min_hamming;
        }
    }
    return min_hamming;
}


int minHammingDstanceParallel(const std::vector<unsigned int>& tab)
{
    int min_hamming = NUM_BITS;
    //std::vector<std::vector<int>> min_hamming(SIZE_OF_ARRAY , std::vector<int> (SIZE_OF_ARRAY, NUM_BITS)); 

    // Initialize task scheduler
    tbb::task_scheduler_init tbb_init;
    /*tbb::parallel_for (tbb::blocked_range2d<unsigned int>(0, N, 32, 0, N, 32),  [&](tbb::blocked_range2d<unsigned int> r)
    {

    });*/
    tbb::parallel_for(0, SIZE_OF_ARRAY, [&](int i)
    {
        tbb::parallel_for(i+1, SIZE_OF_ARRAY, [&](int j)
        {

            std::bitset<NUM_BITS> res {tab[i] ^ tab[j]};
            min_hamming = (min_hamming > res.count()) ? res.count() : min_hamming;


            /*std::bitset<NUM_BITS> res {tab[i] ^ tab[j]};
            min_hamming[i][j] = (min_hamming[i][j] > res.count()) ? res.count() : min_hamming[i][j];*/
        });
    });
    return min_hamming;
}
