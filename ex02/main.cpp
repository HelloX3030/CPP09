#include "PmergeMe.hpp"
#include <chrono>
#include <iomanip>

int main(int argc, char** argv)
{
    try
    {
        // Vector version
        auto vector_start = std::chrono::high_resolution_clock::now();
        PmergeMeVector pmVector(argc, argv);
        pmVector.sortData();
        auto vector_end = std::chrono::high_resolution_clock::now();

        // List version
        auto list_start =  std::chrono::high_resolution_clock::now();
        PmergeMeList pmList(argc, argv);
        pmList.sortData();
        auto list_end = std::chrono::high_resolution_clock::now();

        // Display results
        std::cout << "Before: ";
        pmVector.displayData();
        std::cout << "After: ";
        pmVector.displaySorted();
        
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
