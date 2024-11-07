#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>

// Задаем максимальный размер стека
const int MaxStackSize = 100;

template <typename T>
class TStack {
private:
    T* elements;       // Указатель на массив элементов стека
    int maxSize;       // Максимальный размер стека
    int topIndex;      // Индекс верхнего элемента стека

public:
    // Конструктор с параметром начального размера стека
    // Принимает параметр initialSize для указания размера стека, по умолчанию равен 1
    explicit TStack(int initialSize = 1)
        : maxSize(initialSize), topIndex(-1) {  // Инициализация maxSize и topIndex
        if (maxSize < 1 || maxSize > MaxStackSize) {  // Проверка на допустимый размер
            throw std::out_of_range("Stack size must be between 1 and 100");
        }
        elements = new T[maxSize];  // Выделение памяти для массива элементов
    }

    // Запрещаем копирование и перемещение объектов стека
    TStack(const TStack<T>&) = delete;
    TStack(TStack<T>&&) = delete;
    TStack& operator=(const TStack<T>&) = delete;
    TStack& operator=(TStack<T>&&) = delete;

    // Деструктор освобождает память, занятую массивом элементов стека
    ~TStack() {
        delete[] elements;
    }

    // Проверка на пустоту стека
    bool isEmpty() const noexcept {
        return topIndex == -1;  // Если topIndex == -1, стек пуст
    }

    // Проверка на переполнение стека
    bool isFull() const noexcept {
        return topIndex == maxSize - 1;  // Если topIndex == maxSize - 1, стек полон
    }

    // Возвращает текущее количество элементов в стеке
    int currentSize() const noexcept {
        return topIndex + 1;  // Количество элементов = topIndex + 1 (нумерация с 0)
    }

    // Добавление элемента в стек
    void push(const T& item) {
        if (isFull()) {  // Если стек полон, выбрасываем исключение
            throw std::overflow_error("Stack is full");
        }
        elements[++topIndex] = item;  // Увеличиваем индекс и добавляем элемент
    }

    // Удаление и возврат верхнего элемента стека
    T pop() {
        if (isEmpty()) {  // Если стек пуст, выбрасываем исключение
            throw std::underflow_error("Stack is empty");
        }
        return elements[topIndex--];  // Возвращаем верхний элемент и уменьшаем индекс
    }

    // Возвращает верхний элемент стека (независимо от того, изменяется ли стек)
    T& top() {
        if (isEmpty()) {  // Если стек пуст, выбрасываем исключение
            throw std::underflow_error("Stack is empty");
        }
        return elements[topIndex];  // Возвращаем верхний элемент
    }

    // Константная версия метода top() для чтения верхнего элемента без изменений
    const T& top() const {
        if (isEmpty()) {  // Если стек пуст, выбрасываем исключение
            throw std::underflow_error("Stack is empty");
        }
        return elements[topIndex];  // Возвращаем верхний элемент (неизменяемый)
    }

    // Возвращает количество элементов в стеке
    int size() const noexcept {
        return topIndex + 1;  // Количество элементов = topIndex + 1
    }
};

#endif // __STACK_H__
