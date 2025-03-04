#include <iostream>
#include <vector>
#include <string> // Для работы со строками
using namespace std;

// фия для вычисления суммы итеративно
int iterativeSumOfDigits(const string& n) {
    int sum = 0;
    vector<int> digits; // слагаемые

    // проходим по всем символам строки, представляющей число
    for (char ch : n) {
        int digit = ch - '0'; // преобразуем символ в цифру
        digits.push_back(digit); // сохраняем цифру для вывода
        sum += digit; // добавляем цифру к сумме
    }

    // итеративный метод
    cout << "Слагаемые (итеративно): ";
    for (size_t i = 0; i < digits.size(); ++i) {
        cout << digits[i];
        if (i < digits.size() - 1) {
            cout << " + ";
        }
    }
    cout << " = " << sum << endl; // итоговая сумма

    return sum;
}

// фия для вычисления суммы рекурсивно
int recursiveSumOfDigits(const string& n, size_t index) {
    // Базовый случай
    if (index >= n.size()) {
        return 0;
    }
    // Рекурсия
    int digit = n[index] - '0'; // преобразуем символ в цифру
    cout << digit; // вводим текущую цифру
    if (index < n.size() - 1) {
        cout << " + "; // если это не последняя цифра, добавляем "+"
    }
    return digit + recursiveSumOfDigits(n, index + 1);
}

int main() {
    setlocale(LC_ALL, "Rus");

    string number; // используем string для хранения большого числа

    cout << "Введите целое число (максимально допустимое число =  123456789123456789): " << endl;
    cin >> number;

    // сумма цифр итеративно
    int sumIterative = iterativeSumOfDigits(number);

    // сумма цифр рекурсивно
    cout << "Слагаемые (рекурсивно): ";
    int sumRecursive = recursiveSumOfDigits(number, 0);
    cout << " = " << sumRecursive << endl;

    return 0;
}
