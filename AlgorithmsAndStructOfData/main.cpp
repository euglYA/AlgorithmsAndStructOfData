//#include <iostream>
//#include "filelib.h"

#include <iostream>
#include "filelib.h"

bool checkForEmpty(const char* file1, const char* file2, const char* file3, const char* file4) {
    std::ifstream file;
    int count = 0;

    file.open(file1);
    if (file.peek() == EOF) count++;
    file.close();

    file.open(file2);
    if (file.peek() == EOF) count++;
    file.close();

    file.open(file3);
    if (file.peek() == EOF) count++;
    file.close();

    file.open(file4);
    if (file.peek() == EOF) count++;
    file.close();

    if (count == 3)
        return true;

    return false;
}

void split(const char* fileName, const char* fileOut1, const char* fileOut2) {
    std::ifstream file(fileName);
    std::ofstream F[2];
    F[0].open(fileOut1, std::ios::trunc);
    F[1].open(fileOut2, std::ios::trunc);

    int x1, x2, n = 0;
    file >> x1;

    while (!file.eof()) {
        F[n] << x1 << " ";
        file >> x2;

        if (x1 > x2)
            n = 1 - n;

        x1 = x2;
    }
    file.close();
    F[0].close(); F[1].close();
}

void merge(const char* fileIn1, const char* fileIn2, const char* fileOut1, const char* fileOut2) {
    std::ifstream f1(fileIn1), f2(fileIn2);
    std::ofstream s1(fileOut1), s2(fileOut2);

    int x1, x2, y1, y2;

    f1 >> y1;
    f2 >> y2;
    
    while (!f1.eof() && !f2.eof()){
        x1 = y1;
        x2 = y2;

        while (x1 <= y1 && x2 <= y2 && !f1.eof() && !f2.eof()){

            if (y1 < y2){
                s1 << y1 << " ";
                x1 = y1;
                f1 >> y1;
            }
            else{
                s1 << y2 << " ";
                x2 = y2;
                f2 >> y2;
            }
        }

        while (x1 <= y1 && !f1.eof()){
            s1 << y1 << " ";
            x1 = y1;
            f1 >> y1;

        }

        while (x2 <= y2 && !f2.eof()){
            s1 << y2 << " ";
            x2 = y2;
            f2 >> y2;

        }

        //---

        x1 = y1;
        x2 = y2;

        while (x1 <= y1 && x2 <= y2 && !f1.eof() && !f2.eof()){

            if (y1 < y2){
                s2 << y1 << " ";
                x1 = y1;
                f1 >> y1;
            }
            else{
                s2 << y2 << " ";
                x2 = y2;
                f2 >> y2;
            }
        }

        while (x1 <= y1 && !f1.eof()){
            s2 << y1 << " ";
            x1 = y1;
            f1 >> y1;
        }

        while (x2 <= y2 && !f2.eof()){
            s2 << y2 << " ";
            x2 = y2;
            f2 >> y2;
        }

    }

    while (!f1.eof()){
        s1 << y1 << " ";
        f1 >> y1;
    }

    while (!f2.eof()){
        s2 << y2 << " ";
        f2 >> y2;
    }

    f1.close(); f2.close();
    s1.close(); s2.close();

    s1.open(fileIn1, std::ios_base::trunc);
    s2.open(fileIn2, std::ios_base::trunc);
    s1.close(); s2.close();
}

void sort(const char* fileName) {
    split(fileName, "s1.txt", "s2.txt");

    while (!checkForEmpty(fileName, "f1.txt", "s1.txt", "s2.txt")) {
        std::cout << "1| ";
        merge("s1.txt", "s2.txt", fileName, "f1.txt");
        std::cout << "2| ";
        merge(fileName, "f1.txt", "s1.txt", "s2.txt");
    }
}

const char* whatFileIsSorted(const char* file1, const char* file2, const char* file3, const char* file4) {
    std::ifstream file;
    
    file.open(file1);
    if (!(file.peek() == EOF)) return file1;
    file.close();

    file.open(file2);
    if (!(file.peek() == EOF)) return file2;
    file.close();

    file.open(file3);
    if (!(file.peek() == EOF)) return file3;
    file.close();

    file.open(file4);
    if (!(file.peek() == EOF)) return file4;
    file.close();

}

int createAndSortFile(const char* fileName, const int numbersCount, const int maxNumberValue) {
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue))
        return -1;

    sort(fileName);

    const char* fileNameEnd = whatFileIsSorted("f1.txt", "f2.txt", "s1.txt", "s2.txt");
    std::cout << "File " << fileNameEnd << " is sorted" << std::endl;

    if (!isFileContainsSortedArray(fileNameEnd))
        return -2;

    return 1;
}

int main() {
    const char* fileName = "file.txt";
    const int numbersCount = 10;
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