#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cassert>

using namespace std;

template<typename T>
vector<T> removeDuplicates(const vector<T>& input) {
    unordered_set<T> uniqueElements;
    vector<T> result;

    for (const auto& element : input) {
        if (uniqueElements.insert(element).second) {
            result.push_back(element);
        }
    }

    return result;
}

template<typename T>
void printContainer(const vector<T>& container) {
    for (const auto& element : container) {
        cout << element << " ";
    }
    cout << endl;
}

void TestRemover() {

    vector<int> input = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 4 };
    vector<int> output = { 1, 2, 3, 4 };
    vector<int> expected_output = removeDuplicates(input);
    assert(output == expected_output);
    cout << "Testing Remover is OK." << endl;
}
int main() {

    TestRemover();
    vector<int> input = { 1, 2, 3, 4, 2, 3, 5 };

    vector<int> output = removeDuplicates(input);

    cout << "Input: ";
    printContainer(input);
    cout << "Output: ";
    printContainer(output);

    return 0;
}
