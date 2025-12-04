#pragma once

#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>
#include <optional>

class PmergeMe {
private:
    int argc;
    char** argv;
    std::vector<int> _vector;
    std::list<int> _list;

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
    void sortList();
    void displayData() const;
    void displaySorted() const;
};
