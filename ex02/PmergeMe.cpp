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

static void insert(std::deque<int> &deq, int value) {
    int n = deq.size();
    deq.push_back(0); // make space
    int i = n - 1;
    while (i >= 0 && deq[i] > value) {
        deq[i + 1] = deq[i]; // shift right
        i--;
    }
    deq[i + 1] = value;
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
        // J(k) = J(k-1) + 2*J(k-2)
        // => 2ULL to avoid overflow for large k, by promoting to unsigned long long
        unsigned long long next = _J_vector[k - 1] + 2ULL * _J_vector[k - 2];
        if (next > n) break;
        _J_vector.push_back(next);
    }
}

void PmergeMe::cache_J_deque(size_t n) {
    _J_deque.clear();

    if (n == 0) return;

    _J_deque.push_back(1);
    if (n == 1) return;

    _J_deque.push_back(1);

    while (true) {
        size_t k = _J_deque.size();
        // J(k) = J(k-1) + 2*J(k-2)
        // => 2ULL to avoid overflow for large k, by promoting to unsigned long long
        unsigned long long next = _J_deque[k - 1] + 2ULL * _J_deque[k - 2];
        if (next > n) break;
        _J_deque.push_back(next);
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
    _J_deque = other._J_deque;
    _vector = other._vector;
    _deque = other._deque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        argc = other.argc;
        argv = other.argv;
        _J_vector = other._J_vector;
        _J_deque = other._J_deque;
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

void PmergeMe::verifySorted() const {
    if (_vector.size() != _deque.size()) {
        throw std::runtime_error("Error: Vector and Deque sizes differ.");
    }
    if (_vector.size() != static_cast<size_t>(argc - 1)) {
        throw std::runtime_error("Error: Sorted size does not match input size.");
    }
    for (size_t i = 0; i < _vector.size(); ++i) {
        if (_vector[i] != _deque[i]) {
            throw std::runtime_error("Error: Vector and Deque sorted results differ.");
        }
        if (i > 0 && _vector[i] < _vector[i - 1]) {
            throw std::runtime_error("Error: Vector is not sorted correctly.");
        }
    }
}

/*
    Inserts elements from 'insert_values' into 'vec' following the
    Jacobsthal order, which is used in Ford–Johnson merge-insertion
    sorting.

    The process works as follows:
      1. Iterate through the cached Jacobsthal numbers (_J_vector),
         which define the boundaries for insertion.
      2. For each Jacobsthal number j, insert elements
         from j-1 down to last.
      3. Clamp j to the size of insert_values to avoid out-of-bounds
         access.
      4. Continue until all elements from insert_values are inserted.
      5. Any leftover elements beyond the last Jacobsthal boundary
         are inserted at the end.
*/

void PmergeMe::insert_in_jacobsthal_order(std::vector<int> &vec, const std::vector<int> &insert_values) {
    size_t n = insert_values.size();
    if (n == 0) return;

    // Insert in reverse chunks
    size_t last = 0;
    for (size_t idx = 0; idx < _J_vector.size(); ++idx) {
        size_t j = _J_vector[idx];

        // Ensure we do not exceed the insert_values size
        if (j > n) j = n;

        // Insert smaller[j-1], ..., smaller[last]
        for (size_t s = j; s > last; --s) {
            insert(vec, insert_values[s - 1]);
        }

        last = j;

        // Stop if we have inserted all elements
        if (last == n) break;
    }

    // If leftover smaller elements remain
    for (size_t s = n; s > last; --s) {
        insert(vec, insert_values[s - 1]);
    }
}

void PmergeMe::insert_in_jacobsthal_order(std::deque<int> &deq, const std::deque<int> &insert_values) {
    size_t n = insert_values.size();
    if (n == 0) return;

    // Insert in reverse chunks
    size_t last = 0;
    for (size_t idx = 0; idx < _J_deque.size(); ++idx) {
        size_t j = _J_vector[idx];

        // Ensure we do not exceed the insert_values size
        if (j > n) j = n;

        // Insert smaller[j-1], ..., smaller[last]
        for (size_t s = j; s > last; --s) {
            insert(deq, insert_values[s - 1]);
        }

        last = j;

        // Stop if we have inserted all elements
        if (last == n) break;
    }

    // If leftover smaller elements remain
    for (size_t s = n; s > last; --s) {
        insert(deq, insert_values[s - 1]);
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

void PmergeMe::sort(std::deque<int> &deq) {
    if ( deq.size() <= 1 ) return;

    // Get Leftover element if the size is odd
    std::optional<int> leftover;
    if (deq.size() % 2 != 0) {
        leftover = deq.back();
    }

    // Create pairs
    size_t pair_count = deq.size() / 2;
    std::deque<int> bigger;
    std::deque<int> smaller;
    for (size_t i = 0; i < pair_count; ++i) {
        int first = deq[2 * i];
        int second = deq[2 * i + 1];
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
    deq = bigger;
}

void PmergeMe::sortVector() {
    _vector.reserve(argc - 1);
    for (int i = 1; i < argc; ++i) {
        int value = parse_int(std::string(argv[i]));
        _vector.push_back(value);
    }

    sort(_vector);
}

void PmergeMe::sortDeque() {
    for (int i = 1; i < argc; ++i) {
        int value = parse_int(std::string(argv[i]));
        _deque.push_back(value);
    }

    sort(_deque);
}
