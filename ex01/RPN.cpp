#include "RPN.hpp"

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \n\r\t");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \n\r\t");
    return s.substr(start, end - start + 1);
}

static bool is_operator(const std::string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

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

static int apply_operator(int left, int right, const std::string &op) {
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") {
        if (right == 0)
            throw std::runtime_error("Error: Division by zero");
        return left / right;
    }
    throw std::runtime_error("Error: Unknown operator: " + op);
}

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
    _stack = other._stack;
    _operands = other._operands;
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other) {
        _stack = other._stack;
        _operands = other._operands;
    }
    return *this;
}

RPN::~RPN()
{
}

RPN::RPN(const std::string &str)
{
    std::string input = trim(str);

    while (!input.empty()) {
        size_t pos = input.find_last_of(' ');
        if (pos == std::string::npos) {
            _stack.push(input);
            break;
        }
        _stack.push(input.substr(pos + 1));
        input = trim(input.substr(0, pos));
    }
}


int RPN::calc()
{
    while (_stack.size())
    {
        std::string token = _stack.top();
        _stack.pop();
        if (is_operator(token)) {
            if (_operands.size() < 2)
                throw std::runtime_error("Error: Not enough operands for operator " + token);
            int right, left;
            right = _operands.top();
            _operands.pop();
            left = _operands.top();
            _operands.pop();
            int result = apply_operator(left, right, token);
            _operands.push(result);
        }
        else {
            _operands.push(parse_int(token));
        }
    }
    if (_operands.size() != 1) {
        throw std::runtime_error("Error: Invalid RPN expression, remaining operands: " + std::to_string(_operands.size()));
    }
    return _operands.top();
}
