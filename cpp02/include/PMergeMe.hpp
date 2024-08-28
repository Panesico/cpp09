#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <cstdlib>   // For strtoul
#include <cstring>   // For strlen
#include <algorithm> // For sort
#include <iterator>  // For back_inserter
#include <limits>    // For numeric_limits
#include <iomanip>
#include <ctime>

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"

class PMergeMe {
private:
    std::vector<std::vector<unsigned long> > tempvectors;
    std::list<std::list<unsigned long> > templists;
    std::vector<unsigned long> vector;
    std::list<unsigned long> list;
public:
    PMergeMe();
    PMergeMe(const PMergeMe &rpn);
    PMergeMe &operator=(const PMergeMe &rpn);
    ~PMergeMe();
    std::vector<std::vector<unsigned long> > &getTempVectors();
    std::list<std::list<unsigned long> > &getTempLists();
    std::vector<unsigned long> &getVector();
    std::list<unsigned long> &getList();
    bool isNumber(const char* str);
    bool parseArgument(const char* arg);
    void sortVector();
    void sortList();
};

#endif // PMergeMe_HPP