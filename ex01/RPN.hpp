#pragma once

#include <string>
#include <stack>

class RPN
{
    private:
        std::stack<std::string>  _stack;

    public:
        // Canonical Form
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        // Special Constructor
        RPN(const char *str);

        // Functions
        std::string to_string();
        int calc();
};
