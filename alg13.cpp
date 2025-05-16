#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <sstream>

using namespace std;

// константа недостижимой вершины
const int INF = numeric_limits<int>::max();

// структура ребра
struct Edge {
    int target;    // номер вершины
    int weight;    // вес ребра 
    Edge(int t, int w) : target(t), weight(w) {}
};

// ф-ия для безопасного ввода чисел
int getInput(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && value >= minVal && value <= maxVal) {
            return value;
        }
        cout << "Ошибка! Введите число от " << minVal << " до " << maxVal << ".\n";
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    // пояснение для пользователя
    cout << "Алгоритм Дейкстры — это метод поиска кратчайшего пути от одной вершины графа ко всем остальным.\n";
    cout << "INF - это специальное значение, обозначающее, что вершина недостижима из стартовой точки.\n\n";

    // ввод основных параметров графа
    int n = getInput("Введите количество вершин (2-100): ", 2, 100);
    int m = getInput("Введите количество рёбер (1-" + to_string(n * (n - 1)) + "): ", 1, n * (n - 1));
    int start = getInput("Введите стартовую вершину (0-" + to_string(n - 1) + "): ", 0, n - 1);

    // создание списка смежности для представления графа
    vector<vector<Edge>> graph(n);

    // блок ввода рёбер
    cout << "\n=== Ввод рёбер ===\n";
    for (int i = 0; i < m; ++i) {
        while (true) {
            cout << "Введите ребро " << i + 1 << " (u v w): ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            int u, v, w;

            
            if (ss >> u >> v >> w) {
                // проверка корректности номеров вершин
                if (u < 0 || u >= n || v < 0 || v >= n) {
                    cout << "Неверные номера вершин! ";
                    continue;
                }
                // проверка положительности веса
                if (w <= 0) {
                    cout << "Вес должен быть положительным! ";
                    continue;
                }
                // добавление ребра в граф
                graph[u].emplace_back(v, w);
                break;
            }
            cout << "Ошибка формата! ";
        }
    }

    // алгоритм Дейкстры
    vector<int> dist(n, INF);  // массив кратчайших расстояний
    dist[start] = 0;           // нулевое расстояние до стартовой вершины

    // приоритетная очередь для выбора следующей вершины с минимальным расстоянием
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    // начало работы алгоритма
    cout << "\n=== Начало обработки ===\n";
    cout << "Стартовая вершина: [" << start << "]\n";
    cout << "Инициализация расстояний: ";
    for (int i = 0; i < n; ++i) {
        cout << (i == start ? "0" : "INF") << " ";
    }
    cout << "\n" << string(50, '-') << endl;

    int step = 1;
    while (!pq.empty()) {

        // извлечение вершины с минимальным текущим расстоянием
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        cout << "\nШаг " << step++ << ":\n";
        cout << "Извлечена вершина [" << u << "] с текущим расстоянием " << current_dist << "\n";

        // проверка на актуальность извлеченного расстояния
        if (current_dist > dist[u]) {
            cout << "  ! Устаревшее расстояние! Текущее лучше: " << dist[u] << " < " << current_dist << ". Пропуск.\n";
            continue;
        }

        // обработка всех исходящих рёбер текущей вершины
        cout << "  Обработка рёбер:\n";
        for (const Edge& e : graph[u]) {
            int v = e.target;
            int new_dist = current_dist + e.weight;

            // инфа о текущем ребре
            cout << "  * Ребро " << u << "->" << v << " (вес " << e.weight << ")\n";
            cout << "    Текущее расстояние до [" << v << "]: "
                << (dist[v] == INF ? "INF" : to_string(dist[v]))
                << " | Новое: " << new_dist;

            // обнова расстояния при нахождении более короткого пути
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                pq.push({ new_dist, v });
                cout << "  [V] Улучшение! Добавляем [" << v << "] в очередь.\n";
            }
            else {
                cout << "  [X] Не улучшает.\n";
            }
        }

        // промежуточное состояние расстояний
        cout << "\nТекущее состояние расстояний:\n";
        for (int i = 0; i < n; ++i) {
            cout << "[" << i << "]: "
                << (dist[i] == INF ? "INF" : to_string(dist[i])) << " | ";
        }
        cout << "\n" << string(50, '-') << endl;
    }

    // резы
    cout << "\n=== Результаты ===\n";
    for (int i = 0; i < n; ++i) {
        cout << "-> До вершины [" << i << "]: ";
        if (dist[i] == INF) cout << "недостижима\n";
        else cout << dist[i] << "\n";
    }

    return 0;
}
