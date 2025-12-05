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

    void cache_J_vector(size_t n);
    void cache_J_deque(size_t n);
    void insert_in_jacobsthal_order(std::vector<int> &vec, const std::vector<int> &insert_values);
    void insert_in_jacobsthal_order(std::deque<int> &deq, const std::deque<int> &insert_values);
    void sort(std::vector<int> &vec);
    void sort(std::deque<int> &deq);

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
    void verifySorted() const;
};
