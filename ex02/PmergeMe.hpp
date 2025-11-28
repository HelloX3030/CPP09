#pragma once

#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>

class PmergeMe {
private:
    std::vector<int> _data_vector;
    std::vector<int> _sorted_vector;
    std::list<int> _data_list;
    std::list<int> _sorted_list;

public:
    // Canonical Form
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    // Functions
    void sortVector(int argc, char** argv);
    void sortList(int argc, char** argv);
    void displayData() const;
    void displaySorted() const;
};
