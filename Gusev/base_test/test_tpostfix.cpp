#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

// Тест создания объекта TPostfix с допустимым выражением
TEST(TPostfix, canCreatePostfix) {
    // Проверка на создание объекта без исключений для простого выражения
    ASSERT_NO_THROW(TPostfix p("0"));
}

// Тест создания объекта TPostfix с правильными скобками
TEST(TPostfix, canCreatePostfixOkBrackets) {
    // Проверка на создание объекта с правильной расставленностью скобок
    ASSERT_NO_THROW(TPostfix p("(1 + 1) * ((8)) + (2*(-1))"));
}

// Тест создания объекта TPostfix с некорректными скобками
TEST(TPostfix, cantCreatePostfixInvalidBrackets) {
    // Проверка на создание объекта с некорректно расставленными скобками (недостающая или лишняя скобка)
    ASSERT_ANY_THROW(TPostfix p("1) + 23 ("));
}

// Тест получения инфиксного выражения как вектора строк
TEST(TPostfix, canGetInfix) {
    TPostfix p("x1 + x2 + x3");
    vector<string> infix{ "x1", "+", "x2", "+", "x3" };
    // Проверка, что инфиксное выражение возвращается как вектор строк
    EXPECT_EQ(infix, p.GetInfix());
}

// Тест получения инфиксного выражения как строки
TEST(TPostfix, canGetUnfixString) {
    TPostfix p("x1 + x2 + 3");
    // Проверка, что инфиксное выражение возвращается как строка
    EXPECT_EQ("x1 + x2 + 3 ", p.getInfixExpression());
}

// Тест преобразования инфиксного выражения в постфиксное
TEST(TPostfix, canGetPostfix) {
    TPostfix p("x1 + x2 + 3");
    vector<string> postfix{ "x1", "x2", "+", "3", "+" };
    // Проверка, что постфиксное выражение возвращается как вектор строк
    EXPECT_EQ(postfix, p.GetPostfix());
}

// Тест получения постфиксного выражения как строки
TEST(TPostfix, canGetStringPostfix) {
    TPostfix p("(a + b * c / e - d)");
    // Проверка, что постфиксное выражение возвращается как строка
    EXPECT_EQ("a b c * e / + d - ", p.getPostfixExpression());
}

// Тест преобразования выражения с операциями в постфиксное выражение
TEST(TPostfix, canGetPostfixWithExpressions) {
    TPostfix p("a*(b-c)");
    vector<string> postfix{ "a", "b", "c", "-", "*" };
    // Проверка, что постфиксное выражение возвращается правильно для заданного выражения
    EXPECT_EQ(postfix, p.GetPostfix());
}

// Тест вычисления арифметического выражения с операцией сложения
TEST(TPostfix, canCalculateArithmeticExpressionWithPlus) {
    TPostfix p("a + b + 3");
    p.setVariableValue("a", 1);  // Устанавливаем значение переменной "a"
    p.setVariableValue("b", 2);  // Устанавливаем значение переменной "b"
    // Проверка, что результат вычисления выражения равен 1 + 2 + 3
    EXPECT_EQ(1 + 2 + 3, p.evaluate());
}

// Тест вычисления арифметического выражения с операцией вычитания
TEST(TPostfix, canCalculateArithmeticExpressionWithMinus) {
    TPostfix p("a - b - 3");
    p.setVariableValue("a", -1);  // Устанавливаем значение переменной "a"
    p.setVariableValue("b", -2);  // Устанавливаем значение переменной "b"
    // Проверка, что результат вычисления выражения равен -1 - (-2) - 3
    EXPECT_EQ(-1 - (-2) - 3, p.evaluate());
}

// Тест вычисления арифметического выражения с операцией умножения
TEST(TPostfix, canCalculateArithmeticExpressionWithMult) {
    TPostfix p("a * b * 3");
    p.setVariableValue("a", 10.0 / 3);  // Устанавливаем значение переменной "a"
    p.setVariableValue("b", -1);        // Устанавливаем значение переменной "b"
    // Проверка, что результат вычисления выражения равен (10 / 3) * (-1) * 3
    EXPECT_EQ(double(10) / 3 * (-1) * 3, p.evaluate());
}

// Тест вычисления арифметического выражения с операцией деления
TEST(TPostfix, canCalculateArithmeticExpressionWithDiv) {
    TPostfix p("a / b / 1.5");
    p.setVariableValue("a", 10.0);  // Устанавливаем значение переменной "a"
    p.setVariableValue("b", 1);     // Устанавливаем значение переменной "b"
    // Проверка, что результат вычисления выражения равен 10 / 1 / 1.5
    EXPECT_EQ(10.0 / 1 / 1.5, p.evaluate());
}
