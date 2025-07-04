//Итог
#include <iostream>
#include <string>
#include <vector>

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

    // Функция для добавления в стек
    void push(char c) {
        Node* newNode = new Node();
        newNode->data = c;
        newNode->next = top;
        top = newNode;
    }

    // Функция для удаления элемента из стека
    char pop() {
        if (top == nullptr) {
            return '0'; // стек пустой
        }
        char c = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return c;
    }

    // Проверка, пустой ли стек
    bool empty() {
        return top == nullptr;
    }
};

// Функция для проверки правильности расстановки скобок
void check(const string& expression) {
    Stack stack;
    bool contains = false; // Флаг для отслеживания наличия скобок
    bool err = false;

    for (size_t i = 0; i < expression.size(); i++) {
        char current = expression[i];

        // Открытую скобку добавляем в стек
        if (current == '(' || current == '{' || current == '[') {
            stack.push(current);
            contains = true; // Ставим флаг
        }
        // Если закрывающая скобка, проверяем стек
        else if (current == ')' || current == '}' || current == ']') {
            if (stack.empty()) {
                cout << "Ошибка: найдена закрывающая скобка '" << current << "' без соответствующей открывающей." << endl;
                err = true;
                //return;
            }
            char topItem = stack.pop();
            // Проверка на соответствие скобок
            if ((topItem == '(' && current != ')') ||
                (topItem == '{' && current != '}') ||
                (topItem == '[' && current != ']')) {
                cout << "Ошибка: несоответствующие скобки '" << topItem << "' и '" << current << "'." << endl;
                err = true;
                //return;
            }
        }
    }

    // Если стек не пуст в конце, это означает, что есть открывающие скобки без закрывающих
    vector<char> unclosedBrackets; // Для хранения открывающих скобок, которые остались в стеке(костыль)
    while (!stack.empty()) {
        unclosedBrackets.push_back(stack.pop());
    }

    // Вывод инфs об ошибках
    if (!unclosedBrackets.empty()) {
        cout << "Ошибка: есть открывающие скобки без соответствующих закрывающих: ";
        for (char c : unclosedBrackets) {
            cout << c << " "; 
        }
        cout << endl;
        err = true;
    }

    // Скобочек нет или мы расставили их идеально
    if (!contains) {
        cout << "В строке скобок нет." << endl;
    }
    else if (contains && err) {
        cout << "Есть ошибки!" << endl;
    }
    else {
        cout << "Скобки расставлены правильно." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    string test;
    cout << "Введите строку для проверки: ";
    getline(cin, test);
    check(test);
    system("pause");

    return 0;
}
