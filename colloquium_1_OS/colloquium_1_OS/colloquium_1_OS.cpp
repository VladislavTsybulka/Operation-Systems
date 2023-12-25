#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;

unsigned long long factorial(unsigned int n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

vector<unsigned long long> getFactorials(unsigned int n) {

    vector<unsigned long long> factorials;
    for (unsigned int i = 0; i < n; i++) {
        try {
            factorials.push_back(factorial(i));
        }
        catch (const overflow_error& e) {
            cerr << "Ошибка: переполнение при вычислении факториала " << i << endl;
        }
    }
    return factorials;
}

void TestFact() {
    unsigned int n = 5;
    vector<unsigned long long> result = { 1, 1, 2, 6, 24 };
    vector<unsigned long long> expected_result = getFactorials(n);
    assert(result == expected_result);
    cout << "Testing Factorials is OK." << endl;
}
int main() {

    setlocale(LC_ALL, "Rus");
    TestFact();
    unsigned int n;
    cout << "Введите количество факториалов: ";
    cin >> n;

    vector<unsigned long long> factorials;
    try {
        factorials = getFactorials(n);
    }
    catch (const std::invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    cout << "Факториалы:";
    for (auto factorial : factorials)
        cout << " " << factorial;
    cout << endl;

    return 0;
}
