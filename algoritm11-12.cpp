#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>   
#include <sstream>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int u, v, weight;  // вершины u и v, вес ребра
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    // Перегрузка оператора < для сортировки рёбер по весу
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Класс для системы непересекающихся множеств (DSU)
class DSU {
private:
    vector<int> parent;  // массив родителей вершин
    vector<int> rank;    // массив рангов вершин

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Изначально каждая вершина - своё собственное множество
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // Нахождение корня множества для вершины u с path compression
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Объединение множеств, содержащих u и v, с union by rank
    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] < rank[v])
                swap(u, v);
            parent[v] = u;
            if (rank[u] == rank[v])
                rank[u]++;
        }
    }
};

// Функция для безопасного чтения целого числа с проверками
int readInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        cin >> line;
        stringstream ss(line);
        if (ss >> value && ss.eof()) {
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            cout << "Ошибка: число должно быть в диапазоне от " << minVal << " до " << maxVal << ".\n";
        }
        else {
            cout << "Ошибка: введите целое число.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    cout << "Алгоритм Краскала для поиска минимального остовного дерева\n";
    cout << "Примечание: вершины нумеруются с 0!\n\n";

    // Чтение количества вершин и рёбер
    int n = readInt("Введите количество вершин (не менее 1): ", 1, numeric_limits<int>::max());
    int m = readInt("Введите количество рёбер (не менее 0): ", 0, numeric_limits<int>::max());

    vector<Edge> edges;
    edges.reserve(m);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Чтение рёбер с проверками
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        bool valid = false;
        while (!valid) {
            cout << "Введите ребро " << i + 1 << " (u v w), где u и v - вершины (0.." << n-1 << "), w - вес: ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            if (ss >> u >> v >> w) {
                char extra;
                if (ss >> extra) {
                    cout << "Ошибка: лишние символы в строке.\n";
                }
                else if (u < 0 || u >= n || v < 0 || v >= n) {
                    cout << "Ошибка: вершины должны быть от 0 до " << n - 1 << ".\n";
                }
                else if (w < 0) {
                    cout << "Ошибка: вес должен быть неотрицательным.\n";
                }
                else {
                    valid = true;
                }
            }
            else {
                cout << "Ошибка: некорректный ввод. Введите три целых числа (u v w).\n";
            }
        }
        edges.emplace_back(u, v, w);
    }

    // Вывод введённых рёбер
    cout << "\nВходные данные (рёбра графа):\n";
    for (const Edge& e : edges) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }

    // Сортировка рёбер по весу (ключевой шаг алгоритма Крускала)
    sort(edges.begin(), edges.end());
    cout << "\nРёбра после сортировки по весу:\n";
    for (const Edge& e : edges) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }

    // Построение MST с помощью DSU
    DSU dsu(n);
    vector<Edge> mst;
    int total_weight = 0;
    
    cout << "\nПроцесс построения MST:\n";
    for (const Edge& e : edges) {
        cout << "Проверяем ребро " << e.u << "-" << e.v << " (вес " << e.weight << "): ";
        
        // Если вершины в разных компонентах связности, добавляем ребро в MST
        if (dsu.find(e.u) != dsu.find(e.v)) {
            cout << "добавляем в MST (вершины в разных компонентах)\n";
            mst.push_back(e);
            total_weight += e.weight;
            dsu.unite(e.u, e.v);
            
            // MST содержит n-1 ребро для n вершин
            if (mst.size() == n - 1) {
                cout << "Получено " << n-1 << " ребро - MST построено.\n";
                break;
            }
        } else {
            cout << "пропускаем (вершины в одной компоненте)\n";
        }
    }

    // Проверка связности графа
    if (mst.size() != n - 1) {
        cout << "\nГраф не связный, минимальное остовное дерево не существует.\n";
        return 0;
    }

    // Вывод результатов
    cout << "\nРезультат:\nРёбра минимального остовного дерева:\n";
    for (const Edge& e : mst) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }
    cout << "Суммарный вес MST: " << total_weight << endl;

    return 0;
}
