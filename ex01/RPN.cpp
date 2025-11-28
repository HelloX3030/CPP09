#include "RPN.hpp"

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

RPN::RPN(const char *str)
{
    (void)str;
}

std::string RPN::to_string()
{
    return std::string();
}

int RPN::calc()
{
    return 0;
}
