#include <iostream>
#include <cstdlib> 
#include <ctime>   // рандом

using namespace std;

// обмен двух элементов
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Функция для разделения массива на две части
int partition(int arr[], int low, int high, int& swapCount) {
    // Выбор последнего элемента в качестве опорного
    int pivot = arr[high];
    int i = low - 1;

    // Перемещение элементов меньше опорного влево от опорного
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swapCount++; // плюсуем счетчик 
        }
    }
    // Помещение опорного элемента на его правильное место
    swap(arr[i + 1], arr[high]);
    swapCount++; // плюсуем счетчик
    return i + 1;
}

// Функция быстрой сортировки
void quickSort(int arr[], int low, int high, int& swapCount) {
    if (low < high) {
        // Разделение массива и получение индекса опорного элемента
        int pi = partition(arr, low, high, swapCount);

        // Промежуточный результат 
        cout << "Промежуточный результат сортировки: ";
        for (int k = 0; k <= high; k++) {
            cout << arr[k] << " ";
        }
        cout << "| Количество перестановок: " << swapCount << endl;

        // Рекурсивная сортировка
        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

int main() {

    setlocale(LC_ALL, "Rus");

    // Генератор случайных чисел
    srand(static_cast<unsigned>(time(0)));

    int count;
    cout << "Введите количество целых чисел для генерации: ";
    cin >> count;

    // Проверка правильности ввода числа
    if (count <= 0) {
        cout << "Ошибка: количество целых чисел должно быть положительным." << endl;
        return 1; 
    }

    char choice;
    cout << "Хотите генерировать только положительные числа? (y/n): ";
    cin >> choice;

    // Динамическое выделение памяти 
    int* arr = new int[count];

    // Генерация случайных чисел и заполнение массива
    for (int i = 0; i < count; i++) {
        if (choice == 'y' || choice == 'Y') {
            arr[i] = rand() % 100; // Генерация чисел от 0 до 99
        }
        else {
            arr[i] = rand() % 199 - 99; // Генерация чисел от -99 до 99
        }
    }

    cout << "Сгенерированные числа: ";
    for (int i = 0; i < count; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int totalSwaps = 0; // Счетчик перестановок

    // Вызов функции быстрой сортировки
    quickSort(arr, 0, count - 1, totalSwaps);

    //  отсортированный массив
    cout << "Отсортированные числа: ";
    for (int i = 0; i < count; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // количество перестановок
    cout << "Общее количество перестановок: " << totalSwaps << endl;

    // Очистка выделенной памяти, надеюсь похвалите)
    delete[] arr;

    return 0;
}
