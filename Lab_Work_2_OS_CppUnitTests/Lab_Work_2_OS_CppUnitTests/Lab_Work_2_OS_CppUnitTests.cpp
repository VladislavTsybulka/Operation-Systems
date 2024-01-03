#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include <windows.h>

// Function of thread minMaxThread
void MinMaxFind(const std::vector<int>& arr) {
    try {
        if (arr.empty()) {
            throw std::runtime_error("Array is empty");
        }

        int minValue = arr[0];
        int maxValue = arr[0];

        for (const auto& num : arr) {
            if (num < minValue) {
                minValue = num;
            }
            if (num > maxValue) {
                maxValue = num;
            }
            Sleep(7); // Sleep 7 ms
        }

        std::cout << "Min value: " << minValue << std::endl;
        std::cout << "Max value: " << maxValue << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }
}

// Function of thread averageThread
void AverageFind(const std::vector<int>& arr) {
    try {
        if (arr.empty()) {
            throw std::runtime_error("Array is empty");
        }

        int sum = 0;
        for (const auto& num : arr) {
            sum += num;
            Sleep(12); // Sleep 12 ms
        }

        double average = static_cast<double>(sum) / arr.size();
        std::cout << "Average: " << average << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }
}

// Функция для получения вывода из cout
std::string getOutputFromCout(std::ostream& stream) {
    std::stringstream ss;
    ss << stream.rdbuf();
    return ss.str();
}

int main() {

    // Entering the size and elements of the array
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Invalid array size. Please enter a positive value." << std::endl;
        return 1;
    }

    std::vector<int> arr(size);
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    // Creating of threads minMaxThread and averageThread
    std::thread minMaxThread([&arr]() { MinMaxFind(arr); });
    minMaxThread.join();

    std::thread averageThread([&arr]() { AverageFind(arr); });
    averageThread.join();

    int minValue = arr[0];
    int maxValue = arr[0];
    int sum = 0;
    for (const auto& num : arr) {
        if (num < minValue) {
            minValue = num;
        }
        if (num > maxValue) {
            maxValue = num;
        }
        sum += num;
    }
    double average = static_cast<double>(sum) / arr.size();

    for (auto& num : arr) {
        if (num == minValue || num == maxValue) {
            num = average;
        }
    }

    // Results
    std::cout << "Modified array: ";
    for (const auto& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
