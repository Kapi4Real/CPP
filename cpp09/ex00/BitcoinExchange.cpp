#include "BitcoinExchange.hpp"

#include <cfloat>
#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

namespace
{
std::string trim(const std::string& text)
{
    std::string::size_type first = 0;
    std::string::size_type last = text.size();

    while (first < last && (text[first] == ' ' || text[first] == '\t'
            || text[first] == '\r' || text[first] == '\n'))
        ++first;
    while (last > first && (text[last - 1] == ' ' || text[last - 1] == '\t'
            || text[last - 1] == '\r' || text[last - 1] == '\n'))
        --last;
    return text.substr(first, last - first);
}

bool isDigits(const std::string& text, std::string::size_type first,
    std::string::size_type count)
{
    std::string::size_type index = first;

    while (index < first + count)
    {
        if (text[index] < '0' || text[index] > '9')
            return false;
        ++index;
    }
    return true;
}

bool isValidDate(const std::string& date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    if (!isDigits(date, 0, 4) || !isDigits(date, 5, 2)
        || !isDigits(date, 8, 2))
        return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (year == 0 || month < 1 || month > 12)
        return false;
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    return true;
}

bool parseNumber(const std::string& text, double& value)
{
    std::string cleaned = trim(text);
    char* end = 0;

    if (cleaned.empty())
        return false;
    errno = 0;
    value = std::strtod(cleaned.c_str(), &end);
    if (errno == ERANGE || end == cleaned.c_str() || *end != '\0')
        return false;
    if (value != value || value > DBL_MAX || value < -DBL_MAX)
        return false;
    return true;
}

void printBadInput(const std::string& text)
{
    std::cerr << "Error: bad input => " << text << std::endl;
}
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    : _rates(other._rates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _rates = other._rates;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

bool BitcoinExchange::loadDatabase(const std::string& path)
{
    std::ifstream database(path.c_str());
    std::string line;
    bool firstLine = true;

    if (!database.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return false;
    }
    while (std::getline(database, line))
    {
        if (firstLine)
        {
            firstLine = false;
            if (trim(line) == "date,exchange_rate")
                continue;
        }
        if (trim(line).empty())
            continue;

        std::string::size_type comma = line.find(',');
        if (comma == std::string::npos
            || line.find(',', comma + 1) != std::string::npos)
        {
            std::cerr << "Error: invalid database." << std::endl;
            return false;
        }

        std::string date = trim(line.substr(0, comma));
        double rate = 0.0;
        if (!isValidDate(date) || !parseNumber(line.substr(comma + 1), rate)
            || rate < 0.0)
        {
            std::cerr << "Error: invalid database." << std::endl;
            return false;
        }
        _rates[date] = rate;
    }
    if (_rates.empty())
    {
        std::cerr << "Error: invalid database." << std::endl;
        return false;
    }
    return true;
}

void BitcoinExchange::processInput(const std::string& path) const
{
    std::ifstream input(path.c_str());
    std::string line;
    bool firstLine = true;

    if (!input.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    while (std::getline(input, line))
    {
        std::string cleanedLine = trim(line);
        if (cleanedLine.empty())
            continue;
        if (firstLine)
        {
            firstLine = false;
            if (cleanedLine == "date | value" || cleanedLine == "date|value")
                continue;
        }

        std::string::size_type separator = line.find('|');
        if (separator == std::string::npos
            || line.find('|', separator + 1) != std::string::npos)
        {
            printBadInput(cleanedLine);
            continue;
        }

        std::string date = trim(line.substr(0, separator));
        std::string valueText = trim(line.substr(separator + 1));
        double value = 0.0;
        if (!isValidDate(date))
        {
            printBadInput(date);
            continue;
        }
        if (!parseNumber(valueText, value))
        {
            printBadInput(cleanedLine);
            continue;
        }
        if (value < 0.0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000.0)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        std::map<std::string, double>::const_iterator rate = _rates.lower_bound(date);
        if (rate == _rates.begin() && rate->first != date)
        {
            std::cerr << "Error: no earlier exchange rate available." << std::endl;
            continue;
        }
        if (rate == _rates.end() || rate->first != date)
            --rate;
        std::cout << date << " => " << value << " = " << value * rate->second
                  << std::endl;
    }
}
