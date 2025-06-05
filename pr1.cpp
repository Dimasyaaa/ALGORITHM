#include <iostream>
#include <queue> // очереди в ++
#include <vector>
#include <string>// для stoi

using namespace std;

// фия для объединения двух очередей с уникальными элементами
void mergeUnique(queue<int>& q1, queue<int>& q2, queue<int>& q3) {
    while (!q1.empty() && !q2.empty()) {
        if (q1.front() < q2.front()) {
            q3.push(q1.front());
            q1.pop();
        }
        else if (q1.front() > q2.front()) {
            q3.push(q2.front());
            q2.pop();
        }
        else {
            // если элементы равны добавляем только один из них
            q3.push(q1.front());
            q1.pop();
            q2.pop();
        }
    }

    // если остались элементы в q1
    while (!q1.empty()) {
        q3.push(q1.front());
        q1.pop();
    }

    // усли остались элементы в q2
    while (!q2.empty()) {
        q3.push(q2.front());
        q2.pop();
    }
}

// фия для объединения двух очередей с возможными дубликатами
void mergeWithDuplicates(queue<int>& q1, queue<int>& q2, queue<int>& q3) {
    while (!q1.empty() && !q2.empty()) {
        if (q1.front() < q2.front()) {
            q3.push(q1.front());
            q1.pop();
        }
        else if (q1.front() > q2.front()) {
            q3.push(q2.front());
            q2.pop();
        }
        else {
            // если элементы равны добавляем оба
            q3.push(q1.front());
            q3.push(q2.front());
            q1.pop();
            q2.pop();
        }
    }

    // если остались элементы в q1
    while (!q1.empty()) {
        q3.push(q1.front());
        q1.pop();
    }

    // если остались элементы в q2
    while (!q2.empty()) {
        q3.push(q2.front());
        q2.pop();
    }
}

// фия для вывода очереди
void printQueue(queue<int> q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {

    setlocale(LC_ALL, "Rus");

    queue<int> q1, q2, q3_unique, q3_duplicates;
    vector<int> elements;

    // ввод 1 множества
    cout << "Введите УПОРЯДОЧЕННЫЙ список элементов 1 множества (для выхода нажми 'e'):\n";
    while (true) {
        string input;
        cin >> input;
        if (input == "e") break;
        elements.push_back(stoi(input));
    }

    // заполнение первой очереди
    for (int elem : elements) {
        q1.push(elem);
    }

    // очистка вектора для ввода второго множества
    elements.clear();

    // ввод 2 множества
    cout << "Введите УПОРЯДОЧЕННЫЙ список элементов 2 множества (для выхода нажми 'e'):\n";
    while (true) {
        string input;
        cin >> input;
        if (input == "e") break;
        elements.push_back(stoi(input));
    }

    // заполнение второй очереди
    for (int elem : elements) {
        q2.push(elem);
    }

    // объединение с уникальными элементами
    mergeUnique(q1, q2, q3_unique);

    // вывод резов
    cout << "\nРезультат объединения без дубликатов (Q3): ";
    printQueue(q3_unique);

    // восстановление очередей для объединения с дубликатами
    for (int elem : elements) {
        q2.push(elem);
    }
    q1 = queue<int>(); // сброс первой очереди
    for (int elem : elements) {
        q1.push(elem);
    }

    // объединение с дубликатами
    mergeWithDuplicates(q1, q2, q3_duplicates);

    // вывод резов с дубликатами
    cout << "Результат объединения с дубликатами (Q3): ";
    printQueue(q3_duplicates);

    return 0;
}
