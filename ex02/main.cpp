#include "PmergeMe.hpp"

int main(int argc, char** argv) {

    try
    {
        PmergeMeVector pmVector(argc, argv);
        pmVector.displayData();
        pmVector.sortData();
        pmVector.displaySorted();
        PmergeMeList pmList(argc, argv);
        pmList.displayData();
        pmList.sortData();
        pmList.displaySorted();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
