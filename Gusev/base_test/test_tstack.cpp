#include "stack.h"
#include <gtest.h>

// Тест на создание стека с положительной длиной
TEST(TStack, can_create_stack_with_positive_length) {
    // Проверка на создание стека с допустимым положительным размером
    ASSERT_NO_THROW(TStack<int> st(5));
}

// Тест на создание стека с отрицательной длиной
TEST(TStack, cant_create_stack_with_negative_length) {
    // Проверка, что при отрицательном размере стека выбрасывается исключение
    EXPECT_ANY_THROW(TStack<int> st(-1));
}

// Тест метода isEmpty для пустого стека
TEST(TStack, method_isEmpty_for_empty_stack_return_true) {
    TStack<int> st(5);
    // Проверка, что метод isEmpty возвращает true для пустого стека
    EXPECT_TRUE(st.isEmpty());
}

// Тест метода isEmpty для непустого стека
TEST(TStack, method_isEmpty_for_not_empty_stack_return_false) {
    TStack<int> st(5);
    st.push(1);
    // Проверка, что метод isEmpty возвращает false для непустого стека
    EXPECT_FALSE(st.isEmpty());
}

// Тест метода isFull для полного стека
TEST(TStack, method_isFull_for_full_stack_return_true) {
    TStack<int> st(5);
    for (int i = 0; i < 5; ++i) {
        st.push(1);
    }
    // Проверка, что метод isFull возвращает true для полного стека
    EXPECT_TRUE(st.isFull());
}

// Тест метода isFull для неполного стека
TEST(TStack, method_isFull_for_not_full_stack_return_false) {
    TStack<int> st(5);
    for (int i = 0; i < 4; ++i) {
        st.push(1);
    }
    // Проверка, что метод isFull возвращает false для неполного стека
    EXPECT_FALSE(st.isFull());
}

// Тест на получение текущего размера стека
TEST(TStack, can_get_current_size_of_stack) {
    TStack<int> st(10);
    for (int i = 0; i < 4; ++i) {
        st.push(1);
    }
    // Проверка, что метод currentSize возвращает правильный размер стека
    EXPECT_EQ(st.currentSize(), 4);
}

// Тест добавления элемента в неполный стек
TEST(TStack, can_push_element_into_not_full_stack) {
    TStack<int> st(5);
    // Проверка на возможность добавления элемента в неполный стек
    ASSERT_NO_THROW(st.push(1));
}

// Тест попытки добавить элемент в полный стек
TEST(TStack, cant_push_element_into_full_stack) {
    TStack<int> st(5);
    for (int i = 0; i < 5; ++i) {
        st.push(1);
    }
    // Проверка, что попытка добавления элемента в полный стек вызывает исключение
    ASSERT_ANY_THROW(st.push(1));
}

// Тест извлечения и получения элемента из непустого стека
TEST(TStack, can_pop_and_top_element_from_not_empty_stack) {
    TStack<int> st(3);
    st.push(1);
    // Проверка, что извлечение и получение элемента из непустого стека не вызывает ошибок
    ASSERT_NO_THROW(st.pop());
    st.push(1);
    ASSERT_NO_THROW(st.top());
}

// Тест попытки извлечения и получения элемента из пустого стека
TEST(TStack, cant_pop_and_top_element_from_empty_stack) {
    TStack<int> st(3);
    // Проверка, что извлечение и получение элемента из пустого стека вызывает исключение
    ASSERT_ANY_THROW(st.pop());
    ASSERT_ANY_THROW(st.top());
}

// Тест метода top для получения верхнего элемента
TEST(TStack, method_top_return_top_element) {
    TStack<int> st(3);
    st.push(147);
    // Проверка, что метод top возвращает правильный верхний элемент
    EXPECT_EQ(st.top(), 147);
}

// Тест уменьшения размера после извлечения элемента
TEST(TStack, method_pop_decrement_size) {
    TStack<int> st(10);
    for (int i = 0; i < 5; ++i) {
        st.push(1);
    }
    st.pop();
    // Проверка, что размер стека уменьшается после извлечения элемента
    EXPECT_EQ(st.currentSize(), 4);
}

// Тест, что метод top не изменяет размер стека
TEST(TStack, method_top_doesnt_change_size) {
    TStack<int> st(10);
    for (int i = 0; i < 5; ++i) {
        st.push(1);
    }
    st.top();
    // Проверка, что метод top не изменяет размер стека
    EXPECT_EQ(st.currentSize(), 5);
}
