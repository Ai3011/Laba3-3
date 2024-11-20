#include <gtest/gtest.h>
#include <fstream>
#include <stdexcept>
#include "List.h" // Подключаем ваш заголовочный файл с реализацией списка

// Тестирование добавления элемента в начало списка
TEST(LinkedListTest, AddHead) {
    LinkedList list;
    list.addHead("Element1");
    list.addHead("Element2");

    EXPECT_EQ(list.length(), 2);
    EXPECT_EQ(list.find("Element1"), 1);
    EXPECT_EQ(list.find("Element2"), 0);
}

// Тестирование добавления элемента в конец списка
TEST(LinkedListTest, AddTail) {
    LinkedList list;
    list.addTail("Element1");
    list.addTail("Element2");

    EXPECT_EQ(list.length(), 2);
    EXPECT_EQ(list.find("Element1"), 0);
    EXPECT_EQ(list.find("Element2"), 1);
}

// Тестирование удаления головы списка
TEST(LinkedListTest, RemoveHead) {
    LinkedList list;
    list.addHead("Element1");
    list.addHead("Element2");
    
    list.removeHead();

    EXPECT_EQ(list.length(), 1);
    EXPECT_EQ(list.find("Element1"), 0);
    EXPECT_EQ(list.find("Element2"), -1); // Элемент удален
}

// Тестирование удаления хвоста списка
TEST(LinkedListTest, RemoveTail) {
    LinkedList list;
    list.addTail("Element1");
    list.addTail("Element2");

    list.removeTail();

    EXPECT_EQ(list.length(), 1);
    EXPECT_EQ(list.find("Element1"), 0);
    EXPECT_EQ(list.find("Element2"), -1); // Элемент удален
}

// Тестирование удаления элемента по значению
TEST(LinkedListTest, RemoveByValue) {
    LinkedList list;
    list.addHead("Element1");
    list.addHead("Element2");
    
    EXPECT_TRUE(list.removeByValue("Element1"));
    EXPECT_EQ(list.length(), 1);
    EXPECT_EQ(list.find("Element1"), -1);
    EXPECT_EQ(list.find("Element2"), 0);
    
    EXPECT_FALSE(list.removeByValue("Element3")); // Элемент не найден
}

// Тестирование загрузки и сохранения данных в/из файла
TEST(LinkedListTest, SaveLoadFromFile) {
    LinkedList list;
    list.addHead("Element1");
    list.addTail("Element2");
    
    list.saveToFile("test.txt");

    LinkedList newList;
    newList.loadFromFile("test.txt");

    EXPECT_EQ(newList.length(), 2);
    EXPECT_EQ(newList.find("Element1"), 0);
    EXPECT_EQ(newList.find("Element2"), 1);
}

// Тестирование сериализации и десериализации в бинарный файл
TEST(LinkedListTest, SerializeDeserializeBinary) {
    LinkedList list;
    list.addHead("Element1");
    list.addTail("Element2");

    // Сериализация в бинарный файл
    list.serializeBinary("test.bin");

    LinkedList newList;
    // Десериализация из бинарного файла
    newList.deserializeBinary("test.bin");

    EXPECT_EQ(newList.length(), 2);
    EXPECT_EQ(newList.find("Element1"), 0);
    EXPECT_EQ(newList.find("Element2"), 1);
}

// Тестирование метода clear
TEST(LinkedListTest, Clear) {
    LinkedList list;
    list.addHead("Element1");
    list.addTail("Element2");
    
    list.clear();
    
    EXPECT_EQ(list.length(), 0);
    EXPECT_TRUE(list.isEmpty());
}

// Тестирование метода isEmpty
TEST(LinkedListTest, IsEmpty) {
    LinkedList list;
    EXPECT_TRUE(list.isEmpty());

    list.addHead("Element1");
    EXPECT_FALSE(list.isEmpty());

    list.clear();
    EXPECT_TRUE(list.isEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
