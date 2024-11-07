#include "stack.h"
#include <gtest.h>

// ���� �� �������� ����� � ������������� ������
TEST(TStack, can_create_stack_with_positive_length) {
    // �������� �� �������� ����� � ���������� ������������� ��������
    ASSERT_NO_THROW(TStack<int> st(5));
}

// ���� �� �������� ����� � ������������� ������
TEST(TStack, cant_create_stack_with_negative_length) {
    // ��������, ��� ��� ������������� ������� ����� ������������� ����������
    EXPECT_ANY_THROW(TStack<int> st(-1));
}

// ���� ������ isEmpty ��� ������� �����
TEST(TStack, method_isEmpty_for_empty_stack_return_true) {
    TStack<int> st(5);
    // ��������, ��� ����� isEmpty ���������� true ��� ������� �����
    EXPECT_TRUE(st.isEmpty());
}

// ���� ������ isEmpty ��� ��������� �����
TEST(TStack, method_isEmpty_for_not_empty_stack_return_false) {
    TStack<int> st(5);
    st.push(1);
    // ��������, ��� ����� isEmpty ���������� false ��� ��������� �����
    EXPECT_FALSE(st.isEmpty());
}

// ���� ������ isFull ��� ������� �����
TEST(TStack, method_isFull_for_full_stack_return_true) {
    TStack<int> st(5);
    for (int i = 0; i < 5; ++i) {
        st.push(1);
    }
    // ��������, ��� ����� isFull ���������� true ��� ������� �����
    EXPECT_TRUE(st.isFull());
}

// ���� ������ isFull ��� ��������� �����
TEST(TStack, method_isFull_for_not_full_stack_return_false) {
    TStack<int> st(5);
    for (int i = 0; i < 4; ++i) {
        st.push(1);
    }
    // ��������, ��� ����� isFull ���������� false ��� ��������� �����
    EXPECT_FALSE(st.isFull());
}

// ���� �� ��������� �������� ������� �����
TEST(TStack, can_get_current_size_of_stack) {
    TStack<int> st(10);
    for (int i = 0; i < 4; ++i) {
        st.push(1);
    }
    // ��������, ��� ����� currentSize ���������� ���������� ������ �����
    EXPECT_EQ(st.currentSize(), 4);
}

// ���� ���������� �������� � �������� ����
TEST(TStack, can_push_element_into_not_full_stack) {
    TStack<int> st(5);
    // �������� �� ����������� ���������� �������� � �������� ����
    ASSERT_NO_THROW(st.push(1));
}

// ���� ������� �������� ������� � ������ ����
TEST(TStack, cant_push_element_into_full_stack) {
    TStack<int> st(5);
    for (int i = 0; i < 5; ++i) {
        st.push(1);
    }
    // ��������, ��� ������� ���������� �������� � ������ ���� �������� ����������
    ASSERT_ANY_THROW(st.push(1));
}

// ���� ���������� � ��������� �������� �� ��������� �����
TEST(TStack, can_pop_and_top_element_from_not_empty_stack) {
    TStack<int> st(3);
    st.push(1);
    // ��������, ��� ���������� � ��������� �������� �� ��������� ����� �� �������� ������
    ASSERT_NO_THROW(st.pop());
    st.push(1);
    ASSERT_NO_THROW(st.top());
}

// ���� ������� ���������� � ��������� �������� �� ������� �����
TEST(TStack, cant_pop_and_top_element_from_empty_stack) {
    TStack<int> st(3);
    // ��������, ��� ���������� � ��������� �������� �� ������� ����� �������� ����������
    ASSERT_ANY_THROW(st.pop());
    ASSERT_ANY_THROW(st.top());
}

// ���� ������ top ��� ��������� �������� ��������
TEST(TStack, method_top_return_top_element) {
    TStack<int> st(3);
    st.push(147);
    // ��������, ��� ����� top ���������� ���������� ������� �������
    EXPECT_EQ(st.top(), 147);
}

// ���� ���������� ������� ����� ���������� ��������
TEST(TStack, method_pop_decrement_size) {
    TStack<int> st(10);
    for (int i = 0; i < 5; ++i) {
        st.push(1);
    }
    st.pop();
    // ��������, ��� ������ ����� ����������� ����� ���������� ��������
    EXPECT_EQ(st.currentSize(), 4);
}

// ����, ��� ����� top �� �������� ������ �����
TEST(TStack, method_top_doesnt_change_size) {
    TStack<int> st(10);
    for (int i = 0; i < 5; ++i) {
        st.push(1);
    }
    st.top();
    // ��������, ��� ����� top �� �������� ������ �����
    EXPECT_EQ(st.currentSize(), 5);
}
