#pragma once

#include <string>
#include <stack>
#include <iostream>

class RPN
{
    private:
        std::stack<std::string> _stack;
        std::stack<int> _operands;

    public:
        // Canonical Form
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        // Special Constructor
        RPN(const std::string &str);

        // Functions
        int calc();
};
