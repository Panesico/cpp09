#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"

class RPN {
private:
    std::stack<int> stack;

public:
    RPN();
    RPN(const RPN &rpn);
    RPN &operator=(const RPN &rpn);
    ~RPN();
    std::stack<int> &getStack();
    bool isOperator(const std::string &token);
    bool isNumber(const std::string &token);
    int calculate(const std::string &tokens, int numTokens);
    int parseRPN(const std::string &expression, std::string &tokens);
    bool validateRPN(const std::string &tokens, int numTokens);
    std::string getToken(const std::string &tokens, int index);
};

#endif // RPN_HPP