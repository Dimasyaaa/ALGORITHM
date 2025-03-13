#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ф-ия для суммы итеративно
int iterativeSumOfDigits(const string& n) {
    
    int sum = 0;
    vector<int> digits; // слагаемые

    // проходим по всем символам строки, представляющей число
    for (char ch : n) {
        if (isdigit(ch)) { // проверка на цыфру
            int digit = ch - '0'; // преобразуем символ в цифру
            digits.push_back(digit); // сохр цифру для вывода
            sum += digit; // добавляем цифру к сумме
        }
    }

    // Итеративный метод
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

// ф-ция для суммы рекурсивно
int recursiveSumOfDigits(const string& n, size_t index) {
    // Базовый случай
    if (index >= n.size()) {
        return 0;
    }
    // рекурсия
    if (isdigit(n[index])) { // проверка на цифру
        int digit = n[index] - '0'; // преобразуем символ в цифру
        cout << digit; 
        if (index < n.size() - 1) {
            cout << " + "; // если это не последняя цифра, добавляем "+"
        }
        return digit + recursiveSumOfDigits(n, index + 1);
    }
    // если  не цифра, просто продолжаем рекурсию
    return recursiveSumOfDigits(n, index + 1);
}

int main() {
    setlocale(LC_ALL, "Rus");

    string number; // string чтоб не ломали int) и работать легче

    cout << "Введите целое положительное число (максимально допустимое число =  123456789123456789): " << endl;
    cin >> number;

    // Убираем знак "-" из числа, если он есть
    if (number[0] == '-') {
        number = number.substr(1); // Убираем первый символ
        cout << "Сумма числа без -: " << endl;
    }

    // cумма  итеративно
    int sumIterative = iterativeSumOfDigits(number);

    // cумма рекурсивно
    cout << "Слагаемые (рекурсивно): ";
    int sumRecursive = recursiveSumOfDigits(number, 0);
    cout << " = " << sumRecursive << endl;

    return 0;
}
