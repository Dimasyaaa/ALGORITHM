#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream> 

using namespace std;

// Функция для нахождения максимального значения между двумя числами
int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    setlocale(LC_ALL, "Rus");

    // Информация о нумерации вершин
    cout << "Внимание: нумерация вершин начинается с 0." << endl;
    cout << "Изолированная вершина — это вершина, не имеющая рёбер, то есть не соединенная ни с одной другой вершиной." << endl;

    int edges; // количество рёбер
    cout << "Введите количество рёбер графа:" << endl;
    cin >> edges;

    if (edges < 0) {
        cout << "Количество рёбер не может быть отрицательным!" << endl;
        return 1;
    }

    // Вектор для хранения рёбер графа
    vector<vector<int>> listOfEdges;
    set<int> edge; // множество вершин
    int node1, node2, vertices = 0; // узлы и количество вершин
    vector<int> isol; // список изолированных вершин
    int edgesCount = 0; //кол-во вершин адекватное
    // Ввод рёбер
    cout << "Введите рёбра (node1 node2), для изолированных вершин введите -1 node:" << endl;
    for (int i = 0; i < edges; i++) {
        cin >> node1 >> node2;

        if (node1 != -1 && node2 != -1) {
            // Добавляем рёбра
            edgesCount++;
            for ( int j = 0; j < isol.size(); j++)
            {
                if (isol[j] == node1 || isol[j] == node2)
                {
                    cout<<"Одна из введеных вершин изолирована! Попробуйте сначала!!!" << endl;
                    return 0;
                }
            }
            edge.insert(node1);
            edge.insert(node2);
            listOfEdges.push_back({ node1, node2 });
        }
        else {
            // Проверка на ввод изолированной вершины
            int isolatedNode = (node1 == -1) ? node2 : node1;

            if (edge.find(isolatedNode) != edge.end()) {
                cout << "Данная вершина не может быть изолирована! Попробуйте сначала!!!" << endl;
                return 1;
            }
            isol.push_back(isolatedNode);
            edge.insert(isolatedNode);
        }
    }

    // Обновляем количество вершин
    for (int v : edge) {
        vertices = max(vertices, v);
    }
    vertices++; // увеличиваем количество вершин для корректной индексации

    // Создание матрицы смежности
    vector<vector<int>> matrix(vertices, vector<int>(vertices, 0));
    for (const auto& edge : listOfEdges) {
        matrix[edge[0]][edge[1]] = 1; // устанавливаем связь между узлами
        matrix[edge[1]][edge[0]] = 1; // для неориентированного графа
    }

    bool isolatedFlag; // флаг для изолированных вершин
    vector<int> loops; // список петель
    vector<int> degrees(vertices, 0); // вектор для хранения степеней вершин

    // Анализ графа
    for (int i = 0; i < vertices; i++) {
        isolatedFlag = true;
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) { // если есть связь
                isolatedFlag = false; // не изолированная вершина
                if (i == j) {
                    loops.push_back(i); // если соединена сама с собой
                }
                degrees[i]++; // увеличиваем степень вершины
            }
        }
    }
    // Вывод результатов
    cout << "\t\tРЕЗУЛЬТАТ" << endl;
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Количество вершин: " << vertices << endl;
    cout << "Количество рёбер: " << edgesCount << endl;
    cout << "Количество изолированных вершин: " << isol.size() << endl;
    if (!isol.empty()) {
        cout << "Изолированные вершины: ";
        for (int i : isol) {
            cout << i << "\t";
        }
        cout << endl;
    }
    cout << "Количество петель: " << loops.size() << endl;
    if (!loops.empty()) {
        cout << "Петли находятся в вершинах: ";
        for (int i : loops) {
            cout << i << "\t";
        }
        cout << endl;
    }

    // Сортировка степеней вершин в порядке убывания
    sort(degrees.begin(), degrees.end(), greater<int>());
    cout << "Степени вершин в порядке убывания:" << endl;
    for (int i : degrees) {
        cout << i << "\t";
    }
    cout << endl;

    // Запись данных в файл
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
    outputFile << "Количество рёбер: " << edgesCount << endl;
    outputFile << "Количество изолированных вершин: " << isol.size() << endl;
    if (!isol.empty()) {
        outputFile << "Изолированные вершины: ";
        for (int i : isol) {
            outputFile << i << "\t";
        }
        outputFile << endl;
    }
    outputFile << "Количество петель: " << loops.size() << endl;
    if (!loops.empty()) {
        outputFile << "Петли находятся в вершинах: ";
        for (int i : loops) {
            outputFile << i << "\t";
        }
        outputFile << endl;
    }
    outputFile << "Степени вершин в порядке убывания:" << endl;
    for (int i : degrees) {
        outputFile << i << "\t";
    }
    outputFile.close();

    return 0;
}
