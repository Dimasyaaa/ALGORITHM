#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
//#include <algorithm>
//#include <set>

using namespace std;

// ф-ия для считывания ребер графа из стандартного ввода
vector<pair<int, int>> readEdges() {
    vector<pair<int, int>> edges; // ребра
    int u, v; // вершины ркбер

    cout << "Введите рёбра графа в формате 'u v' (для завершения введите '0 0'): " << endl;
    while (true) {
        cin >> u >> v;
        if (u == 0 && v == 0) break; // конец
        edges.push_back(make_pair(u, v)); // добавление ребер
    }
    return edges;
}

// ф-ия для анализа графа и вывода характеристик
void analyzeGraph(const vector<pair<int, int>>& edges, const string& filename) {
    set<int> vertices; // множество для уникальных вершин
    vector<int> degrees; // вектор для  степеней вершин
    bool hasLoops = false; // наличие петель

    // проход по всем рёбрам 
    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;

        // обновление  вершин
        vertices.insert(u);
        vertices.insert(v);

        // проверка петель
        if (u == v) {
            hasLoops = true;
        }
    }
    //  вектор степеней
    int maxVertex = *vertices.rbegin(); //макс вершина из множества
    degrees.resize(maxVertex + 1, 0); // увелечинеи размера вектора до максимальной вершины

    for (const auto& edge : edges) {
        degrees[edge.first]++;
        degrees[edge.second]++;
    }
    // хара-ки графа
    int numVertices = vertices.size(); // колво вершин
    int numEdges = edges.size(); // колво ребер
    // вывод матрицы смежности
    vector<vector<int>> adjacencyMatrix(numVertices + 1, vector<int>(numVertices + 1, 0));

    for (const auto& edge : edges) {
        adjacencyMatrix[edge.first][edge.second] = 1;
        adjacencyMatrix[edge.second][edge.first] = 1; // Обновление матрицы для неориентированного графа
    }

    cout << "Матрица смежности:\n";
    for (int i = 1; i <= numVertices; i++) {
        for (int j = 1; j <= numVertices; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Количество вершин: " << numVertices << endl;
    cout << "Количество рёбер: " << numEdges << endl;
    // провека изолированных вершин
    bool hasIsolated = false;
    for (int i = 1; i <= maxVertex; i++) {
        if (degrees[i] == 0) {
            hasIsolated = true;
            break;
        }
    }
    cout << "Наличие изолированных вершин: " << (hasIsolated ? "Есть" : "Нет") << endl;
    // проверка петли
    cout << "Наличие петель: " << (hasLoops ? "Есть" : "Нет") << endl;
    // список степеней вершин
    vector<int> degreeList;
    for (int i = 1; i <= maxVertex; i++) {
        if (degrees[i] > 0) { // пропуск изолированных вершин
            degreeList.push_back(degrees[i]);
        }
    }
    // сортировка
    sort(degreeList.begin(), degreeList.end(), greater<int>());

    cout << "Список степеней вершин в порядке убывания: ";
    for (int degree : degreeList) {
        cout << degree << " "; // вывод степеней вершин
    }
    cout << endl;
    // сохр в файл
    ofstream outfile(filename, ios::app);
    outfile << "\n--- Выходные данные ---\n";
    outfile << "Матрица смежности:\n";
    for (const auto& row : adjacencyMatrix) {
        for (int val : row) {
            outfile << val << " ";
        }
        outfile << endl;
    }
    outfile << "Количество вершин: " << numVertices << endl;
    outfile << "Количество рёбер: " << numEdges << endl;
    outfile << "Наличие изолированных вершин: " << (hasIsolated ? "Есть" : "Нет") << endl;
    outfile << "Наличие петель: " << (hasLoops ? "Есть" : "Нет") << endl;
    outfile << "Список степеней вершин в порядке убывания: ";
    for (int degree : degreeList) {
        outfile << degree << " ";
    }
    outfile << endl;
    outfile.close();
}

int main() {
    setlocale(LC_ALL, "Rus");
    vector<pair<int, int>> edges = readEdges();
    analyzeGraph(edges, "output.txt");

    return 0;
}
