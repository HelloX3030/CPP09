#include "PmergeMe.hpp"
#include <chrono>
#include <iomanip>

int main(int argc, char** argv)
{
    try
    {
        PmergeMe pm(argc, argv);

        // Vector version
        auto vector_start = std::chrono::high_resolution_clock::now();
        pm.sortVector();
        auto vector_end = std::chrono::high_resolution_clock::now();

        // List version
        auto list_start =  std::chrono::high_resolution_clock::now();
        pm.sortList();
        auto list_end = std::chrono::high_resolution_clock::now();

        // Display results
        std::cout << "Before: ";
        pm.displayData();
        std::cout << "After: ";
        pm.displaySorted();

        // Timing results
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : "
                  << std::chrono::duration_cast<std::chrono::microseconds>(vector_end - vector_start).count()
                  << " us" << std::endl;
        std::cout << "Time to process a range of " << argc - 1 << " elements with std::list : "
                  << std::chrono::duration_cast<std::chrono::microseconds>(list_end - list_start).count()
                  << " us" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
