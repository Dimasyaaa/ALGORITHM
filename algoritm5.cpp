#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <iomanip>

using namespace std;

// Функция для генерации случайной последовательности чисел с возможностью включения отрицательных значений
vector<int> generateRandomNumbers(int count) {
    vector<int> numbers(count);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-10000, 10000); // Генератор чисел от -100 до 100 УЖЕ БОЛЬШЕ И С ОТРИЦАТЕЛЬНЫМИ :))))

    for (int i = 0; i < count; ++i) {
        numbers[i] = dis(gen); 
    }
    return numbers;
}

// Функция для сортировки массива методом Шелла
// Возвращает общее количество перестановок, сделанных во время сортировки
int shellSort(vector<int>& arr, const vector<int>& steps, ofstream& outFile) {
    int totalSwaps = 0; //общее количество перестановок

    // ПроходКА  ПО каждому шагу сортировки
    for (int step : steps) {
        // Сортировка с текущим шагом
        for (int i = step; i < arr.size(); i++) {
            int temp = arr[i]; // текущее значение для сравнения !!!!!
            int j = i;

            // Сравниваем элементы и сдвигаем их для вставки
            while (j >= step && arr[j - step] > temp) {
                arr[j] = arr[j - step]; // Перемещаем элемент
                j -= step; // Переходим на шаг назад
                totalSwaps++; // добавлеям счетчик
            }
            arr[j] = temp; // вставляем сохраненое значение в нужное место
        }

        // промежуточный результат 
        cout << "После сортировки с шагом " << step << ": ";
        for (int num : arr) {
            cout << num << " "; 
        }
        cout << endl;

        // промежуточные резы в файлик
        outFile << "После сортировки с шагом " << step << ": ";
        for (int num : arr) {
            outFile << num << " "; 
        }
        outFile << endl;
    }

    return totalSwaps; 
}

// Ф-ия для генерации шагов для сортировки Шелла
vector<int> generateSteps(int count, int formula) {
    vector<int> steps; // Вектор для хранения шагов
    int step;

    if (formula == 1) { // Формула hi+1 = 3hi + 1
        step = 1;
        while (step < count) {
            steps.push_back(step); // Добавляем шаг в вектор
            step = 3 * step + 1; // следующий шаг
        }
    }
    else if (formula == 2) { // Формула hi+1 = 2hi + 1
        step = 1;
        while (step < count) {
            steps.push_back(step); // Добавляем шаг в вектор
            step = 2 * step + 1; // следующий шаг
        }
    }
    else if (formula == 3) { // Формула hi+1 = 2hi
        step = count / 2;
        while (step > 0) {
            steps.push_back(step); // Добавляем шаг в вектор
            step /= 2; // делим шаг на 2 для следующего
        }
    }

    // Обращаем порядок шагов для сортировки Шелла
    reverse(steps.begin(), steps.end());
    return steps; 
}

int main() {
    setlocale(LC_ALL, "Rus"); // русская мова

    int count; //  количествo чисел
    cout << "Введите количество чисел в сортируемой последовательности: ";
    cin >> count;

    // Генерация случайной последовательности
    vector<int> numbers = generateRandomNumbers(count);
    cout << "Сгенерированная последовательность: ";
    for (int num : numbers) {
        cout << num << " "; 
    }
    cout << endl;

    // Запись в файл
    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return 1; 
    }

    // сгенерированая последовательность с записькой в файл
    outFile << "Сгенерированная последовательность: ";
    for (int num : numbers) {
        outFile << num << " "; 
    }
    outFile << endl;

    // Сортировка с шагом hi+1 = 3hi + 1
    vector<int> numbersCopy = numbers; // Копируем ориги
    vector<int> steps1 = generateSteps(count, 1); // Генерируем шаги
    outFile << "Сортировка с шагом hi+1 = 3hi + 1:" << endl;
    cout << "Сортировка с шагом hi+1 = 3hi + 1:" << endl;

    int swaps1 = shellSort(numbersCopy, steps1, outFile); 
    outFile << "Полностью отсортированная последовательность: ";
    for (int num : numbersCopy) {
        outFile << num << " "; 
    }
    outFile << endl;
    outFile << "Количество перестановок: " << swaps1 << endl; 
    cout << "Количество перестановок: " << swaps1 << endl; 

    // Сортировка с шагом hi+1 = 2hi + 1
    numbersCopy = numbers; // Копируем оригу
    vector<int> steps2 = generateSteps(count, 2); // Генерируем шаги
    outFile << "Сортировка с шагом hi+1 = 2hi + 1:" << endl;
    cout << "Сортировка с шагом hi+1 = 2hi + 1:" << endl;

    int swaps2 = shellSort(numbersCopy, steps2, outFile); 
    outFile << "Полностью отсортированная последовательность: ";
    for (int num : numbersCopy) {
        outFile << num << " "; 
    }
    outFile << endl;
    outFile << "Количество перестановок: " << swaps2 << endl;
    cout << "Количество перестановок: " << swaps2 << endl; 

    // Сортировка с шагом hi+1 = 2hi
    numbersCopy = numbers; // Копируем оригу
    vector<int> steps3 = generateSteps(count, 3); // Генерируем шаги
    outFile << "Сортировка с шагом hi+1 = 2hi:" << endl;
    cout << "Сортировка с шагом hi+1 = 2hi:" << endl;

    int swaps3 = shellSort(numbersCopy, steps3, outFile); 
    outFile << "Полностью отсортированная последовательность: ";
    for (int num : numbersCopy) {
        outFile << num << " "; 
    }
    outFile << endl;
    outFile << "Количество перестановок: " << swaps3 << endl; 
    cout << "Количество перестановок: " << swaps3 << endl; 

    outFile.close(); // Закрываем файл
    cout << "Результаты сохранены в файл output.txt" << endl; 

    return 0; 
}
