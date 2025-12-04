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

static void insert(std::vector<int> &vec, int value) {
    int n = vec.size();
    vec.push_back(0); // make space
    int i = n - 1;
    while (i >= 0 && vec[i] > value) {
        vec[i + 1] = vec[i]; // shift right
        i--;
    }
    vec[i + 1] = value;
}

/*
Jacobsthal numbers form a sequence defined by the recurrence:

    J(0) = 0
    J(1) = 1
    J(n) = J(n − 1) + 2·J(n − 2)   for n ≥ 2

The sequence begins: 0, 1, 1, 3, 5, 11, 21, 43, …

They grow approximately like (2/3)·2^n. Each term is formed by
adding the previous term and twice the term before that.
*/
void PmergeMe::cache_J_vector(size_t n) {
    _J_vector.clear();

    // Upper bound: number of Jacobsthal numbers <= n is O(log n).
    if (n > 1) {
        size_t ub = 2 + static_cast<size_t>(std::log2(n));
        _J_vector.reserve(ub);
    } else {
        _J_vector.reserve(2);
    }

    if (n == 0) return;

    _J_vector.push_back(1);
    if (n == 1) return;

    _J_vector.push_back(1);

    while (true) {
        size_t k = _J_vector.size();
        size_t next = _J_vector[k - 1] + 2ULL * _J_vector[k - 2];
        if (next > n) break;
        _J_vector.push_back(next);
    }
}

PmergeMe::PmergeMe()
    : argc(0), argv(nullptr)
{

}

PmergeMe::PmergeMe(const PmergeMe& other) {
    argc = other.argc;
    argv = other.argv;
    _J_vector = other._J_vector;
    _vector = other._vector;
    _deque = other._deque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        argc = other.argc;
        argv = other.argv;
        _J_vector = other._J_vector;
        _vector = other._vector;
        _deque = other._deque;
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

void PmergeMe::insert_in_jacobsthal_order(std::vector<int> &vec, const std::vector<int> &insert_values) {
    size_t n = insert_values.size();
    if (n == 0) return;

    // Insert in reverse chunks
    size_t last = 0;
    for (size_t idx = 0; idx < _J_vector.size(); ++idx) {
        size_t j = _J_vector[idx]; // current Jacobsthal boundary

        // Insert smaller[j-1], smaller[j-2], ..., smaller[last]
        // (reverse order)
        for (size_t s = j; s > last; --s) {
            insert(vec, insert_values[s - 1]);
        }

        last = j;
    }

    // If leftover smaller elements remain
    for (size_t s = n; s > last; --s) {
        insert(vec, insert_values[s - 1]);
    }
}

void PmergeMe::sort(std::vector<int> &vec) {
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
    bigger.reserve(vec.size());
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

    sort(bigger);
    insert_in_jacobsthal_order(bigger, smaller);

    if (leftover) {
        insert(bigger, *leftover);
    }
    vec = bigger;
}

void PmergeMe::sortVector() {
    for (int i = 1; i < argc; ++i) {
        int value = parse_int(std::string(argv[i]));
        _vector.push_back(value);
    }

    sort(_vector);
}

void PmergeMe::sortDeque() {
}
