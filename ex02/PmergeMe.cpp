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

template <typename T>
PmergeMe<T>::PmergeMe() {}

template <typename T>
PmergeMe<T>::PmergeMe(const PmergeMe& other) {
    _data = other._data;
    _sorted = other._sorted;
}

template <typename T>
PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe& other) {
    if (this != &other) {
        _data = other._data;
        _sorted = other._sorted;
    }
    return *this;
}

template <typename T>
PmergeMe<T>::~PmergeMe() {}

// Special Constructor
template <typename T>
PmergeMe<T>::PmergeMe(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        _data.push_back(parse_int(argv[i]));
    }
}

// Functions
template <typename T>
void PmergeMe<T>::displayData() const {
    for (typename T::const_iterator it = _data.begin(); it != _data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PmergeMe<T>::displaySorted() const {
    for (typename T::const_iterator it = _sorted.begin(); it != _sorted.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PmergeMe<T>::sortData() {
}

template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::list<int> >;
