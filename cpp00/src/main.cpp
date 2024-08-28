#include "../include/bitcoinExchange.hpp"

int main(int argc, char* argv[]) {
    BitcoinExchange exchange;

    if ( argc != 2 ) {
        std::cerr << "Usage: " << argv[0] << RED << " <filename>" << RESET << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    try {
        exchange.readCSV("data.csv");
        exchange.printExchangeRates(filename);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
