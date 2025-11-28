#include "PmergeMe.hpp"

static int parse_int(const std::string &token) {
    try {
        size_t pos;
        int value = std::stoi(token, &pos);
        if (pos != token.size()) {
            throw std::runtime_error("Error: Invalid integer: " + token);
        }
        if (value < 0) {
            throw std::runtime_error("Error: Negative integer: " + token);
        }
        return value;
    } catch (const std::exception &e) {
        throw std::runtime_error("Error: Invalid integer: " + token);
    }
}


PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
    _data_vector = other._data_vector;
    _sorted_vector = other._sorted_vector;
    _data_list = other._data_list;
    _sorted_list = other._sorted_list;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _data_vector = other._data_vector;
        _sorted_vector = other._sorted_vector;
        _data_list = other._data_list;
        _sorted_list = other._sorted_list;
    }
    return *this;
}


PmergeMe::~PmergeMe() {}

// Functions
void PmergeMe::displayData() const {
    auto it = _data_list.begin();
    for (size_t i = 0; i < _data_vector.size(); ++i) {
        std::cout << _data_vector[i] << " ";
        if (it == _data_list.end() || _data_vector[i] != *it)
            throw std::runtime_error("Error: Data mismatch between vector and list.");
        ++it;
    }
    std::cout << std::endl;

    auto it = _sorted_list.begin();
    for (size_t i = 0; i < _sorted_vector.size(); ++i) {
        std::cout << _sorted_vector[i] << " ";
        if (it == _sorted_list.end() || _sorted_vector[i] != *it)
            throw std::runtime_error("Error: Sorted data mismatch between vector and list.");
        ++it;
    }
    std::cout << std::endl;
}

void PmergeMe::displaySorted() const {
    for (std::vector<int>::const_iterator it = _sorted_vector.begin(); it != _sorted_vector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::sortVector(int argc, char** argv) {
    std::vector<std::pair<int, int> > pairs;
}

void PmergeMe::sortList(int argc, char** argv) {
    std::list<std::pair<int, int> > pairs;
}
