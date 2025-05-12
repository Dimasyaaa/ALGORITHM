#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>   // Для numeric_limits
#include <sstream>  // Для stringstream

using namespace std;

// структура ребра графи
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    // перегрузка оператора для сортировки рёбер по возрастанию веса
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// классс системы непересекающихся множеств (DSU)
class DSU {
private:
    vector<int> parent;  // массив для хранения родительских вершин
    vector<int> rank;    // ранг для объединения по высоте дерева

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Инициализация: каждая вершина - своя собственная родительская
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // найти корень множества, содержащего вершину u
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // оптимизация
        return parent[u];
    }

    // объединить множества, содержащие вершины u и v
    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            // поддерживаем дерево с меньшим рангом под корнем дерева с большим рангом
            if (rank[u] < rank[v])
                swap(u, v);
            parent[v] = u;
            if (rank[u] == rank[v])
                rank[u]++;
        }
    }
};

// ф-ия для безопасного ввода целого числа с проверкой диапазона
int readInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
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

    // ввод количества вершин с проверкой
    int n = readInt("Введите количество вершин (не менее 1): ", 1, numeric_limits<int>::max());

    // ввод количества рёбер с проверкой
    int m = readInt("Введите количество рёбер (не менее 0): ", 0, numeric_limits<int>::max());

    vector<Edge> edges;
    edges.reserve(m);

    // ввод рёбер с проверкой
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        bool valid = false;
        while (!valid) {
            cout << "Введите ребро " << i + 1 << " в формате u v w: ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            if (ss >> u >> v >> w) {
                // проверка на лишние символы
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
                cout << "Ошибка: некорректный ввод. Введите три целых числа.\n";
            }
        }
        edges.emplace_back(u, v, w);
    }

    // входные данные
    cout << "\nВходные данные (рёбра графа):\n";
    for (const Edge& e : edges) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }

    // сортировка рёбер по возрастанию веса
    sort(edges.begin(), edges.end());

    DSU dsu(n);          // инициализация DSU
    vector<Edge> mst;    // минимальное остовное дерево
    int total_weight = 0; // суммарный вес MST

    // Алгоритм Крускала: обработка рёбер в порядке возрастания веса
    for (const Edge& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            mst.push_back(e);
            total_weight += e.weight;
            dsu.unite(e.u, e.v);
            // если дерево уже содержит n-1 ребро, завершаем цикл
            if (mst.size() == n - 1)
                break;
        }
    }

    // проверка на связность графа
    if (mst.size() != n - 1) {
        cout << "\nГраф не связный, минимальное остовное дерево не существует.\n";
        return 0;
    }

    // резы
    cout << "\nРёбра минимального остовного дерева:\n";
    for (const Edge& e : mst) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }
    cout << "Суммарный вес: " << total_weight << endl;

    return 0;
}
