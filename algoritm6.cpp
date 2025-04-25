#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Ф-я  кучи
void heap(vector<int>& arr, int count, int i, int& swapCount) {

    int largest = i; // Инициализируем максимальный элемент как корень
    int left = 2 * i + 1; // левый потомок
    int right = 2 * i + 2; // правый потомок

    // Если левый дочерний элемент > корня
    if (left < count && arr[left] > arr[largest]) {
        largest = left;
    }

    // Если правый дочерний элемент > текущего макс
    if (right < count && arr[right] > arr[largest]) {
        largest = right;
    }

    // Если макс не корень
    if (largest != i) {
        swap(arr[i], arr[largest]); // Меняем местами
        swapCount++; // прибовляем счетчик

        // Рекурсивно приводим в порядок затронутое поддерево
        heap(arr, count, largest, swapCount);
    }
}

// ф-ия сортировки кучами
void heapSort(vector<int>& arr) {
    int count = arr.size();
    int totalSwaps = 0; // счетчик перестановок

    // Построение кучи (перегруппировка массива)
    for (int i = count / 2 - 1; i >= 0; i--) {
        heap(arr, count, i, totalSwaps);
    }

    // друг за другом извлекаем элементы из кучи
    for (int i = count - 1; i >= 0; i--) {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);
        totalSwaps++; // прибовляем счетчик

        // промежуточные резы
        cout << "Промежуточный результат (после перемещения элемента): ";
        for (int j = 0; j < count; j++) {
            cout << arr[j] << " ";
        }
        cout << "| Количество перестановок: " << totalSwaps << endl;

        // Вызываем heap на уменьшенной куче
        heap(arr, i, 0, totalSwaps);
    }
}

int main() {

    setlocale(LC_ALL, "Rus");

    int count; // Количество целых чисел 
    cout << "Введите количество целых чисел для сортировки: ";
    cin >> count;

    char choice;
    cout << "Хотите генерировать только положительные числа? (y/n): ";
    cin >> choice;

    // Генерация случайной последовательности
    vector<int> arr(count);
    srand(time(nullptr)); // генератор случайных чисел

    for (int i = 0; i < count; i++) {
        if (choice == 'y' || choice == 'Y') {
            arr[i] = std::rand() % 100; // Генерация случайных положительных чисел от 0 до 99
        }
        else {
            arr[i] = std::rand() % 199 - 99; // Генерация случайных чисел от -99 до 99
        }
    }

    // промежУТКА
    cout << "Сгенерированная последовательность: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Выполнение сортировки
    heapSort(arr);

    // ИТОГ
    cout << "Полностью отсортированная последовательность: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
