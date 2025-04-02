#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

// фия для сортировки чисел по LSD
void LSDRadixSort(vector<int>& arr, int k) {
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
        cout << "Промежуточная последовательность после сортировки по разряду " << i + 1 << ": ";
        for (int b = 0; b < 10; b++) {
            for (int num : buckets[b]) {
                cout << num << " ";
            }
        }
        cout << endl;

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
    cout << "Полностью отсортированная последовательность: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// фия для генерации случайной последовательности 
vector<int> generateRandomNumbers(int n, int k) {
    vector<int> numbers(n);
    mt19937 gen(random_device{}());
    uniform_int_distribution<> dis(0, pow(10, k) - 1);

    for (int i = 0; i < n; ++i) {
        numbers[i] = dis(gen);  // генерация случайных чисел
    }
    return numbers;
}

// фия для сортировки слов
void LSDRadixSortWords(vector<string>& arr, int k) {

    int n = arr.size();
    vector<vector<string>> buckets(26); // 26 букв английского алфавита

    for (int i = k - 1; i >= 0; i--) {
        // распределение по очередям на основании i-го символа
        for (int j = 0; j < n; j++) {
            char c = arr[j][i];
            buckets[c - 'a'].push_back(arr[j]);
        }
        // печать промежуточного вывода
        cout << "Промежуточная последовательность после сортировки по разряду " << i + 1 << ": ";
        for (int b = 0; b < 26; b++) {
            for (const auto& word : buckets[b]) {
                cout << word << " ";
            }
        }
        cout << endl;

        // слияние очередей
        arr.clear();
        for (int b = 0; b < 26; b++) {
            arr.insert(arr.end(), buckets[b].begin(), buckets[b].end());
            buckets[b].clear();
        }
    }

    // отсортированый вывод
    cout << "Полностью отсортированная последовательность: ";
    for (const auto& word : arr) {
        cout << word << " ";
    }
    cout << endl;
}

bool isValidWord(const string& word, int requiredLength) {
    return word.length() == requiredLength && all_of(word.begin(), word.end(), ::isalpha);
}

int main() {

    setlocale(LC_ALL, "Rus");

    int n, k;
    cout << "Введите количество чисел: ";
    cin >> n;
    cout << "Введите количество разрядов в числах: ";
    cin >> k;

    vector<int> numbers = generateRandomNumbers(n, k);
    cout << "Исходная последовательность чисел: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    LSDRadixSort(numbers, k);

    cout << "Введите количество слов: ";
    cin >> n;
    cout << "Введите количество букв в словах: ";
    cin >> k;

    vector<string> words(n);

    cout << "Введите слова (каждое слово должно состоять из " << k << " букв):" << endl;

    for (int i = 0; i < n; ++i) {
        while (true) {
            cin >> words[i];
            if (isValidWord(words[i], k)) {
                break; // если слово кайфовое, брейкаемся
            }
            else {
                cout << "Ошибка: слово должно состоять из " << k << " букв и не содержать цифр. Попробуйте еще раз:" << endl;
            }
        }
    }

    LSDRadixSortWords(words, k);

    return 0;
}
