#include <iostream>
#include <string>
using namespace std;

string to_binary(unsigned long n) { // переписал с Си
    string result;
    
    if (n == 0) {
        return "0"; // обработка 0
    }

    while (n > 0) {
        result = to_string(n % 2) + result; // младший бит в начале строки
        n /= 2;
    }
    return result;
}

void reverse(const string& binary) { // ф-ия перевернутая двоичная форма
    for (int i = binary.length() - 1; i >= 0; --i) {
        cout << binary[i]; // Выводим каждый бит в обратном порядке
    }
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
            string binary = to_binary(number); // Получаем двоичное представление
            cout << binary << endl; // Выводим на экран
            cout << "Число в двоичной форме (в обратном порядке): ";
            reverse(binary); // Вызываем функцию для вывода в обратном порядке
            cout << endl;
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
