#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>

class BitcoinExchange
{
    private:
        std::map<std::string, double> data;

    public:
        // Canonical Form
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        // Special Constructors
        BitcoinExchange(const std::string& filename);

        void displayData() const;
};
