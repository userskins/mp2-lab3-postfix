#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

// ���� �������� ������� TPostfix � ���������� ����������
TEST(TPostfix, canCreatePostfix) {
    // �������� �� �������� ������� ��� ���������� ��� �������� ���������
    ASSERT_NO_THROW(TPostfix p("0"));
}

// ���� �������� ������� TPostfix � ����������� ��������
TEST(TPostfix, canCreatePostfixOkBrackets) {
    // �������� �� �������� ������� � ���������� ���������������� ������
    ASSERT_NO_THROW(TPostfix p("(1 + 1) * ((8)) + (2*(-1))"));
}

// ���� �������� ������� TPostfix � ������������� ��������
TEST(TPostfix, cantCreatePostfixInvalidBrackets) {
    // �������� �� �������� ������� � ����������� �������������� �������� (����������� ��� ������ ������)
    ASSERT_ANY_THROW(TPostfix p("1) + 23 ("));
}

// ���� ��������� ���������� ��������� ��� ������� �����
TEST(TPostfix, canGetInfix) {
    TPostfix p("x1 + x2 + x3");
    vector<string> infix{ "x1", "+", "x2", "+", "x3" };
    // ��������, ��� ��������� ��������� ������������ ��� ������ �����
    EXPECT_EQ(infix, p.GetInfix());
}

// ���� ��������� ���������� ��������� ��� ������
TEST(TPostfix, canGetUnfixString) {
    TPostfix p("x1 + x2 + 3");
    // ��������, ��� ��������� ��������� ������������ ��� ������
    EXPECT_EQ("x1 + x2 + 3 ", p.getInfixExpression());
}

// ���� �������������� ���������� ��������� � �����������
TEST(TPostfix, canGetPostfix) {
    TPostfix p("x1 + x2 + 3");
    vector<string> postfix{ "x1", "x2", "+", "3", "+" };
    // ��������, ��� ����������� ��������� ������������ ��� ������ �����
    EXPECT_EQ(postfix, p.GetPostfix());
}

// ���� ��������� ������������ ��������� ��� ������
TEST(TPostfix, canGetStringPostfix) {
    TPostfix p("(a + b * c / e - d)");
    // ��������, ��� ����������� ��������� ������������ ��� ������
    EXPECT_EQ("a b c * e / + d - ", p.getPostfixExpression());
}

// ���� �������������� ��������� � ���������� � ����������� ���������
TEST(TPostfix, canGetPostfixWithExpressions) {
    TPostfix p("a*(b-c)");
    vector<string> postfix{ "a", "b", "c", "-", "*" };
    // ��������, ��� ����������� ��������� ������������ ��������� ��� ��������� ���������
    EXPECT_EQ(postfix, p.GetPostfix());
}

// ���� ���������� ��������������� ��������� � ��������� ��������
TEST(TPostfix, canCalculateArithmeticExpressionWithPlus) {
    TPostfix p("a + b + 3");
    p.setVariableValue("a", 1);  // ������������� �������� ���������� "a"
    p.setVariableValue("b", 2);  // ������������� �������� ���������� "b"
    // ��������, ��� ��������� ���������� ��������� ����� 1 + 2 + 3
    EXPECT_EQ(1 + 2 + 3, p.evaluate());
}

// ���� ���������� ��������������� ��������� � ��������� ���������
TEST(TPostfix, canCalculateArithmeticExpressionWithMinus) {
    TPostfix p("a - b - 3");
    p.setVariableValue("a", -1);  // ������������� �������� ���������� "a"
    p.setVariableValue("b", -2);  // ������������� �������� ���������� "b"
    // ��������, ��� ��������� ���������� ��������� ����� -1 - (-2) - 3
    EXPECT_EQ(-1 - (-2) - 3, p.evaluate());
}

// ���� ���������� ��������������� ��������� � ��������� ���������
TEST(TPostfix, canCalculateArithmeticExpressionWithMult) {
    TPostfix p("a * b * 3");
    p.setVariableValue("a", 10.0 / 3);  // ������������� �������� ���������� "a"
    p.setVariableValue("b", -1);        // ������������� �������� ���������� "b"
    // ��������, ��� ��������� ���������� ��������� ����� (10 / 3) * (-1) * 3
    EXPECT_EQ(double(10) / 3 * (-1) * 3, p.evaluate());
}

// ���� ���������� ��������������� ��������� � ��������� �������
TEST(TPostfix, canCalculateArithmeticExpressionWithDiv) {
    TPostfix p("a / b / 1.5");
    p.setVariableValue("a", 10.0);  // ������������� �������� ���������� "a"
    p.setVariableValue("b", 1);     // ������������� �������� ���������� "b"
    // ��������, ��� ��������� ���������� ��������� ����� 10 / 1 / 1.5
    EXPECT_EQ(10.0 / 1 / 1.5, p.evaluate());
}
