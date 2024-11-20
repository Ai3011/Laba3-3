#include <gtest/gtest.h>
#include "Dlist.h"  // Включение заголовочного файла, где объявлен класс DoublyLinkedList

// Тест на добавление элемента в начало списка
TEST(DoublyLinkedListTest, AddHeadTest) {
    DoublyLinkedList list;

    // Добавление элементов в начало списка
    list.addHead("first");
    list.addHead("second");

    // Проверка содержимого списка
    EXPECT_EQ(list.find("second"), 0);  // "second" должен быть первым
    EXPECT_EQ(list.find("first"), 1);   // "first" должен быть вторым
}

// Тест на добавление элемента в конец списка
TEST(DoublyLinkedListTest, AddTailTest) {
    DoublyLinkedList list;

    // Добавление элементов в конец списка
    list.addTail("first");
    list.addTail("second");

    // Проверка содержимого списка
    EXPECT_EQ(list.find("first"), 0);   // "first" должен быть первым
    EXPECT_EQ(list.find("second"), 1);  // "second" должен быть вторым
}

// Тест на удаление головы списка
TEST(DoublyLinkedListTest, RemoveHeadTest) {
    DoublyLinkedList list;
    list.addHead("Element1");
    list.addHead("Element2");
    
    list.removeHead();

    EXPECT_EQ(list.find("Element1"), 0);
    EXPECT_EQ(list.find("Element2"), -1); // Элемент удален
}

//Тест на удаление хвоста списка
TEST(DoublyLinkedListTest, RemoveTailTest) {
    DoublyLinkedList list;
    list.addHead("first");
    list.addTail("second");

    list.removeTail();  // Удаление последнего элемента

    EXPECT_EQ(list.find("second"), -1);  // "second" должен быть удален
    EXPECT_EQ(list.find("first"), 0);   // "first" остается на месте
}

// Тест на поиск элемента в списке
TEST(DoublyLinkedListTest, FindTest) {
    DoublyLinkedList list;
    list.addHead("first");
    list.addTail("second");

    EXPECT_EQ(list.find("first"), 0);   // "first" на первом месте
    EXPECT_EQ(list.find("second"), 1);  // "second" на втором месте
    EXPECT_EQ(list.find("third"), -1);  // "third" не найден
}

// Тест на сериализацию (сохранение в бинарный файл)
TEST(DoublyLinkedListTest, SaveToBinaryFileTest) {
    DoublyLinkedList list;
    list.addHead("first");
    list.addTail("second");

    // Сохранение в бинарный файл
    const std::string filename = "test_binary.bin";
    list.saveToBinaryFile(filename);

    // Проверка, что файл существует
    std::ifstream file(filename, std::ios::binary);
    ASSERT_TRUE(file.is_open()) << "File should be created";
    file.close();

    // Очистка
    std::remove(filename.c_str());
}

// Тест на десериализацию (загрузка из бинарного файла)
TEST(DoublyLinkedListTest, LoadFromBinaryFileTest) {
    DoublyLinkedList list;
    list.addHead("first");
    list.addTail("second");

    // Сохранение в бинарный файл
    const std::string filename = "test_binary.bin";
    list.saveToBinaryFile(filename);

    // Новый список для загрузки данных
    DoublyLinkedList newList;
    newList.loadFromBinaryFile(filename);

    // Проверка загрузки данных
    EXPECT_EQ(newList.find("first"), 0);  // "first" должен быть первым
    EXPECT_EQ(newList.find("second"), 1); // "second" должен быть вторым

    // Очистка
    std::remove(filename.c_str());
}

// Тест на удаление элемента по значению
TEST(DoublyLinkedListTest, RemoveValueTest) {
    DoublyLinkedList list;
    list.addHead("first");
    list.addTail("second");
    list.addTail("third");

    EXPECT_TRUE(list.removeValue("second"));  // "second" должен быть удален
    EXPECT_EQ(list.find("second"), -1);      // "second" не найден
    EXPECT_EQ(list.find("first"), 0);        // "first" остался на месте
    EXPECT_EQ(list.find("third"), 1);        // "third" на втором месте

    EXPECT_FALSE(list.removeValue("nonexistent"));  // Элемент "nonexistent" не существует
}

// Тест на очистку списка
TEST(DoublyLinkedListTest, ClearTest) {
    DoublyLinkedList list;
    list.addHead("first");
    list.addTail("second");

    list.clear();  // Очистка списка

    EXPECT_EQ(list.find("first"), -1);   // "first" должен быть удален
    EXPECT_EQ(list.find("second"), -1);  // "second" должен быть удален
}

// Тест на загрузку данных из файла
TEST(DoublyLinkedListTest, LoadFromFileTest) {
    DoublyLinkedList list;
    const std::string filename = "test_file.txt";

    // Запись данных в файл
    {
        std::ofstream file(filename);
        file << "first" << std::endl;
        file << "second" << std::endl;
        file << "third" << std::endl;
    }

    // Загрузка данных из файла
    list.loadFromFile(filename);

    // Проверка содержимого списка
    EXPECT_EQ(list.find("first"), 0);   // "first" на первом месте
    EXPECT_EQ(list.find("second"), 1);  // "second" на втором месте
    EXPECT_EQ(list.find("third"), 2);   // "third" на третьем месте

    // Очистка
    std::remove(filename.c_str());
}
