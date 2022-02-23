#include <iostream>
#include "filelib.h"

void sortFile(const char* fileName) {
    std::ifstream f1;
    std::ifstream f2;
    std::ofstream f3;
    std::ofstream f4;


}

int createAndSortFile(const char* fileName, const int numbersCount, const int maxNumberValue) {
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue))
        return -1;

    sortFile(fileName);

    if (!isFileContainsSortedArray(fileName))
        return -2;

    return 1;
}

int main() {
    const char* fileName = "file.txt";
    const int numbersCount = 1000000;
    const int maxNumberValue = 100000;

    for (int i = 0; i < 10; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
        case 1:
            std::cout << "Test passed." << std::endl;
            break;

        case -1:
            std::cout << "Test failed: can't create file." << std::endl;
            break;

        case -2:
            std::cout << "test failed: file isn't sorted." << std::endl;
            break;
        }
    }

    return 0;
}