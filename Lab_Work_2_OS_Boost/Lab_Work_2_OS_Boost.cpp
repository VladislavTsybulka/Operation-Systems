#include <iostream>
#include <vector>
#include <sstream>
#include <boost/thread.hpp>

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
            boost::this_thread::sleep(boost::posix_time::milliseconds(7)); // Sleep 7 ms
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
            boost::this_thread::sleep(boost::posix_time::milliseconds(12)); // Sleep 12 ms
        }

        double average = static_cast<double>(sum) / arr.size();
        std::cout << "Average: " << average << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }
}

int main() {
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
    boost::thread minMaxThread(boost::bind(&MinMaxFind, arr));
    minMaxThread.join();

    boost::thread averageThread(boost::bind(&AverageFind, arr));
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
