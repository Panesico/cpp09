#include "../include/RPN.hpp"

RPN::RPN() {
}

RPN::~RPN() {
}

RPN::RPN(const RPN &rpn) {
    (void)rpn;  // Mark rpn as unused to avoid the compiler warning
    std::cout << "RPN copy constructor" << std::endl;
}

RPN &RPN::operator=(const RPN &rpn) {
    (void)rpn;  // Mark rpn as unused to avoid the compiler warning
    std::cout << "RPN copy assignment" << std::endl;
    return *this;
}

std::stack<int> &RPN::getStack() {
    return stack;
}

bool RPN::isOperator(const std::string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RPN::isNumber(const std::string &token) {
    for (size_t i = 0; i < token.size(); ++i) {
        if (!std::isdigit(token[i])) {
            return false;
        }
    }
    std::stringstream ss(token);
    int number;
    ss >> number;
    return number < 10;
}

bool RPN::validateRPN(const std::string &tokens, int numTokens) {
    int operandCount = 0;
    for (int i = 0; i < numTokens; ++i) {
        std::string token = getToken(tokens, i);
        if (isNumber(token)) {
            operandCount++;
        } else if (isOperator(token)) {
            if (operandCount < 2) {
                return false; // Not enough operands
            }
            operandCount--; // Replace two operands with one result
        } else {
            return false; // Invalid token
        }
    }
    return operandCount == 1; // Only one result should remain
}

int RPN::calculate(const std::string &tokens, int numTokens) {
    // Reset the stack before calculation
    while (!stack.empty()) stack.pop();

    if (!validateRPN(tokens, numTokens)) {
        throw std::invalid_argument("Invalid RPN expression");
    }

    for (int i = 0; i < numTokens; ++i) {
        std::string token = getToken(tokens, i);
        if (isNumber(token)) {
            std::stringstream ss(token);
            int number;
            ss >> number;
            stack.push(number);
        } else if (isOperator(token)) {
            if (stack.size() < 2) {
                throw std::invalid_argument("Insufficient operands for the operator");
            }
            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();
            if (token == "+") {
                stack.push(operand1 + operand2);
            } else if (token == "-") {
                stack.push(operand1 - operand2);
            } else if (token == "*") {
                stack.push(operand1 * operand2);
            } else if (token == "/") {
                if (operand2 == 0) {
                    throw std::invalid_argument("Division by zero");
                }
                stack.push(operand1 / operand2);
            }
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("The RPN expression is invalid");
    }

    return stack.top();
}

int RPN::parseRPN(const std::string &expression, std::string &tokens) {
    std::stringstream ss(expression);
    std::string token;
    int tokenCount = 0;

    while (ss >> token) {
        if (tokenCount > 0) {
            tokens += ' '; // Add a space delimiter between tokens
        }
        tokens += token;
        tokenCount++;
    }

    return tokenCount; // Return the number of tokens parsed
}

std::string RPN::getToken(const std::string &tokens, int index) {
    std::stringstream ss(tokens);
    std::string token;
    int i = 0;

    while (std::getline(ss, token, ' ')) {
        if (i == index) {
            return token;
        }
        i++;
    }
    return "";
}