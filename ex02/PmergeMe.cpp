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

PmergeMe::PmergeMe()
    : argc(0), argv(nullptr)
{

}

PmergeMe::PmergeMe(const PmergeMe& other) {
    argc = other.argc;
    argv = other.argv;
    _vector = other._vector;
    _list = other._list;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        argc = other.argc;
        argv = other.argv;
        _vector = other._vector;
        _list = other._list;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

// Special Constructor
PmergeMe::PmergeMe(int argc, char **argv)
    : argc(argc), argv(argv)
{

}

// Functions
void PmergeMe::displayData() const {
    for (int i = 1; i < argc; ++i) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::displaySorted() const {
    for (size_t i = 0; i < _vector.size(); ++i) {
        std::cout << _vector[i] << " ";
    }
    std::cout << std::endl;
}

static void sort_vector(std::vector<int> &vec) {
    if ( vec.size() <= 1 ) return;

    // Get Leftover element if the size is odd
    std::optional<int> leftover;
    if (vec.size() % 2 != 0) {
        leftover = vec.back();
    }

    // Create pairs
    size_t pair_count = vec.size() / 2;
    std::vector<int> bigger;
    std::vector<int> smaller;
    bigger.reserve(pair_count);
    smaller.reserve(pair_count);
    for (size_t i = 0; i < pair_count; ++i) {
        int first = vec[2 * i];
        int second = vec[2 * i + 1];
        if (first > second) {
            bigger.push_back(first);
            smaller.push_back(second);
        } else {
            bigger.push_back(second);
            smaller.push_back(first);
        }
    }

    // Recursively sort the bigger elements
    sort_vector(bigger);

    // Insert smaller elements into the sorted bigger elements
    std::vector<int> sorted;
    sorted.reserve(vec.size());
    
}

void PmergeMe::sortVector() {
    for (int i = 1; i < argc; ++i) {
        int value = parse_int(std::string(argv[i]));
        _vector.push_back(value);
    }

    sort_vector(_vector);
}

void PmergeMe::sortList() {
    std::list<std::pair<int, int> > pairs;
}
