#include <iostream>
#include <string>

using namespace std;

void to_binary(unsigned long n) {
    if (n >= 2) {
        to_binary(n / 2);
    }
    cout << (n % 2); // Выводим младший бит
}

int main() {

    setlocale(LC_ALL, "Rus");

    unsigned long number;

    while (true) {
        cout << "Введите целое число (9-15) или Q для завершения: ";
        string input;
        cin >> input;

        if (input == "Q") {
            cout << "Программа завершена!" << endl;
            break;
        }

        try {
            number = stoul(input);
            if (number < 9 || number > 15) {
                cout << "Пожалуйста, введите число в диапазоне от 9 до 15." << endl;
                continue;
            }
            cout << "Число в двоичной форме: ";
            to_binary(number);
            cout << endl; // Для разделения выводов
        }
        catch (invalid_argument&) {
            cout << "Некорректный ввод. Пожалуйста, введите целое число или Q для завершения." << endl;
        }
        catch (out_of_range&) {
            cout << "Число слишком велико." << endl;
        }
    }

    return 0;
}
