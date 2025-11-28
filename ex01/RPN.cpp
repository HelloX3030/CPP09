#include "RPN.hpp"

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \n\r\t");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \n\r\t");
    return s.substr(start, end - start + 1);
}

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
    _stack = other._stack;
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN()
{
}

RPN::RPN(const std::string &str)
{
    std::string input = trim(str);
    size_t pos = input.find_first_of(" ");
    while (pos != std::string::npos)
    {
        std::string token = input.substr(0, pos);
        _stack.push(token);
        input = trim(input.substr(pos + 1));
        pos = input.find_first_of(" ");
    }
    if (!input.empty()) {
        _stack.push(input);
    }
}

int RPN::calc()
{
    while (_stack.size())
    {
        std::string token = _stack.top();
        std::cout << token << " ";
        _stack.pop();
    }
    std::cout << std::endl;
    return 0;
}
