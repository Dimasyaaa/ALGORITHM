#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// фия для генерации случайной последовательности целых чисел
vector<int> generateRandomSequence(int n, int minValue, int maxValue) {
    vector<int> sequence(n);
    for (int i = 0; i < n; ++i) {
        sequence[i] = minValue + rand() % (maxValue - minValue + 1);
    }
    return sequence;
}

// сортировка Шелла с заданной последовательностью шагов
void shellSort(vector<int>& arr, const vector<int>& increments) {
    for (int gap : increments) {
        // сортировка вставками для каждого шага
        for (int i = gap; i < arr.size(); ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
        // промежуточные резы после сортировки с текущим шагом
        cout << "После сортировки с шагом " << gap << ": ";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {

    setlocale(LC_ALL, "Rus");

    // генерим случайные числа
    srand(static_cast<unsigned int>(time(0)));

    // Ввод количества чисел в последовательности
    int n;
    cout << "Введите количество чисел в сортируемой последовательности: ";
    cin >> n;

    // рандом последовательность
    vector<int> sequence = generateRandomSequence(n, 0, 100); // от 0 до 100

    // исходная последовательность
    cout << "Исходная последовательность: ";
    for (int num : sequence) {
        cout << num << " ";
    }
    cout << endl;

    // копирую исходную последовательность для сортировки с разными шагами
    vector<int> sequence1 = sequence; // Для h_i+1 = 3h_i + 1
    vector<int> sequence2 = sequence; // Для h_i+1 = 2h_i + 1
    vector<int> sequence3 = sequence; // Для h_i+1 = 2h_i

    //  последовательности шагов
    vector<int> increments1 = { 364, 121, 40, 13, 4, 1 }; // 3h + 1
    vector<int> increments2 = { 255, 127, 63, 31, 15, 7, 3, 1 }; // 2h + 1
    vector<int> increments3 = { 128, 64, 32, 16, 8, 4, 2, 1 }; // 2h

    // cортировка с 1 последовательностью шагов
    cout << "Сортировка с шагами h_i+1 = 3h_i + 1:" << endl;
    shellSort(sequence1, increments1);

    // с 2 последовательностью шагов
    cout << "Сортировка с шагами h_i+1 = 2h_i + 1:" << endl;
    shellSort(sequence2, increments2);

    // c 3 последовательностью шагов
    cout << "Сортировка с шагами h_i+1 = 2h_i:" << endl;
    shellSort(sequence3, increments3);

    //отсортированная последовательность
    cout << "Полностью отсортированная последовательность (для всех шагов): ";
    sort(sequence.begin(), sequence.end());
    for (int num : sequence) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
