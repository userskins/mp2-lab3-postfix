#ifndef POSTFIX_H
#define POSTFIX_H

#include "stack.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stdexcept>
#include <cctype>

using namespace std;

class TPostfix {
    string infixExpression;                   // Инфиксное выражение
    vector<string> postfixTokens;             // Постфиксные токены
    vector<string> parsedTokens;              // Лексемы инфиксного выражения
    static map<char, int> operatorPrecedence; // Приоритет операторов
    map<string, double> variableValues;       // Значения переменных
    set<string> fixedVariables;               // Набор неизменяемых переменных

    // Разбивает инфиксное выражение на лексемы
    void tokenizeExpression();

    // Преобразует инфиксное выражение в постфиксное
    void convertToPostfix();

public:
    TPostfix() = default;  // Конструктор по умолчанию
    explicit TPostfix(const string& expression) { setInfixExpression(expression); }

    // Метод для проверки сбалансированности скобок в выражении
    void TPostfix::checkBrackets() const {
        int balance = 0;  // Счетчик для скобок
        for (char ch : infixExpression) {
            if (ch == '(') {
                balance++;
            }
            else if (ch == ')') {
                balance--;
                if (balance < 0) {  // Больше закрывающих скобок
                    throw std::runtime_error("Unbalanced parentheses: more closing brackets.");
                }
            }
        }
        if (balance != 0) {  // Недостающая закрывающая или открывающая скобка
            throw std::runtime_error("Unbalanced parentheses: unmatched opening bracket.");
        }
    }

    // Устанавливает инфиксное выражение и проверяет его на сбалансированность
    void TPostfix::setInfixExpression(const string& expression) {
        infixExpression = expression;
        checkBrackets();  // Проверка на сбалансированность скобок
        tokenizeExpression();  // Разбиение выражения на токены
        convertToPostfix();  // Преобразование инфиксного выражения в постфиксное
    }

    // Возвращает инфиксное выражение как строку
    string getInfixExpression() const;

    // Возвращает список токенов инфиксного выражения
    vector<string> GetInfix() const { return parsedTokens; }

    // Возвращает постфиксное выражение как строку
    string getPostfixExpression() const;

    // Возвращает список постфиксных токенов
    vector<string> GetPostfix() const { return postfixTokens; }

    // Оценивает выражение
    double evaluate() const;

    // Устанавливает значение переменной
    void setVariableValue(const string& var, double value) {
        if (isVariableFixed(var)) {
            throw std::runtime_error("Variable is fixed and cannot be modified.");
        }
        variableValues[var] = value;
    }

    // Получает значение переменной
    double getVariableValue(const string& var) const {
        if (variableValues.find(var) != variableValues.end()) {
            return variableValues.at(var);
        }
        throw std::runtime_error("Variable not found.");
    }

    // Устанавливает переменную как неизменяемую
    void fixVariable(const string& var) { fixedVariables.insert(var); }

    // Проверяет, является ли переменная неизменяемой
    bool isVariableFixed(const string& var) const { return fixedVariables.find(var) != fixedVariables.end(); }

private:
    // Выполняет операцию над двумя операндами
    double performOperation(double operand1, double operand2, char op) const;

    // Проверяет, является ли токен числом или переменной
    bool isNumberOrVariable(const string& token) const;
};

#endif // POSTFIX_H
