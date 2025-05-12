#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <sstream>
#include <algorithm>
#include <random> 

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int target;
    int weight;
    Edge(int t, int w) : target(t), weight(w) {}
};

// фия для безопасного ввода
int inputOrGenerate(const string& prompt, int minVal, int maxVal, bool allowRandom = true) {
    if (allowRandom) {
        cout << prompt << " (или введите -1 для случайного значения): ";
    }
    else {
        cout << prompt << ": ";
    }

    string line;
    getline(cin, line);
    stringstream ss(line);
    int value;

    if (ss >> value) {
        if (value == -1 && allowRandom) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(minVal, maxVal);
            return dist(gen);
        }
        if (value >= minVal && value <= maxVal) {
            return value;
        }
    }

    // если ввод некорректный или выбран рандом
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);
    cout << "Используется случайное значение: ";
    int random_value = dist(gen);
    cout << random_value << endl;
    return random_value;
}

int main() {

    setlocale(LC_ALL, "Rus");

    // выбор режима ввода
    cout << "Выберите режим:\n"
        << "1. Ручной ввод\n"
        << "2. Случайная генерация всех параметров\n";
    int mode = inputOrGenerate("Ваш выбор", 1, 2, false);

    // генерация параметров графа
    int n, m, start;
    if (mode == 2) {
        random_device rd;
        mt19937 gen(rd());
        n = uniform_int_distribution<>(2, 10)(gen);
        m = uniform_int_distribution<>(1, n * (n - 1))(gen);
        start = uniform_int_distribution<>(0, n - 1)(gen);
        cout << "\nСгенерированные параметры:\n"
            << "Вершин: " << n << "\n"
            << "Рёбер: " << m << "\n"
            << "Стартовая вершина: " << start << "\n";
    }
    else {
        n = inputOrGenerate("Введите количество вершин (2-100)", 2, 100);
        m = inputOrGenerate("Введите количество рёбер (1-" + to_string(n * (n - 1)) + ")", 1, n * (n - 1));
        start = inputOrGenerate("Введите стартовую вершину (0-" + to_string(n - 1) + ")", 0, n - 1);
    }

    vector<vector<Edge>> graph(n);

    // заполнение рёбер
    if (mode == 2) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> vertex_dist(0, n - 1);
        uniform_int_distribution<> weight_dist(1, 100);

        for (int i = 0; i < m; ++i) {
            int u = vertex_dist(gen);
            int v;
            do {
                v = vertex_dist(gen);
            } while (v == u); // исключаем петли

            graph[u].emplace_back(v, weight_dist(gen));
        }
    }
    else {
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
    }

    // АЛГОРИТМ Дейкстры
    vector<int> dist(n, INF);  // массив расстояний
    dist[start] = 0;

    // приоритетная очередь: (расстояние, вершина)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // пропускаем устаревшие записи
        if (current_dist > dist[u]) continue;

        // обновляем расстояния до соседей
        for (const Edge& e : graph[u]) {
            int v = e.target;
            int new_dist = dist[u] + e.weight;
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                pq.push({ new_dist, v });
            }
        }
    }

    // резы
    cout << "\nКратчайшие расстояния от вершины " << start << ":\n";
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
