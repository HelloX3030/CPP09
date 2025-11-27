#include "BitcoinExchange.hpp"

static void validate_date(const std::string &date) {
    int year, month, day;
    char sep1, sep2;
    std::stringstream ss(date);

    ss >> year >> sep1 >> month >> sep2 >> day;
    if (!ss || sep1 != '-' || sep2 != '-') {
        throw std::runtime_error("Invalid date format: " + date);
    }

    // Check month range
    if (month < 1 || month > 12) {
        throw std::runtime_error("Invalid month: " + std::to_string(month));
    }

    // Check day range
    if (day < 1 || day > 31) {
        throw std::runtime_error("Invalid day: " + std::to_string(day));
    }

    // Months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        throw std::runtime_error("Invalid day for month: " + std::to_string(day));
    }

    // February and leap year
    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (month == 2 && ((leap && day > 29) || (!leap && day > 28))) {
        throw std::runtime_error("Invalid day for February");
    }
}

void BitcoinExchange::load_btc_data(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Error: Could not open file " + filename);

    // Validate Header
    std::string line;
    if (!std::getline(file, line))
        throw std::runtime_error("Error: File " + filename + " is empty or missing header");
    line.erase(0, line.find_first_not_of(" \n\r\t"));
    line.erase(line.find_last_not_of(" \n\r\t") + 1);
    if (line != "date,exchange_rate")
        throw std::runtime_error("Error: Invalid header in file " + filename + " (expected 'date,exchange_rate') got " + line);
    
    // Process data lines
    while (std::getline(file, line))
    {
        // Trim
        line.erase(0, line.find_first_not_of(" \n\r\t"));
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        if (line.empty())
            continue;
        
        // Extract Date
        std::string date;
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            throw std::runtime_error("Error: Invalid line format in file " + filename + " (expected 'date|value') got \"" + line + "\"");
        date = line.substr(0, pos);
        std::string value_str = line.substr(pos + 1);
        validate_date(date);

        // Parse Value
        pos = 0;
        double value;
        try {
            value = std::stod(value_str, &pos);
            if (pos != value_str.size()) {
                throw std::runtime_error("Invalid characters in value: " + value_str);
            }
        } catch(const std::exception& e) {
            throw std::runtime_error("Error: Invalid value for date " + date + " value: " + value_str);
        }
        if (value < 0)
            throw std::runtime_error("Error: Negative value for date " + date + " value: " + value_str);
        data[date] = value;
    }
}

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

BitcoinExchange::BitcoinExchange(const std::string& btc_dat_filename)
{
    load_btc_data(btc_dat_filename);
}

void BitcoinExchange::displayData() const
{
    for (const auto& pair : data)
        std::cout << pair.first << ": " << pair.second << std::endl;
}

void BitcoinExchange::displayUserData(const std::string& filename) const
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Error: Could not open file " + filename);
    
    // Validate Header
    std::string line;
    if (!std::getline(file, line))
        throw std::runtime_error("Error: File " + filename + " is empty or missing header");
    line.erase(0, line.find_first_not_of(" \n\r\t"));
    line.erase(line.find_last_not_of(" \n\r\t") + 1);
    size_t pos = line.find('|');
    if (pos == std::string::npos)
        throw std::runtime_error("Error: Invalid header format in file " + filename + " (expected 'date|value') got \"" + line + "\"");
    std::string date_str = line.substr(0, pos);
    date_str.erase(line.find_last_not_of(" \n\r\t") + 1);
    if (date_str != "date")
        throw std::runtime_error("Error: Invalid header format in file " + filename + " (expected 'date|value') got \"" + line + "\"");
    std::string value_str = line.substr(pos + 1);
    value_str.erase(0, value_str.find_first_not_of(" \n\r\t"));
    value_str.erase(value_str.find_last_not_of(" \n\r\t") + 1);
    if (value_str != "value")
        throw std::runtime_error("Error: Invalid header format in file " + filename + " (expected 'date|value') got \"" + line + "\"");
    
    // Load Values
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}
