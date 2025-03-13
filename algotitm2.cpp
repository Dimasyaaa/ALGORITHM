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

    // информация о нумерации вершин
    cout << "Внимание: нумерация вершин начинается с 0." << endl;
    cout << "Изолированная вершина — это вершина, не имеющая рёбер, то есть не соединенная ни с одной другой вершиной." << endl;
    cout << "Чтобы создать изолированную вершину, необходимо не указывать её в списке рёбер." << endl;

    int edges; // количество рёбер
    cout << "Введите количество рёбер графа:" << endl;
    cin >> edges;

    // Вектор для хранения рёбер графа
    vector<vector<int>> listOfEdges(edges, vector<int>(2, 0));
    int node1, node2, vertices = 0; // узлы и количество вершин

    // Ввод рёбер
    cout << "Введите рёбра (node1 node2):" << endl;
    for (int i = 0; i < edges; i++) {
        cin >> node1 >> node2;
        // обновляем количество вершин
        if (max(node1, node2) > vertices) vertices = max(node1, node2);
        listOfEdges[i][0] = node1;
        listOfEdges[i][1] = node2;
    }

    vertices++; // увеличиваем количество вершин для корректной индексации
    // создание матрицы смежности
    vector<vector<int>> matrix(vertices, vector<int>(vertices, 0));
    for (int i = 0; i < edges; i++) {
        matrix[listOfEdges[i][0]][listOfEdges[i][1]] = 1; // устанавливаем связь между узлами
        matrix[listOfEdges[i][1]][listOfEdges[i][0]] = 1; // для неориентированного графа
    }

    bool isolatedFlag; // флаг для изолированных вершин
    vector<int> isolated; // список изолированных вершин
    vector<int> loops; // список петель
    vector<int> degrees(vertices, 0); // вектор для хранения степеней вершин

    // анализ графа
    for (int i = 0; i < vertices; i++) {
        isolatedFlag = true;
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) { // если есть связь
                if (i != j) isolatedFlag = false; // изолированная вершина
                if (i == j) {
                    loops.push_back(i); // если соединена сама с собой
                }
                degrees[i]++; // увеличиваем степень вершины
            }
        }
        if (isolatedFlag) isolated.push_back(i); // если изолирована, добавляем в список
    }

    // вывод результатов
    cout << "\t\tРЕЗУЛЬТАТ" << endl;
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Количество вершин: " << vertices << endl;
    cout << "Количество рёбер: " << edges << endl;
    cout << "Количество изолированных вершин: " << isolated.size() << endl;
    if (!isolated.empty()) {
        cout << "Изолированные вершины: ";
        for (int i = 0; i < isolated.size(); i++) {
            cout << isolated[i] << "\t";
        }
        cout << endl;
    }
    cout << "Количество петель: " << loops.size() << endl;
    if (!loops.empty()) {
        cout << "Петли находятся в вершинах(счет с 0): ";
        for (int i = 0; i < loops.size(); i++) {
            cout << loops[i] << "\t";
        }
        cout << endl;
    }

    // сортировка степеней вершин в порядке убывания
    sort(degrees.begin(), degrees.end(), greater<int>());
    cout << "Степени вершин в порядке убывания:" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << degrees[i] << "\t";
    }
    cout << endl;

    // запись данных в файл
    ofstream outputFile("graph.txt", ios::app);
    outputFile << "\n\t\tРЕЗУЛЬТАТ" << endl;
    outputFile << "Матрица смежности:" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            outputFile << matrix[i][j] << "\t";
        }
        outputFile << endl;
    }
    outputFile << "Количество вершин: " << vertices << endl;
    outputFile << "Количество рёбер: " << edges << endl;
    outputFile << "Количество изолированных вершин: " << isolated.size() << endl;
    if (!isolated.empty()) {
        outputFile << "Изолированные вершины: ";
        for (int i = 0; i < isolated.size(); i++) {
            outputFile << isolated[i] << "\t";
        }
        outputFile << endl;
    }
    outputFile << "Количество петель: " << loops.size() << endl;
    if (!loops.empty()) {
        outputFile << "Петли находятся в вершинах(счет с 0): ";
        for (int i = 0; i < loops.size(); i++) {
            outputFile << loops[i] << "\t";
        }
        outputFile << endl;
    }
    outputFile << "Степени вершин в порядке убывания:" << endl;
    for (int i = 0; i < vertices; i++) {
        outputFile << degrees[i] << "\t";
    }
    outputFile.close();

    return 0;
}
