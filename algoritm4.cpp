#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>  // для работы с файлами
#include <sstream>  // для обработки строкового ввода
#include <cctype>   // для isalpha

using namespace std;

// функция для записи в файл
void writeToFile(ofstream& file, const string& message) {
    cout << message;      // вывод в консоль
    file << message;      // запись в файл
}

// функция для сортировки чисел по LSD
void LSDRadixSort(vector<int>& arr, int k, ofstream& outFile) {
    int n = arr.size();
    int exp = 1;

    // вектор для очередей по десятичным числам
    vector<vector<int>> buckets(10);

    for (int i = 0; i < k; i++) {
        // распределение по очередям
        for (int j = 0; j < n; j++) {
            int digit = (arr[j] / exp) % 10;
            buckets[digit].push_back(arr[j]);
        }

        // печать промежуточного вывода
        stringstream ss;
        ss << "Промежуточная последовательность после сортировки по разряду " << i + 1 << ": ";
        for (int b = 0; b < 10; b++) {
            for (int num : buckets[b]) {
                ss << num << " ";
            }
        }
        ss << endl;
        writeToFile(outFile, ss.str());

        // слияние очередей
        arr.clear();
        for (int b = 0; b < 10; b++) {
            arr.insert(arr.end(), buckets[b].begin(), buckets[b].end());
            buckets[b].clear();
        }

        // переход к следующему разряду
        exp *= 10;
    }

    // конечный отсортированный вывод
    stringstream ss;
    ss << "Полностью отсортированная последовательность: ";
    for (int num : arr) {
        ss << num << " ";
    }
    ss << endl;
    writeToFile(outFile, ss.str());
}

// функция для генерации случайной последовательности
vector<int> generateRandomNumbers(int n, int k) {
    vector<int> numbers(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, static_cast<int>(pow(10, k)) - 1);

    for (int i = 0; i < n; ++i) {
        numbers[i] = dis(gen);  // генерация случайных чисел
    }
    return numbers;
}

// функция для ввода чисел с клавиатуры
vector<int> inputNumbersManually(int n) {
    vector<int> numbers(n);
    cout << "Введите " << n << " чисел через пробел: ";
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    return numbers;
}

// функция для сортировки слов
void LSDRadixSortWords(vector<string>& arr, int k, ofstream& outFile) {
    int n = arr.size();
    vector<vector<string>> buckets(26); // 26 букв английского алфавита

    for (int i = k - 1; i >= 0; i--) {
        // распределение по очередям на основании i-го символа
        for (int j = 0; j < n; j++) {
            char c = tolower(arr[j][i]); // приводим к нижнему регистру
            buckets[c - 'a'].push_back(arr[j]);
        }

        // печать промежуточного вывода
        stringstream ss;
        ss << "Промежуточная последовательность после сортировки по разряду " << i + 1 << ": ";
        for (int b = 0; b < 26; b++) {
            for (const auto& word : buckets[b]) {
                ss << word << " ";
            }
        }
        ss << endl;
        writeToFile(outFile, ss.str());

        // слияние очередей
        arr.clear();
        for (int b = 0; b < 26; b++) {
            arr.insert(arr.end(), buckets[b].begin(), buckets[b].end());
            buckets[b].clear();
        }
    }

    // отсортированный вывод
    stringstream ss;
    ss << "Полностью отсортированная последовательность: ";
    for (const auto& word : arr) {
        ss << word << " ";
    }
    ss << endl;
    writeToFile(outFile, ss.str());
}

bool isValidWord(const string& word, int requiredLength) {
    if (word.length() != requiredLength) return false;
    for (char c : word) {
        if (!isalpha(c)) return false;
    }
    return true;
}


int main() {
    setlocale(LC_ALL, "Rus");

    // Открываем файл для записи
    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return 1;
    }

    int n, k, choice;
    cout << "Введите количество чисел: ";
    cin >> n;
    //writeToFile(outFile, "Введите количество чисел: " + to_string(n) + "\n");

    cout << "Введите количество разрядов в числах: ";
    cin >> k;
    //writeToFile(outFile, "Введите количество разрядов в числах: " + to_string(k) + "\n");

    cout << "Выберите способ заполнения чисел: " << endl;
    cout << "1) Вручную" << endl;
    cout << "2) Рандомными числами" << endl;
    //writeToFile(outFile, "Выберите способ заполнения чисел: \n1) Вручную\n2) Рандомными числами\n");

    cin >> choice;
    vector<int> numbers;

    if (choice == 2) {
        numbers = generateRandomNumbers(n, k);
        stringstream ss;
        ss << "Исходная последовательность чисел: ";
        for (int num : numbers) {
            ss << num << " ";
        }
        ss << endl;
        writeToFile(outFile, ss.str());

        LSDRadixSort(numbers, k, outFile);
    }
    else if (choice == 1) {
        numbers = inputNumbersManually(n);
        stringstream ss;
        ss << "Исходная последовательность чисел: ";
        for (int num : numbers) {
            ss << num << " ";
        }
        ss << endl;
        writeToFile(outFile, ss.str());

        //  максимальное количество разрядов
        int maxDigits = 0;
        for (int num : numbers) {
            int digits = to_string(abs(num)).length();
            if (digits > maxDigits) maxDigits = digits;
        }
        LSDRadixSort(numbers, maxDigits, outFile);
    }
    else {
        string errorMsg = "Некорректный выбор!\n";
        writeToFile(outFile, errorMsg);
        cout << errorMsg;
        return 1;
    }

    cout << "Введите количество слов: ";
    cin >> n;
    //writeToFile(outFile, "Введите количество слов: " + to_string(n) + "\n");

    cout << "Вводите только буквы английского алфавита, иначе будет выведена ошибка)" << endl;
    //writeToFile(outFile, "Вводите только буквы английского алфавита, иначе будет выведена ошибка)\n");

    cout << "Введите количество букв в словах: ";
    cin >> k;
    //writeToFile(outFile, "Введите количество букв в словах: " + to_string(k) + "\n");

    cin.ignore(); // очищаем буфер ввода

    vector<string> words(n);
    cout << "Введите слова (каждое слово должно состоять из " << k << " букв):" << endl;
    //writeToFile(outFile, "Введите слова (каждое слово должно состоять из " + to_string(k) + " букв):\n");

    for (int i = 0; i < n; ++i) {
        while (true) {
            cin >> words[i];
            // Приводим слово к нижнему регистру
            transform(words[i].begin(), words[i].end(), words[i].begin(), ::tolower);
            if (isValidWord(words[i], k)) {
                break; // если слово корректное, выходим из цикла
            }
            else {
                string errorMsg = "Ошибка: слово должно состоять из " + to_string(k) +
                                " букв и не содержать цифр. А также состоять только из букв английского алфавита. Попробуйте еще раз:\n";
                writeToFile(outFile, errorMsg);
                cout << errorMsg;
            }
        }
    }

    LSDRadixSortWords(words, k, outFile);
    outFile.close();

    cout << "Результаты сохранены в файл output.txt" << endl;

    return 0;
}
