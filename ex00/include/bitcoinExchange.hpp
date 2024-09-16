#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <sys/stat.h>
#include <ctime>
#include <limits>
#include <cstdlib>
#include <cstring>
#include <iomanip>

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

class BitcoinExchange {
private:
    std::map<time_t, double> exchangeRates;
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &rpn);
    BitcoinExchange &operator=(const BitcoinExchange &rpn);
    ~BitcoinExchange();
    void readCSV(const std::string& filename);
    time_t parseDateToUnixTime(const std::string& date);
    bool isDirectory(const std::string& path);
	double getExchange(time_t date);
    void printExchangeRates(const std::string& filename);
    std::string unixTimeToDate(time_t unix_time);
    std::string trim(const std::string& str);
    std::map<time_t, double> getExchangeRates() const;
    void setExchangeRates(std::map<time_t, double> &exchangeRates);
};

#endif // BITCOINEXCHANGE_HPP
