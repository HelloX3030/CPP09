#pragma once

#include <string>
#include <iostream>

class BitcoinExchange
{
    private:
    public:
        // Canonical Form
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        // Special Constructors
        BitcoinExchange(const std::string& filename);
};
