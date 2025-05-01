#include <iostream>
#include <vector>
#include <cstdlib> // рандом 
#include <ctime>   // рандом

using namespace std;

// глобалка для счета рекурсивных вызовов
int recursiveCallsCount = 0;

// ф-ия для слияния двух сортированных подмассивов
void merge(vector<int>& arr, int left, int mid, int right) {
    
    // размеры подмассивов
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // временные массивы
    vector<int> L(n1);
    vector<int> R(n2);

    // суем данные в временные массивы L и R
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // слияние временных массивов обратно в arr[left..right]
    
    int i = 0; // индекс 1 подмассива
    int j = 0; // индекс 2 подмассива
    int k = left; // индекс слияния

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // копируем оставшиеся элементы, если есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// СОРТИРОВКА СЛИЯНИЕМ
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // счетчик рекурсивных вызовов ++ :)
        recursiveCallsCount++;

        // середина
        int mid = left + (right - left) / 2;

        // рекурсивно сортируем две половины
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // сливаем сортированные половины
        merge(arr, left, mid, right);
    }
}

// Случайные числа
vector<int> generateRandomNumbers(int n, bool generateNegative) {
    vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        if (generateNegative) {
            numbers[i] = rand() % 100 - 50; // случайное число от -50 до 50
        }
        else {
            numbers[i] = rand() % 100; // случайное число от 0 до 99
        }
    }
    return numbers;
}

int main() {

    setlocale(LC_ALL, "Rus");

    srand(static_cast<unsigned int>(time(0))); // генератор случайных чисел

    int n;
    char choice;

    cout << "Введите количество чисел для сортировки: ";
    cin >> n;

    cout << "Выберите тип чисел (n - натуральные, d - отрицательные): ";
    cin >> choice;

    bool generateNegative = choice == 'd';

    // случайные числа
    vector<int> numbers = generateRandomNumbers(n, generateNegative);

    cout << "Сгенерированная последовательность: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // сама сортировка
    mergeSort(numbers, 0, n - 1);

    cout << "Отсортированная последовательность: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Количество рекурсивных вызовов: " << recursiveCallsCount << endl;

    return 0;
}
