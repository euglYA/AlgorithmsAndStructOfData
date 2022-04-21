#include <iostream>
#include <fstream>
#include <stdio.h>
#include <random>

bool createFileWithRandomNumbers(const char* fileName, const int numbersCount, const int maxNumberValue) {
	std::ofstream file(fileName);

	if (!file.is_open()) {
		std::cout << "cant open file" << std::endl;
		return false;
	}

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, maxNumberValue);
	generator.seed(time(0));

	for (int i = 0; i < numbersCount; i++)
		file << distribution(generator) << " ";

	file.close();
	return true;
}

bool isFileContainsSortedArray(const char* fileName) {
	std::ifstream file(fileName);

	int number1, number2;
	file >> number1;

	while (file >> number2) {
		if (number2 < number1)
			return false;
		
		number1 = number2;
	}

	return true;
}