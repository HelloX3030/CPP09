#pragma once

#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>

template <typename T>
class PmergeMe {
private:
    T data;
    T sorted;

public:
    // Canonical Form
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    // Special Constructor
    PmergeMe(int argc, char** argv);

    // Functions
    void displayData() const;
    void displaySorted() const;
    void sortData();
};

typedef PmergeMe<std::vector<int> > PmergeMeVector;
typedef PmergeMe<std::list<int> > PmergeMeList;
