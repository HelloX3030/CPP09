#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <sstream>

class BitcoinExchange
{
    private:
        std::map<std::string, double> data;

        // Helper
        void load_btc_data(const std::string& filename);

    public:
        // Canonical Form
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        // Special Constructors
        BitcoinExchange(const std::string& btc_dat_filename);

        void displayData() const;
        void displayUserData(const std::string& filename) const;
};
