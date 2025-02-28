#include <iostream>
#include <string>

using namespace std;

// Структура для узла стека
struct Node {
    char data;
    Node* next;
};

// Структура для стека
struct Stack {
    Node* top;

    Stack() {
        top = nullptr;
    }

    // Функция для добавления элемента в стек
    void push(char c) {
        Node* newNode = new Node();
        newNode->data = c;
        newNode->next = top;
        top = newNode;
    }

    // Функция для удаления элемента из стека
    char pop() {
        if (top == nullptr) {
            return '0'; // стек пуст
        }
        char c = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return c;
    }

    // Функция для проверки, пуст ли стек
    bool isEmpty() {
        return top == nullptr;
    }

    // Деструктор для освобождения памяти
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Функция для проверки правильности расстановки скобок
void checkBrackets(const string& test) {
    Stack stack;
    int roundOpen = 0, curlyOpen = 0, squareOpen = 0; // Счетчики открывающих скобок
    bool hasExtraClosing = false;
    bool hasMismatched = false;
    char mismatchedOpen = '0'; // Для хранения несоответствующей открывающей скобки
    int position = -1; // Позиция несоответствующей скобки
    int bracketCount = 0; // Счетчик всех скобок

    for (size_t i = 0; i < test.size(); i++) {
        char current = test[i];

        // Если встречается открывающая скобка, помещаем её в стек и увеличиваем соответствующий счетчик
        if (current == '(' || current == '{' || current == '[') {
            stack.push(current);
            bracketCount++; // Увеличиваем общий счетчик скобок
            if (current == '(') roundOpen++;
            else if (current == '{') curlyOpen++;
            else if (current == '[') squareOpen++;
        }
        // Если встречается закрывающая скобка, проверяем стек
        else if (current == ')' || current == '}' || current == ']') {
            bracketCount++; // Увеличиваем общий счетчик скобок
            char topItem = stack.pop();
            // Если стек пуст, значит есть лишняя закрывающая скобка
            if (topItem == '0') {
                hasExtraClosing = true;
                position = i + 1; // Сохраняем позицию
                mismatchedOpen = current; // Сохраняем закрывающую скобку
                continue; // Переходим к следующей итерации
            }
            // Проверяем соответствие скобок по типу
            if ((topItem == '(' && current != ')') ||
                (topItem == '{' && current != '}') ||
                (topItem == '[' && current != ']')) {
                hasMismatched = true;
                mismatchedOpen = topItem; // Сохраняем несоответствующую открывающую скобку
                position = i + 1; // Сохраняем позицию закрывающей скобки
            }
        }
    }

    // Проверка на лишние открывающиеся скобки
    if (!stack.isEmpty()) {
        cout << "Ошибка: лишняя открывающаяся скобка '"
            << stack.pop() << "' осталась в стеке." << endl;
    }

    // Вывод ошибок, если они были найдены
    if (hasExtraClosing) {
        cout << "Ошибка: лишняя закрывающая скобка '" << mismatchedOpen
            << "' на позиции " << position << endl;
    }
    if (hasMismatched) {
        cout << "Ошибка: несоответствие скобок '" << mismatchedOpen << "' на позиции " << position << endl;
    }

    // Проверка на недостающие скобки
    if (roundOpen > 0) cout << "Недостающие закрывающие скобки: " << roundOpen << " для '('" << endl;
    if (curlyOpen > 0) cout << "Недостающие закрывающие скобки: " << curlyOpen << " для '{" << endl;
    if (squareOpen > 0) cout << "Недостающие закрывающие скобки: " << squareOpen << " для '['" << endl;

    // Если нет ошибок и не было найдено ни одной скобки, выводим сообщение об отсутствии скобок
    if (bracketCount == 0) {
        cout << "В строке нет скобок." << endl;
        return;
    }

    // Если нет ошибок, выводим сообщение об успехе
    if (stack.isEmpty() && roundOpen == 0 && curlyOpen == 0 && squareOpen == 0 && !hasExtraClosing && !hasMismatched) {
        cout << "Расстановка скобок правильная." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    string test;

    cout << "Введите строку для проверки расстановки скобок:" << endl;
    getline(cin, test);
    checkBrackets(test);

    return 0;
}
