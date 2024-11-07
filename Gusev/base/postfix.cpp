#include "postfix.h"
#include "stack.h"
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <iostream> // Для отладочного вывода

// Инициализация карты приоритетов операторов
map<char, int> TPostfix::operatorPrecedence = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
};

// Разделение инфиксного выражения на токены (лексемы)
void TPostfix::tokenizeExpression() {
    parsedTokens.clear();
    string token;
    for (size_t i = 0; i < infixExpression.size(); ++i) {
        char ch = infixExpression[i];
        if (isspace(ch)) continue;

        if (isalpha(ch)) {
            // Считываем всю переменную или идентификатор
            token += ch;
            while (i + 1 < infixExpression.size() && (isalnum(infixExpression[i + 1]))) {
                token += infixExpression[++i];
            }
            parsedTokens.push_back(token);
            token.clear();
        }
        else if (isdigit(ch)) {
            token += ch;
            while (i + 1 < infixExpression.size() && (isdigit(infixExpression[i + 1]) || infixExpression[i + 1] == '.')) {
                token += infixExpression[++i];
            }
            parsedTokens.push_back(token);
            token.clear();
        }
        else if (ch == '(' || ch == ')') {
            parsedTokens.push_back(string(1, ch));
        }
        else {
            parsedTokens.push_back(string(1, ch)); // оператор
        }
    }
}

// Преобразование инфиксного выражения в постфиксное
void TPostfix::convertToPostfix() {
    TStack<char> operators(50); // Увеличиваем размер стека
    postfixTokens.clear();
    for (const string& token : parsedTokens) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            postfixTokens.push_back(token);
        }
        else if (isalpha(token[0])) {
            postfixTokens.push_back(token);
        }
        else if (token == "(") {
            operators.push('(');
        }
        else if (token == ")") {
            while (!operators.isEmpty() && operators.top() != '(') {
                postfixTokens.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.pop(); // Удаление левой скобки
        }
        else {
            while (!operators.isEmpty() && operatorPrecedence[operators.top()] >= operatorPrecedence[token[0]]) {
                postfixTokens.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.push(token[0]);
        }
    }
    while (!operators.isEmpty()) {
        postfixTokens.push_back(string(1, operators.top()));
        operators.pop();
    }
}

// Возвращает инфиксное выражение как строку
string TPostfix::getInfixExpression() const {
    string result;
    for (const auto& token : parsedTokens) {
        result += token + " ";
    }
    return result;
}

// Возвращает постфиксное выражение как строку
string TPostfix::getPostfixExpression() const {
    string result;
    for (const auto& token : postfixTokens) {
        result += token + " ";
    }
    return result;
}

// Вычисление постфиксного выражения и возврат результата
double TPostfix::evaluate() const {
    TStack<double> operands(50); // Увеличиваем размер стека
    for (const string& token : postfixTokens) {
        if (isNumberOrVariable(token)) {
            if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
                operands.push(stod(token));
            }
            else {
                operands.push(getVariableValue(token));
            }
        }
        else {
            if (operands.currentSize() < 2) {
                throw std::runtime_error("Error in postfix expression: insufficient operands.");
            }
            double operand2 = operands.pop();
            double operand1 = operands.pop();
            double result = performOperation(operand1, operand2, token[0]);
            operands.push(result);
        }
    }
    if (operands.currentSize() != 1) {
        throw std::runtime_error("Error in postfix expression: more than one operand left.");
    }
    return operands.pop();
}

// Выполнение операции над числами
double TPostfix::performOperation(double operand1, double operand2, char op) const {
    switch (op) {
    case '+': return operand1 + operand2;
    case '-': return operand1 - operand2;
    case '*': return operand1 * operand2;
    case '/':
        if (operand2 == 0) {
            throw std::runtime_error("Division by zero.");
        }
        return operand1 / operand2;
    default:
        throw std::runtime_error("Unknown operator.");
    }
}

// Проверка, является ли токен числом или переменной
bool TPostfix::isNumberOrVariable(const string& token) const {
    return isdigit(token[0]) || (token.size() > 1 && isdigit(token[1])) || isalpha(token[0]);
}
