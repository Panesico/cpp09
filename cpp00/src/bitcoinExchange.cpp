#include "../include/bitcoinExchange.hpp"

// Constructor

BitcoinExchange::BitcoinExchange() {
}

// Copy constructor

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rpn) {
    exchangeRates = rpn.exchangeRates;
}

// Assignment operator

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rpn) {
    exchangeRates = rpn.exchangeRates;
    return *this;
}

// Destructor

BitcoinExchange::~BitcoinExchange() {
}


// Function to check if a file is a directory
bool BitcoinExchange::isDirectory(const std::string& path) {
    struct stat fileInfo;
    if (stat(path.c_str(), &fileInfo) != 0) {
        return false; // Cannot access the file or it does not exist
    }
    return S_ISDIR(fileInfo.st_mode);
}

// Function to validate and convert date to UNIX time
time_t BitcoinExchange::parseDateToUnixTime(const std::string& date) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));  // Initialize to zero
    if (strptime(date.c_str(), "%Y-%m-%d", &tm) == NULL) {
        std::cout << RED << "Error" << RESET << ": Invalid date format. Expected YYYY-MM-DD.";
        return -1;
    }

    int original_day = tm.tm_mday;
    int original_month = tm.tm_mon;
    int original_year = tm.tm_year;

    tm.tm_isdst = -1; // Not setting daylight saving time
    time_t epoch_time = mktime(&tm);
    if (epoch_time == -1) {
        std::cout << RED << "Error" << RESET << ": Failed to convert date to UNIX time.";
        return -1;
    }
    // Validate if the date was correctly parsed and normalized
    if (tm.tm_mday != original_day || tm.tm_mon != original_month || tm.tm_year != original_year) {
        std::cout << RED "Error" RESET ": bad input => " << BLUE << date << RESET << std::endl;
        return -1;
    }
    return epoch_time;
}

std::string BitcoinExchange::unixTimeToDate(time_t unix_time) {
    struct tm *timeinfo;
    char buffer[11]; // YYYY-MM-DD -> 10 characters + 1 for null terminator

    // Convert the UNIX time to a struct tm using localtime
    timeinfo = localtime(&unix_time);

    // Format the date as YYYY-MM-DD
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);

    return std::string(buffer);
}


// Function to read a CSV file and store its contents in a map
void BitcoinExchange::readCSV(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::map<time_t, double> &data = getExchangeRates();
    // Check if the file was opened successfully
    if (!file.is_open()) {
        throw std::runtime_error(RED "Error" RESET ": Could not open the " YELLOW ".csv " RESET "file.");
    }

    // Check if the file is a directory
    if (isDirectory(filename)) {
        throw std::runtime_error(RED "Error" RESET ": The " YELLOW ".csv " RESET "file is a directory.");
    }

    std::string line;
    std::string date_str;
    std::string exchange_rate_str;

    std::getline(file, line);
    std::stringstream lineStream(line);
    std::getline(lineStream, date_str, ',');
    std::getline(lineStream, exchange_rate_str);

    date_str = trim(date_str);
    exchange_rate_str = trim(exchange_rate_str);

    if (date_str != "date" || exchange_rate_str != "exchange_rate") {
        throw std::runtime_error(RED "Error" RESET ": Invalid CSV header.");
    }

    while (std::getline(file, line)) {
        date_str.clear();
        exchange_rate_str.clear();
        lineStream.clear(); // Clear any error flags
        lineStream.str(line);
        if (std::getline(lineStream, date_str, ',') && std::getline(lineStream, exchange_rate_str)) {
            date_str = trim(date_str);
            exchange_rate_str = trim(exchange_rate_str);
            // Validate and parse the date to UNIX time
            time_t unix_time = parseDateToUnixTime(date_str);
            if (unix_time == -1) {
                continue;
            }
            // Validate and parse the exchange rate to double
            char* endptr;
            double exchange_rate = strtod(exchange_rate_str.c_str(), &endptr);
            if (*endptr != '\0') {
                std::cout << RED "Error" RESET ": Exchange rate is not a valid number." << " => " YELLOW "inside data.csv" << RESET << std::endl;
            }

            // Check for overflow and range
            if (exchange_rate == std::numeric_limits<double>::infinity()) {
                std::cout << RED "Error" RESET ": Exchange rate out of valid range (Overflow!)." << " => " YELLOW "inside data.csv" << RESET << std::endl;
            }

            if (exchange_rate < 0) {
                std::cout << RED "Error" RESET ": not a positive number." << " => " YELLOW "inside data.csv" << RESET << std::endl;
                continue;
            }

            // Store the data in the map
            data[unix_time] = exchange_rate;
        } else {
            std::cout << RED "Error" RESET ": bad input => " << BLUE << line << RESET << " inside data.csv" << std::endl;
        }
    }

    file.close();
}

