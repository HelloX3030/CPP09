#pragma once

#include <string>
#include <vector>
#include <deque>
#include <stdexcept>
#include <iostream>
#include <optional>
#include <cmath>

class PmergeMe {
private:
    int argc;
    char** argv;

    // vector
    std::vector<int> _J_vector;
    std::vector<int> _vector;

    // deque
    std::deque<int> _J_deque;
    std::deque<int> _deque;

    void cache_jacobsthal_numbers(size_t n);

public:
    // Canonical Form
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    // Special Constructor
    PmergeMe(int argc, char **argv);

    // Functions
    void sortVector();
    void sortDeque();
    void displayData() const;
    void displaySorted() const;
};
