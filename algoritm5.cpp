#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>  
#include <iomanip>

using namespace std;

// фия для случайной последовательности
vector<int> generateRandomNumbers(int n) {
    vector<int> numbers(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100); // генератор

    for (int i = 0; i < n; ++i) {
        numbers[i] = dis(gen);
    }
    return numbers;
}

//  сортировка Шелла
int shellSort(vector<int>& arr, const vector<int>& steps, ofstream& outFile) {
    int totalSwaps = 0;

    for (int step : steps) {
        // сортировка с текущим шагом
        for (int i = step; i < arr.size(); i++) {
            int temp = arr[i];
            int j = i;

            while (j >= step && arr[j - step] > temp) {
                arr[j] = arr[j - step];
                j -= step;
                totalSwaps++;
            }
            arr[j] = temp;
        }

        // вывод промежутый
        cout << "После сортировки с шагом " << step << ": ";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;

        // вывод промежутый
        outFile << "После сортировки с шагом " << step << ": ";
        for (int num : arr) {
            outFile << num << " ";
        }
        outFile << endl;
    }

    return totalSwaps;
}

// фия для шагов
vector<int> generateSteps(int n, int formula) {
    vector<int> steps;
    int step;

    if (formula == 1) { // hi+1 = 3hi + 1
        step = 1;
        while (step < n) {
            steps.push_back(step);
            step = 3 * step + 1;
        }
    }
    else if (formula == 2) { // hi+1 = 2hi + 1
        step = 1;
        while (step < n) {
            steps.push_back(step);
            step = 2 * step + 1;
        }
    }
    else if (formula == 3) { // hi+1 = 2hi
        step = n / 2;
        while (step > 0) {
            steps.push_back(step);
            step /= 2;
        }
    }

    // обратить порядок для сортировки Шелла
    reverse(steps.begin(), steps.end());
    return steps;
}

int main() {
    setlocale(LC_ALL, "Rus");

    int n;
    cout << "Введите количество чисел в сортируемой последовательности: ";
    cin >> n;

    // Генерация случайной последовательности
    vector<int> numbers = generateRandomNumbers(n);
    cout << "Сгенерированная последовательность: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Открываем файл для записи
    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return 1;
    }

    // Запись сгенерированной последовательности в файл
    outFile << "Сгенерированная последовательность: ";
    for (int num : numbers) {
        outFile << num << " ";
    }
    outFile << endl;

    // Сортировка с шагом hi+1 = 3hi + 1
    vector<int> numbersCopy = numbers; // Копируем оригинальный массив
    vector<int> steps1 = generateSteps(n, 1);
    outFile << "Сортировка с шагом hi+1 = 3hi + 1:" << endl;
    cout << "Сортировка с шагом hi+1 = 3hi + 1:" << endl;
    int swaps1 = shellSort(numbersCopy, steps1, outFile);
    outFile << "Полностью отсортированная последовательность: ";
    for (int num : numbersCopy) {
        outFile << num << " ";
    }
    outFile << endl;
    outFile << "Количество перестановок: " << swaps1 << endl;

    // Сортировка с шагом hi+1 = 2hi + 1
    numbersCopy = numbers; // Копируем оригинальный массив
    vector<int> steps2 = generateSteps(n, 2);
    outFile << "Сортировка с шагом hi+1 = 2hi + 1:" << endl;
    cout << "Сортировка с шагом hi+1 = 2hi + 1:" << endl;
    int swaps2 = shellSort(numbersCopy, steps2, outFile);
    outFile << "Полностью отсортированная последовательность: ";
    for (int num : numbersCopy) {
        outFile << num << " ";
    }
    outFile << endl;
    outFile << "Количество перестановок: " << swaps2 << endl;

    // Сортировка с шагом hi+1 = 2hi
    numbersCopy = numbers; // Копируем оригинальный массив
    vector<int> steps3 = generateSteps(n, 3);
    outFile << "Сортировка с шагом hi+1 = 2hi:" << endl;
    cout << "Сортировка с шагом hi+1 = 2hi:" << endl;
    int swaps3 = shellSort(numbersCopy, steps3, outFile);
    outFile << "Полностью отсортированная последовательность: ";
    for (int num : numbersCopy) {
        outFile << num << " ";
    }
    outFile << endl;
    outFile << "Количество перестановок: " << swaps3 << endl;

    outFile.close();
    cout << "Результаты сохранены в файл output.txt" << endl;

    return 0;
}
