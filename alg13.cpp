#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <sstream>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int target;
    int weight;
    Edge(int t, int w) : target(t), weight(w) {}
};

int main() {
    setlocale(LC_ALL, "Rus");

    int n, m, start;

    // Ввод количества вершин
    cout << "Введите количество вершин (2-100): ";
    cin >> n;
    while (n < 2 || n > 100) {
        cout << "Некорректный ввод. Введите количество вершин (2-100): ";
        cin >> n;
    }

    // Ввод количества рёбер
    cout << "Введите количество рёбер (1-" << n * (n - 1) << "): ";
    cin >> m;
    while (m < 1 || m > n * (n - 1)) {
        cout << "Некорректный ввод. Введите количество рёбер (1-" << n * (n - 1) << "): ";
        cin >> m;
    }

    // Ввод стартовой вершины
    cout << "Введите стартовую вершину (0-" << n - 1 << "): ";
    cin >> start;
    while (start < 0 || start >= n) {
        cout << "Некорректный ввод. Введите стартовую вершину (0-" << n - 1 << "): ";
        cin >> start;
    }

    vector<vector<Edge>> graph(n);

    // Заполнение рёбер
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < m; ++i) {
        bool valid = false;
        int u, v, w;
        while (!valid) {
            cout << "Введите ребро " << i + 1 << " (u v w): ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            if (ss >> u >> v >> w) {
                char extra;
                if (ss >> extra) {
                    cout << "Ошибка: лишние символы.\n";
                }
                else if (u < 0 || u >= n || v < 0 || v >= n) {
                    cout << "Ошибка: вершины должны быть 0-" << n - 1 << ".\n";
                }
                else if (w < 1) {
                    cout << "Ошибка: вес должен быть положительным.\n";
                }
                else {
                    valid = true;
                }
            }
            else {
                cout << "Ошибка: некорректный формат.\n";
            }
        }
        graph[u].emplace_back(v, w);
    }

    // Вывод информации о графе
    cout << "\nСтруктура графа:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Вершина " << i << " соединена с: ";
        for (const Edge& e : graph[i]) {
            cout << e.target << "(вес " << e.weight << ") ";
        }
        cout << "\n";
    }

    // АЛГОРИТМ Дейкстры
    vector<int> dist(n, INF);  // массив расстояний
    dist[start] = 0;

    // приоритетная очередь: (расстояние, вершина)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    int step = 1;
    while (!pq.empty()) {
        cout << "\n=== Итерация " << step++ << " ===\n";
        cout << "Состояние очереди перед извлечением: ";
        auto pq_copy = pq;
        while (!pq_copy.empty()) {
            cout << "(" << pq_copy.top().first << "," << pq_copy.top().second << ") ";
            pq_copy.pop();
        }
        cout << "\n";

        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        cout << "Извлекаем вершину " << u << " с расстоянием " << current_dist << "\n";

        // пропускаем устаревшие записи
        if (current_dist > dist[u]) {
            cout << "Это устаревшее расстояние, пропускаем\n";
            continue;
        }

        // обновляем расстояния до соседей
        cout << "Обрабатываем соседей вершины " << u << ":\n";
        for (const Edge& e : graph[u]) {
            int v = e.target;
            int new_dist = current_dist + e.weight;  // Исправлено: используем current_dist вместо dist[u]
            cout << "  Сосед " << v << ", текущее расстояние: " << dist[v] 
                 << ", возможное новое: " << new_dist;
            
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                pq.push({ new_dist, v });
                cout << " - ОБНОВЛЕНО\n";
            } else {
                cout << " - не улучшено\n";
            }
        }

        // Вывод текущих расстояний
        cout << "Текущие расстояния после итерации:\n";
        for (int i = 0; i < n; ++i) {
            cout << "До " << i << ": ";
            if (dist[i] == INF) cout << "INF";
            else cout << dist[i];
            cout << "\n";
        }
    }

    // резы
    cout << "\nИтоговые кратчайшие расстояния от вершины " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << "До вершины " << i << ": недостижима\n";
        }
        else {
            cout << "До вершины " << i << ": " << dist[i] << "\n";
        }
    }

    return 0;
}
