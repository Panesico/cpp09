#include "../include/RPN.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << RED << " <RPN_expression>" << RESET << std::endl;
        return 1;
    }

    RPN rpn;
    try {
        std::string tokens;  // Single string used as a matrix to store all tokens
        int numTokens = rpn.parseRPN(argv[1], tokens);

        // Calculate the result
        int result = rpn.calculate(tokens, numTokens);

        // Print the result
        std::cout << GREEN << result << RESET << std::endl;

    } catch (const std::exception &e) {
        std::cerr << RED << "Error" << RESET << ": " << e.what() << std::endl;
        return 1;
    }

    return 0;
}