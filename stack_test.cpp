#include <gtest/gtest.h>
#include <fstream>
#include <stdexcept>
#include "Stack.h"  // Подключаем заголовочный файл с реализацией стека

// Тестирование добавления элемента в стек
TEST(StackTest, Push) {
    Stack stack;
    stack.push("Element1");
    stack.push("Element2");

    // Проверяем, что элементы добавлены в стек
    EXPECT_NO_THROW(stack.push("Element3"));
}

// Тестирование удаления элемента из стека
TEST(StackTest, Pop) {
    Stack stack;
    stack.push("Element1");
    stack.push("Element2");

    stack.pop();  // Удаляем элемент с вершины стека

    // Проверяем, что стек содержит только один элемент
    EXPECT_EQ(stack.length(), 1);  // Проверяем длину стека
}

// Тестирование очистки стека
TEST(StackTest, Clear) {
    Stack stack;
    stack.push("Element1");
    stack.push("Element2");

    stack.clear();

    // Проверяем, что стек очищен
    EXPECT_EQ(stack.length(), 0);  // Проверяем длину стека
    EXPECT_TRUE(stack.isEmpty());  // Проверяем, пуст ли стек
}

// Тестирование сохранения и загрузки стека в/из файла
TEST(StackTest, SaveLoadFromFile) {
    Stack stack;
    stack.push("Element1");
    stack.push("Element2");
    
    stack.saveToFile("stack_test.txt");

    Stack newStack;
    newStack.loadFromFile("stack_test.txt");

    EXPECT_FALSE(newStack.isEmpty());
}

// Тестирование сериализации и десериализации в бинарный файл
TEST(StackTest, SerializeDeserializeBinary) {
    Stack stack;
    stack.push("Element1");
    stack.push("Element2");

    // Сериализация в бинарный файл
    stack.saveToBinaryFile("stack_test.bin");

    Stack newStack;
    // Десериализация из бинарного файла
    newStack.loadFromBinaryFile("stack_test.bin");

    // Проверяем, что данные загрузились корректно
    EXPECT_EQ(newStack.length(), 2);
    EXPECT_EQ(newStack.find("Element1"), 0);  // Проверка поиска первого элемента
    EXPECT_EQ(newStack.find("Element2"), 1);  // Проверка поиска второго элемента
}

// Тестирование метода isEmpty
TEST(StackTest, IsEmpty) {
    Stack stack;
    EXPECT_TRUE(stack.isEmpty());  // Стек должен быть пуст

    stack.push("Element1");
    EXPECT_FALSE(stack.isEmpty());  // После добавления элемента стек не пуст

    stack.clear();
    EXPECT_TRUE(stack.isEmpty());  // После очистки стек снова пуст
}

