#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция для генерации случайной последовательности целых чисел
vector<int> generateRandomSequence(int n, int minValue, int maxValue) {
    vector<int> sequence(n);
    for (int i = 0; i < n; ++i) {
        sequence[i] = minValue + rand() % (maxValue - minValue + 1);
    }
    return sequence;
}

// фия быстрой сортировки
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // выбираем последний элемент в качестве опорного
    int i = low - 1; // индекс меньшего элемента
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++; // + индекс меньшего элемента
            swap(arr[i], arr[j]); // перекидываем
        }
    }
    swap(arr[i + 1], arr[high]); // ставим опорный элемент на правильную позицию
    return i + 1; // индекс опорного элемента
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // индекс опорного элемента
        // рекурсией сортируем элементы до и после опорного
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);

        // промежуточные резы после каждой итерации
        cout << "Промежуточный результат: ";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {

    setlocale(LC_ALL, "Rus");

    // генератор СЧ
    srand(static_cast<unsigned int>(time(0)));

    // ввод количества чисел в последовательности
    int n;
    cout << "Введите количество чисел в сортируемой последовательности(от -50 до 50): ";
    cin >> n;

    // генерация случайной последовательности
    vector<int> sequence = generateRandomSequence(n, -50, 50); // от -50 до 50

    // исходная последовательностЬ
    cout << "Исходная последовательность: ";
    for (int num : sequence) {
        cout << num << " ";
    }
    cout << endl;

    // сортировка
    quickSort(sequence, 0, sequence.size() - 1);

    // отсортированная последовательность
    cout << "Полностью отсортированная последовательность: ";
    for (int num : sequence) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