// Function to get the exchange rates map
std::map<time_t, double> &BitcoinExchange::getExchangeRates() {
    return exchangeRates;
}

double BitcoinExchange::getExchange(time_t date) {
    std::map<time_t, double> &data = getExchangeRates();

    std::map<time_t, double>::iterator it = data.begin();

    if (data.empty()) {
        std::cout << "No exchange rates found." << std::endl;
        throw std::exception();
    }
    time_t chosenDate = it->first;
    while (it != data.end() && it->first < date) {
        chosenDate = it->first;
        ++it;
    }
    return data[chosenDate];
}

// Remove leading whitespace

std::string BitcoinExchange::trim(const std::string& str) {
    std::string result = str;

    size_t start = result.find_first_not_of(" \t\n\r\f\v");
    if (start != std::string::npos) {
        result = result.substr(start);
    } else {
        return "";
    }

    size_t end = result.find_last_not_of(" \t\n\r\f\v");
    if (end != std::string::npos) {
        result = result.substr(0, end + 1);
    }

    return result;
}

void BitcoinExchange::printExchangeRates(const std::string& filename) {
    std::ifstream file(filename.c_str());
    // Check if the file was opened successfully
    if (!file.is_open()) {
        throw std::runtime_error(RED "Error" RESET ": Could not open the " YELLOW "argv[1] " RESET "file.");
    }

    // Check if the file is a directory
    if (isDirectory(filename)) {
        throw std::runtime_error(RED "Error" RESET ": The " YELLOW "argv[1] " RESET "file is a directory.");
    }

    std::string line;
    std::string date_str;
    std::string bitcoins_str;

    std::getline(file, line);
    std::stringstream lineStream(line);
    std::getline(lineStream, date_str, '|');
    std::getline(lineStream, bitcoins_str);

    // remove isspace from the string start and end

    date_str = trim(date_str);
    bitcoins_str = trim(bitcoins_str);

    if (date_str != "date" || bitcoins_str != "value") {
        std::cout << date_str << " " << bitcoins_str << std::endl;

        throw std::runtime_error(RED "Error" RESET ": Invalid CSV header.");
    }

    while (std::getline(file, line)) {
        date_str.clear();
        bitcoins_str.clear();
        lineStream.clear(); // Clear any error flags
        lineStream.str(line);
        if (std::getline(lineStream, date_str, '|') && std::getline(lineStream, bitcoins_str)) {
            // Validate and parse the date to UNIX time
            date_str = trim(date_str);
            bitcoins_str = trim(bitcoins_str);

            time_t unix_time = parseDateToUnixTime(date_str);
            if (unix_time == -1) {
                continue;
            }

            // Validate and parse the exchange rate to double
            char* endptr;
            double bitcoins = strtod(bitcoins_str.c_str(), &endptr);
            if (*endptr != '\0') {
                throw std::runtime_error(RED "Error" RESET ": Exchange rate is not a valid number.");
            }

            // Check for overflow and range
            if (bitcoins == std::numeric_limits<double>::infinity()) {
                std::cout << RED "Error" RESET ": Exchange rate out of valid range (Overflow!)." << std::endl;
                continue;
            }
            if (bitcoins < 0) {
                std::cout << RED "Error" RESET ": not a positive number." << std::endl;
                continue;
            }
            if (bitcoins > 1000.0) {
                std::cout << RED "Error" RESET ": too large of a number" << std::endl;
                continue;
            }

            std::cout << BLUE << unixTimeToDate(unix_time) << RESET << " => " << YELLOW << bitcoins << RESET << " = " << GREEN << bitcoins * getExchange(unix_time) << RESET << std::endl;
        } else {
            std::cout << RED "Error" RESET ": bad input => " << BLUE << line << RESET << std::endl;
        }
    }

    file.close();
}