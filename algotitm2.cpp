#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream> // Для работы с файлами

using namespace std;

// Функция для нахождения максимального значения между двумя числами
int max(int a, int b) {
    return a > b ? a : b;
}

int main() {

    setlocale(LC_ALL, "Rus");

    int edges; // Количество рёбер
    cout << "Введите количество рёбер графа:" << endl;
    cin >> edges;

    // Вектор для хранения рёбер графа
    vector<vector<int>> listOfEdges(edges, vector<int>(2, 0));
    int node1, node2, vertices = 0; // Переменные для хранения узлов и количества вершин

    // Ввод рёбер
    cout << "Введите рёбра (node1 node2):" << endl;
    for (int i = 0; i < edges; i++) {
        cin >> node1 >> node2;
        // Обновляем количество вершин
        if (max(node1, node2) > vertices) vertices = max(node1, node2);
        listOfEdges[i][0] = node1;
        listOfEdges[i][1] = node2;
    }

    vertices++; // Увеличиваем количество вершин для корректной индексации
    // Создание матрицы смежности
    vector<vector<int>> matrix(vertices, vector<int>(vertices, 0));
    for (int i = 0; i < edges; i++) {
        matrix[listOfEdges[i][0]][listOfEdges[i][1]] = 1; // Устанавливаем связь между узлами
        matrix[listOfEdges[i][1]][listOfEdges[i][0]] = 1; // Для неориентированного графа
    }

    bool isolatedFlag; // Флаг для проверки изолированных вершин
    vector<int> isolated; // Список изолированных вершин
    vector<int> loops; // Список петель
    vector<int> degrees(vertices, 0); // Вектор для хранения степеней вершин

    // Анализ графа
    for (int i = 0; i < vertices; i++) {
        isolatedFlag = true; // Сбрасываем флаг изолированной вершины
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) { // Если есть связь
                if (i != j) isolatedFlag = false; // Условие для изолированной вершины
                if (i == j) {
                    loops.push_back(i); // Если вершина соединена сама с собой
                }
                degrees[i]++; // Увеличиваем степень вершины
            }
        }
        if (isolatedFlag) isolated.push_back(i); // Если вершина изолирована, добавляем в список
    }

    // Вывод результатов на экран
    cout << "\t\tРЕЗУЛЬТАТ" << endl;
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << "\t"; // Вывод матрицы смежности
        }
        cout << endl;
    }
    cout << "Количество вершин: " << vertices << endl;
    cout << "Количество рёбер: " << edges << endl;
    cout << "Количество изолированных вершин: " << isolated.size() << endl;
    if (!isolated.empty()) {
        cout << "Изолированные вершины: ";
        for (int i = 0; i < isolated.size(); i++) {
            cout << isolated[i] << "\t"; // Вывод изолированных вершин
        }
        cout << endl;
    }
    cout << "Количество петель: " << loops.size() << endl;
    if (!loops.empty()) {
        cout << "Петли находятся в вершинах: ";
        for (int i = 0; i < loops.size(); i++) {
            cout << loops[i] << "\t"; // Вывод петель
        }
        cout << endl;
    }

    // Сортировка степеней вершин в порядке убывания
    sort(degrees.begin(), degrees.end(), greater<int>());
    cout << "Степени вершин в порядке убывания:" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << degrees[i] << "\t"; // Вывод степеней вершин
    }
    cout << endl;

    // Запись выходных данных в файл
    ofstream outputFile("graph_output.txt", ios::app); // Открываем файл для записи
    outputFile << "\n\t\tРЕЗУЛЬТАТ" << endl;
    outputFile << "Матрица смежности:" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            outputFile << matrix[i][j] << "\t"; // Запись матрицы смежности в файл
        }
        outputFile << endl;
    }
    outputFile << "Количество вершин: " << vertices << endl;
    outputFile << "Количество рёбер: " << edges << endl;
    outputFile << "Количество изолированных вершин: " << isolated.size() << endl;
    if (!isolated.empty()) {
        outputFile << "Изолированные вершины: ";
        for (int i = 0; i < isolated.size(); i++) {
            outputFile << isolated[i] << "\t"; // Запись изолированных вершин в файл
        }
        outputFile << endl;
    }
    outputFile << "Количество петель: " << loops.size() << endl;
    if (!loops.empty()) {
        outputFile << "Петли находятся в вершинах: ";
        for (int i = 0; i < loops.size(); i++) {
            outputFile << loops[i] << "\t"; // Запись петель в файл
        }
        outputFile << endl;
    }

    outputFile << "Степени вершин в порядке убывания:" << endl;
    for (int i = 0; i < vertices; i++) {
        outputFile << degrees[i] << "\t"; // Запись степеней вершин в файл
    }
    outputFile.close(); 

    return 0;
}
