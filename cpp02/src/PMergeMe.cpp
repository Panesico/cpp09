#include "../include/PMergeMe.hpp"

PMergeMe::PMergeMe() {
}

PMergeMe::~PMergeMe() {
}

PMergeMe::PMergeMe(const PMergeMe &rpn) {
    (void)rpn;
    std::cout << "PMergeMe copy constructor" << std::endl;
}

PMergeMe &PMergeMe::operator=(const PMergeMe &rpn) {
    (void)rpn;
    std::cout << "PMergeMe copy assignment" << std::endl;
    return *this;
}

std::vector<std::vector<unsigned long> > &PMergeMe::getTempVectors() {
    return tempvectors;
}

std::list<std::list<unsigned long> > &PMergeMe::getTempLists() {
    return templists;
}

std::vector<unsigned long> &PMergeMe::getVector() {
    return vector;
}

std::list<unsigned long> &PMergeMe::getList() {
    return list;
}

bool PMergeMe::isNumber(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    for (std::size_t i = 0; i < std::strlen(str); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool PMergeMe::parseArgument(const char* arg) {
    if (!isNumber(arg)) {
        std::cerr << "Error: Argument \"" << arg << "\" is not a valid number." << std::endl;
        return false;
    }

    // Convert to unsigned long
    char* end;
    unsigned long value = std::strtoul(arg, &end, 10);

    // Check if conversion was successful
    if (end == arg || *end != '\0') {
        std::cerr << "Error: Argument \"" << arg << "\" is not a valid number." << std::endl;
        return false;
    }

    // Check for overflow
    if (value > std::numeric_limits<unsigned long>::max()) {
        std::cerr << "Error: Argument \"" << arg << "\" exceeds the maximum value for unsigned long." << std::endl;
        return false;
    }

    return true;
}

void PMergeMe::sortVector() {

    for (std::vector<unsigned long>::iterator it = vector.begin(); it != vector.end(); ++it) {
        std::vector<unsigned long> temp;
        temp.push_back(*it);

        std::vector<unsigned long>::iterator next = it;
        ++next;
        if (next != vector.end()) {
            temp.push_back(*next);
            it = next;
        }

        if (temp.size() == 2 && temp[0] > temp[1]) {
            std::swap(temp[0], temp[1]);
        }

        tempvectors.push_back(temp);
    }

    while (tempvectors.size() > 1) {
        std::vector<std::vector<unsigned long> > mergedVectors;

        for (size_t i = 0; i + 1 < tempvectors.size(); i += 2) {
            std::vector<unsigned long>& firstVector = tempvectors[i];
            std::vector<unsigned long>& secondVector = tempvectors[i + 1];

            std::vector<unsigned long> mergedVector;
            mergedVector.reserve(firstVector.size() + secondVector.size());

            std::vector<unsigned long>::iterator jt1 = firstVector.begin();
            std::vector<unsigned long>::iterator jt2 = secondVector.begin();

            while (jt1 != firstVector.end() && jt2 != secondVector.end()) {
                if (*jt1 <= *jt2) {
                    mergedVector.push_back(*jt1++);
                } else {
                    mergedVector.push_back(*jt2++);
                }
            }

            mergedVector.insert(mergedVector.end(), jt1, firstVector.end());
            mergedVector.insert(mergedVector.end(), jt2, secondVector.end());

            mergedVectors.push_back(mergedVector);
        }

        if (tempvectors.size() % 2 != 0) {
            mergedVectors.push_back(tempvectors.back());
        }

        tempvectors.swap(mergedVectors);
    }

    if (!tempvectors.empty()) {
        vector = tempvectors.front();
        tempvectors.clear();
        tempvectors.push_back(vector);
    }
}


void PMergeMe::sortList() {
    // Initial split and sort into pairs of lists
    for (std::list<unsigned long>::iterator it = list.begin(); it != list.end(); ++it) {
        std::list<unsigned long> temp;
        temp.push_back(*it);

        // Check if there's a next element before incrementing the iterator
        std::list<unsigned long>::iterator next = it;
        ++next;
        if (next != list.end()) {
            temp.push_back(*next);
            it = next;
        }
        if (*temp.begin() > *temp.rbegin()) {
            temp.reverse();  // Reverse the list to ensure ascending order
        }
        templists.push_back(temp);
    }

    std::list<std::list<unsigned long> >::iterator it = templists.begin();

    while (templists.size() > 1) {
        it = templists.begin();
        std::list<unsigned long>& firstList = *it;

        std::list<std::list<unsigned long> >::iterator next = it;
        ++next;

        if (next != templists.end()) {
            std::list<unsigned long>& secondList = *next;

            std::list<unsigned long> resultList;
            std::list<unsigned long>::iterator jt1 = firstList.begin();
            std::list<unsigned long>::iterator jt2 = secondList.begin();

            while (jt1 != firstList.end() && jt2 != secondList.end()) {
                if (*jt1 < *jt2 && (jt1 == firstList.begin() || *jt1 >= *(--jt1)++)) {
                    resultList.push_back(*jt1);
                    ++jt1;
                } else if (*jt2 < *jt1 && (jt2 == secondList.begin() || *jt2 >= *(--jt2)++)) {
                    resultList.push_back(*jt2);
                    ++jt2;
                } else {
                    ++jt1;
                    ++jt2;
                }
            }

            while (jt1 != firstList.end()) {
                if (jt1 == firstList.begin() || *jt1 >= *(--jt1)++) {
                    resultList.push_back(*jt1);
                }
                ++jt1;
            }

            while (jt2 != secondList.end()) {
                if (jt2 == secondList.begin() || *jt2 >= *(--jt2)++) {
                    resultList.push_back(*jt2);
                }
                ++jt2;
            }

            it = templists.erase(it);
            it = templists.erase(it);

            templists.push_back(resultList);
        }
    }
}
