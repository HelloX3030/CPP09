#include "PmergeMe.hpp"

static int parse_int(const std::string &token) {
    try {
        size_t pos;
        int value = std::stoi(token, &pos);
        if (pos != token.size()) {
            throw std::runtime_error("Error: Invalid integer: " + token);
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
    data = other.data;
}

template <typename T>
PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

template <typename T>
PmergeMe<T>::~PmergeMe() {}

// Special Constructor
template <typename T>
PmergeMe<T>::PmergeMe(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        data.push_back(parse_int(argv[i]));
    }
    sorted = data;
}

// Functions
template <typename T>
void PmergeMe<T>::displayData() const {
    for (typename T::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PmergeMe<T>::displaySorted() const {
    for (typename T::const_iterator it = sorted.begin(); it != sorted.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PmergeMe<T>::sortData() {
}
