#include <iostream>
#include <vector>

using namespace std;

int iterativeSumOfDigits(int n) {
    int sum = 0;
    vector<int> digits; // слагаемые

    n = abs(n); // абсолютное значение

    // извлекаем цифры итеративно
    while (n > 0) {
        int digit = n % 10; // последняя цифра
        digits.push_back(digit); // сохр цифру для вывода
        sum += digit; //  цифра + сумме
        n /= 10; // убкраем последнюю
    }

    // итеративный метод
    cout << "Слагаемые (итеративно): ";
    for (size_t i = 0; i < digits.size(); ++i) {
        cout << digits[i];
        if (i < digits.size() - 1) {
            cout << " + ";
        }
    }
    cout << " = " << sum << endl; //  итоговая сумма

    return sum;
}

int recursiveSumOfDigits(int n) {
    if (n < 0) {
        n = -n; // приводим к абсолютному
    }

    // обычный случая
    if (n == 0) {
        return 0;
    }
    else {
        // рекурсия
        int digit = n % 10;
        cout << digit; // вводим текущую цифру
        if (n >= 10) {
            cout << " + "; // если это не последняя цифра, добавляем +
        }
        return digit + recursiveSumOfDigits(n / 10);
    }
}

int main() {

    setlocale(LC_ALL, "Rus");

    int number;

    cout << "Введите целое число: ";
    cin >> number;

    // абсолютное значение
    int absNumber = abs(number);

    // сумма цифр итеративно
    int sumIterative = iterativeSumOfDigits(absNumber);

    // сумма цифр рекурсивно
    cout << "Слагаемые (рекурсивно): ";
    int sumRecursive = recursiveSumOfDigits(absNumber);
    cout << " = " << sumRecursive << endl;

    return 0;
}
