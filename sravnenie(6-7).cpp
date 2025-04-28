#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream> // записька в файл

using namespace std;

// Обмен двух элементов
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Функция для разделения массива для быстрой сортировки
int partition(int arr[], int low, int high, int& swapCount) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swapCount++;
        }
    }
    swap(arr[i + 1], arr[high]);
    swapCount++;
    return i + 1;
}

// БЫСТРАЯ СОРТИРОВКА
void quickSort(int arr[], int low, int high, int& swapCount) {
    if (low < high) {
        int pi = partition(arr, low, high, swapCount);

        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

// кучка
void heapify(vector<int>& arr, int n, int i, int& swapCount) {
    int largest = i; // Инициализируем наибольший как корень
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        swapCount++;

        heapify(arr, n, largest, swapCount);
    }
}

// СОРТИРОВКА КУЧЕЙ
void heapSort(vector<int>& arr, int& swapCount) {
    int n = arr.size();

    // Построение кучи
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, swapCount);

    // Извлечение элементов из кучи
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        swapCount++;
        heapify(arr, i, 0, swapCount);
    }
}

int main() {

    setlocale(LC_ALL, "Rus");

    srand(static_cast<unsigned>(time(0)));

    int count;
    cout << "Введите количество целых чисел: ";
    cin >> count;

    if (count <= 0) {
        cout << "Ошибка: количество должно быть положительным." << endl;
        return 1;
    }

    char choice;
    cout << "Хотите генерировать только положительные числа? (y/n): ";
    cin >> choice;

    vector<int> originalArr(count);

    for (int i = 0; i < count; i++) {
        if (choice == 'y' || choice == 'Y') {
            originalArr[i] = rand() % 100; // 0-99
        }
        else {
            originalArr[i] = rand() % 199 - 99; // -99 до 99
        }
    }

    cout << "Сгенерированный массив: ";
    for (int num : originalArr) {
        cout << num << " ";
    }
    cout << endl;

    // Создаем копии для каждой сортировки
    int* arrQuick = new int[count];
    vector<int> arrHeap = originalArr;

    for (int i = 0; i < count; i++) {
        arrQuick[i] = originalArr[i];
    }

    int swapCountQuick = 0;
    int swapCountHeap = 0;

    // Быстрая сортировка
    quickSort(arrQuick, 0, count - 1, swapCountQuick);

    // Сортировка кучей
    heapSort(arrHeap, swapCountHeap);

    // резы
    cout << "\nРезультаты сортировки:" << endl;
    cout << "Быстрая сортировка: " << swapCountQuick << " перестановок." << endl;
    cout << "Сортировка кучей: " << swapCountHeap << " перестановок." << endl;

    // файлик
    ofstream outFile("sravnenie.txt");
    if (outFile.is_open()) {
        outFile << "Сравнение количества перестановок:\n";
        outFile << "Быстрая сортировка: " << swapCountQuick << " перестановок.\n";
        outFile << "Сортировка кучей: " << swapCountHeap << " перестановок.\n";
        outFile.close();
        cout << "Результаты записаны в файл sravnenie.txt" << endl;
    } else {
        cout << "Ошибка открытия файла для записи." << endl;
    }

    delete[] arrQuick;

    return 0;
}
