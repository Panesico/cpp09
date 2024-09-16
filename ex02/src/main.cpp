#include "../include/PMergeMe.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << RED << " <numbers...>" << RESET << std::endl;
        return 1;
    }

    PMergeMe pm;
    for (int i = 1; i < argc; ++i) {
        if (!pm.parseArgument(argv[i])) {
            return 1;
        }
    }

    std::vector<unsigned long> &vector = pm.getVector();
    std::list<unsigned long> &list = pm.getList();

    for (int i = 1; i < argc; ++i) {
        // Add the argument to both the vector and the list
        vector.push_back(std::strtoul(argv[i], 0, 10));
        list.push_back(std::strtoul(argv[i], 0, 10));
    }
	std::cout << "Starting numbers: ";
	for (std::vector<unsigned long>::iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::clock_t start_time = std::clock();
    pm.sortVector();
    std::clock_t after_time = std::clock();
    double duration = static_cast<double>(after_time - start_time) / CLOCKS_PER_SEC;

    std::cout << std::endl;
	std::cout << "Sorted numbers: ";
    for (std::vector<unsigned long>::iterator it = pm.getTempVectors().front().begin(); it != pm.getTempVectors().front().end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(6) << "Time to process a range of " << RED << pm.getTempVectors().front().size() << RESET
              << " elements with " << GREEN << "std::vector : " << BLUE << duration << RESET << " us" << std::endl;

    start_time = std::clock();
    pm.sortList();
    after_time = std::clock();
    duration = static_cast<double>(after_time - start_time) / CLOCKS_PER_SEC;

    std::cout << std::fixed << std::setprecision(6) << "Time to process a range of " << RED << pm.getTempVectors().front().size() << RESET
              << " elements with " << GREEN << "std::list : " << BLUE << duration << RESET << " us" << std::endl;

    return 0;
}
