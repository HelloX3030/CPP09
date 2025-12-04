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
    for (int i = 1; i < argc; ++i) {
        int value = parse_int(std::string(argv[i]));
        _vector.push_back(value);
        _list.push_back(value);
    }
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

void PmergeMe::sortVector() {
    if ( _vector.size() <= 1 ) return;

    // Get Leftover element if the size is odd
    bool leftover = _vector.size() % 2;
    int last_element;
    if (leftover) {
        last_element = _vector.back();
        _vector.pop_back();
    }

    // Create pairs
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < _vector.size(); i += 2) {
        int a = std::min(_vector[i], _vector[i + 1]);
        int b = std::max(_vector[i], _vector[i + 1]);
        pairs.push_back(std::make_pair(a, b));
    }

    // Sort Pairs
}

void PmergeMe::sortList() {
    std::list<std::pair<int, int> > pairs;
}
