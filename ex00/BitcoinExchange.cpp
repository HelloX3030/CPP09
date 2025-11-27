#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    : data(other.data)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        data = other.data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Error: Could not open file " + filename);

    std::string line;
    if (!std::getline(file, line))
        throw std::runtime_error("Error: File " + filename + " is empty or missing header");
    line = line.substr(0, line.find_last_not_of(" \n\r\t") + 1);
    if (line != "date,exchange_rate")
        throw std::runtime_error("Error: Invalid header in file " + filename + " (expected 'date,exchange_rate') got " + line);
    while (std::getline(file, line))
    {
        line = line.substr(0, line.find_last_not_of(" \n\r\t") + 1);
        if (line.empty())
            continue;
        std::cout << line << std::endl;
        std::string date;
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            throw std::runtime_error("Error: Invalid line format in file " + filename);
        date = line.substr(0, pos);
        double value = std::stod(line.substr(pos + 1));
        data[date] = value;
    }
}

void BitcoinExchange::displayData() const
{
    for (const auto& pair : data)
        std::cout << pair.first << ": " << pair.second << std::endl;
}
