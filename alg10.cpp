#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

// Узел дерева
class Node {
public:
    int key; // Ключ узла
    Node* leftChild; // Указатель на левого потомка
    Node* rightChild; // Указатель на правого потомка

    // Конструктор
    Node(int value) {
        key = value;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    // Метод для вывода данных узла
    void displayNode() {
        cout << "(" << key << ", ";
        if (leftChild != nullptr)
            cout << leftChild->key;
        else
            cout << "null";

        cout << ", ";

        if (rightChild != nullptr)
            cout << rightChild->key;
        else
            cout << "null";

        cout << ")";
    }
};

// Дерево поиска
class Tree {
private:
    Node* root; // Корневой узел

public:
    // Конструктор
    Tree() {
        root = nullptr; // Изначально дерево пустое
    }

    // Метод для поиска узла с заданным ключом
    Node* find(int key) {
        Node* current = root; // Начинаем с корня
        while (current != nullptr) {
            if (key == current->key) {
                return current; // Элемент найден
            }
            else if (key < current->key) {
                current = current->leftChild; // Двигаемся налево
            }
            else {
                current = current->rightChild; // Двигаемся направо
            }
        }
        return nullptr; // Элемент не найден
    }

    // Метод для вставки узла
    void insert(int key) {
        Node* newNode = new Node(key); // Создаем новый узел

        if (root == nullptr) {
            root = newNode; // Если дерево пустое, новый узел становится корнем
        }
        else {
            Node* current = root; // Начинаем с корня
            Node* parent = nullptr;

            while (true) {
                parent = current;
                if (key < current->key) {
                    current = current->leftChild; // Двигаемся налево
                    if (current == nullptr) { // Если достигнут конец цепочки
                        parent->leftChild = newNode; // Вставляем слева
                        return;
                    }
                }
                else {
                    current = current->rightChild; // Двигаемся направо
                    if (current == nullptr) { // Если достигнут конец цепочки
                        parent->rightChild = newNode; // Вставляем справа
                        return;
                    }
                }
            }
        }
    }

    // Метод для удаления узла
    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return root; // Если дерево пустое

        // Рекурсивный поиск узла для удаления
        if (key < root->key) {
            root->leftChild = deleteNode(root->leftChild, key);
        }
        else if (key > root->key) {
            root->rightChild = deleteNode(root->rightChild, key);
        }
        else {
            // Узел найден, выполняем удаление
            if (root->leftChild == nullptr) {
                Node* temp = root->rightChild;
                delete root; // Удаляем узел
                return temp; // Возвращаем правого потомка
            }
            else if (root->rightChild == nullptr) {
                Node* temp = root->leftChild;
                delete root; // Удаляем узел
                return temp; // Возвращаем левого потомка
            }

            // Узел с двумя потомками: получаем inorder преемника (минимальное значение в правом поддереве)
            Node* temp = root->rightChild;
            while (temp && temp->leftChild != nullptr) {
                temp = temp->leftChild;
            }

            // Заменяем ключ узла на ключ преемника
            root->key = temp->key;

            // Удаляем преемника
            root->rightChild = deleteNode(root->rightChild, temp->key);
        }
        return root;
    }

    // Метод для вызова удаления корневого узла
    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    // Метод для вывода структуры дерева
    void displayTree(Node* node) {
        if (node != nullptr) {
            displayTree(node->leftChild); // Сначала левое поддерево
            node->displayNode(); // Затем текущий узел
            cout << " "; // Добавляем пробел между узлами
            displayTree(node->rightChild); // И правое поддерево
        }
    }

    // Метод для доступа к корню
    Node* getRoot() {
        return root;
    }

    // Метод для вывода дерева в виде скобочной структуры
    void printTreeStructure(Node* node) {
        if (node == nullptr) {
            cout << "null";
            return;
        }
        cout << "(" << node->key << " ";
        printTreeStructure(node->leftChild);
        cout << " ";
        printTreeStructure(node->rightChild);
        cout << ")";
    }
};

// Функция для проверки ввода
bool validateInput(const string& input, int& output) {
    try {
        size_t pos;
        output = stoi(input, &pos);

        // Проверяем, что вся строка была обработана (нет лишних символов)
        if (pos != input.length()) {
            return false;
        }
        return true;
    } catch (...) {
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    Tree theTree; // Создаем дерево

    // Пример вставки узлов
    theTree.insert(50);
    theTree.insert(25);
    theTree.insert(75);
    theTree.insert(12);
    theTree.insert(37);
    theTree.insert(43);
    theTree.insert(30);
    theTree.insert(33);
    theTree.insert(87);
    theTree.insert(93);
    theTree.insert(97);

    cout << "Первоначальная структура дерева:" << endl;
    theTree.printTreeStructure(theTree.getRoot());
    cout << endl << endl;

    // Ввод ключа для поиска
    string input;
    int searchKey;
    while (true) {
        cout << "Введите ключ для поиска: ";
        cin >> input;

        if (!validateInput(input, searchKey)) {
            cout << "Ошибка: введите целое число!" << endl;
            continue;
        }
        break;
    }

    // Поиск узла
    Node* foundNode = theTree.find(searchKey);
    if (foundNode != nullptr) {
        cout << "Найден узел: ";
        foundNode->displayNode(); // Выводим узел
        cout << endl;
    }
    else {
        cout << "Заданный ключ в дереве не найден." << endl;
    }

    // Вставляем ключ
    int insertKey;
    while (true) {
        cout << "Введите ключ для добавления: ";
        cin >> input;

        if (!validateInput(input, insertKey)) {
            cout << "Ошибка: введите целое число!" << endl;
            continue;
        }
        break;
    }
    theTree.insert(insertKey);

    // Ввод ключа для удаления
    int deleteKey;
    while (true) {
        cout << "Введите ключ для удаления: ";
        cin >> input;

        if (!validateInput(input, deleteKey)) {
            cout << "Ошибка: введите целое число!" << endl;
            continue;
        }
        break;
    }
    theTree.deleteKey(deleteKey);

    // Вывод структуры дерева в порядке возрастания
    cout << "Структура дерева (in-order):" << endl;
    theTree.displayTree(theTree.getRoot());
    cout << endl << endl;

    // Вывод дерева в виде скобочной структуры
    cout << "Структура дерева (скобочная форма):" << endl;
    theTree.printTreeStructure(theTree.getRoot());
    cout << endl;

    return 0;
}
