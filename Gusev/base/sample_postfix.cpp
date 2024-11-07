#include <iostream>
#include <string>
#include <map>
#include <limits>     
#include "postfix.h"
#include "stack.h"

using namespace std;

int main() {
    // Вывод информации о программе
    cout << "Это калькулятор строк. Вы можете использовать следующие операции: +, -, *, /" << endl;
    cout << "Введите \"0\", чтобы закрыть программу." << endl;

    while (true) {  // Бесконечный цикл для работы калькулятора
        cout << "\n\nВведите арифметическое выражение: " << endl;
        string arithmetic_expression;
        getline(cin, arithmetic_expression);  // Считываем выражение целиком

        // Проверка на условие выхода из программы
        if (arithmetic_expression == "0") {
            cout << "До свидания :)" << endl;
            break;  // Выход из цикла и завершение программы
        }

        // Создание объекта TPostfix для обработки введённого выражения
        TPostfix expression(arithmetic_expression);

        // Вывод инфиксной формы выражения
        cout << "Вы ввели: " << arithmetic_expression << endl;

        // Здесь вы можете продолжить логику обработки и вывода результата...
    }

    return 0;
}