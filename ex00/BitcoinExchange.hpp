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
        std::map<std::string, double> user_data;

        // Helper
        void load_btc_data(const std::string& filename);
        void load_user_data(const std::string& filename);

    public:
        // Canonical Form
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        // Special Constructors
        BitcoinExchange(const std::string& btc_dat_filename, const std::string& user_data_filename);

        void displayData() const;
        void displayUserData() const;
};
