#include <gtest/gtest.h>
#include "Array.h"

// Тестирование конструктора и метода add
TEST(StringArrayTest, AddElement) {
    StringArray arr;
    arr.add("Hello");
    arr.add("World");

    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.get(0), "Hello");
    EXPECT_EQ(arr.get(1), "World");
}

// Тестирование метода insert
TEST(StringArrayTest, InsertElement) {
    StringArray arr;
    arr.add("Hello");
    arr.add("World");
    arr.insert(1, "Inserted");

    EXPECT_EQ(arr.length(), 3);
    EXPECT_EQ(arr.get(1), "Inserted");
}

// Тестирование метода remove
TEST(StringArrayTest, RemoveElement) {
    StringArray arr;
    arr.add("Hello");
    arr.add("World");
    arr.remove(0);

    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.get(0), "World");
}

// Тестирование метода replace
TEST(StringArrayTest, ReplaceElement) {
    StringArray arr;
    arr.add("Hello");
    arr.replace(0, "Replaced");

    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.get(0), "Replaced");
}

// Тестирование метода out_of_range
TEST(StringArrayTest, OutOfRange) {
    StringArray arr;
    arr.add("Hello");

    EXPECT_THROW(arr.get(1), std::out_of_range);
    EXPECT_THROW(arr.remove(1), std::out_of_range);
    EXPECT_THROW(arr.replace(1, "New Value"), std::out_of_range);
}

// Тестирование метода clear
TEST(StringArrayTest, ClearArray) {
    StringArray arr;
    arr.add("Hello");
    arr.add("World");
    arr.clear();

    EXPECT_EQ(arr.length(), 0);
}

// Тестирование метода loadFromFile
TEST(StringArrayTest, LoadFromFile) {
    StringArray arr;
    arr.add("Hello");
    arr.add("World");
    arr.saveToFile("test.txt");

    StringArray arrLoaded;
    arrLoaded.loadFromFile("test.txt");

    EXPECT_EQ(arrLoaded.length(), 2);
    EXPECT_EQ(arrLoaded.get(0), "Hello");
    EXPECT_EQ(arrLoaded.get(1), "World");
}

// Тестирование метода saveToFile
TEST(StringArrayTest, SaveToFile) {
    StringArray arr;
    arr.add("Hello");
    arr.add("World");
    arr.saveToFile("test.txt");

    // Проверка, что данные были сохранены в файл
    ifstream file("test.txt");
    ASSERT_TRUE(file.is_open());
    string line;
    getline(file, line);
    EXPECT_EQ(line, "Hello");
    getline(file, line);
    EXPECT_EQ(line, "World");
    file.close();
}

// Тестирование метода serializeBinary
TEST(StringArrayTest, SerializeBinary) {
    StringArray arr;
    arr.add("Hello");
    arr.add("World");
    arr.serializeBinary("test.bin");

    // Проверка, что данные были сериализованы
    ifstream file("test.bin", ios::binary);
    ASSERT_TRUE(file.is_open());

    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    EXPECT_EQ(size, 2); // Ожидаем, что в массиве 2 элемента

    size_t length;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    char* buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = '\0';
    EXPECT_EQ(string(buffer), "Hello");

    delete[] buffer;

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = '\0';
    EXPECT_EQ(string(buffer), "World");

    delete[] buffer;

    file.close();
}

// Тестирование метода deserializeBinary
TEST(StringArrayTest, DeserializeBinary) {
    StringArray arr;
    arr.add("Hello");
    arr.add("World");
    arr.serializeBinary("test.bin");

    StringArray arrLoaded;
    arrLoaded.deserializeBinary("test.bin");

    EXPECT_EQ(arrLoaded.length(), 2);
    EXPECT_EQ(arrLoaded.get(0), "Hello");
    EXPECT_EQ(arrLoaded.get(1), "World");
}

// Тестирование метода resize (косвенно через добавление элементов)
TEST(StringArrayTest, ResizeArray) {
    StringArray arr;

    // Добавляем больше элементов, чем начальная вместимость массива
    for (size_t i = 0; i < 20; ++i) {
        arr.add("Element " + to_string(i));
    }

    // Проверяем, что вместимость массива увеличена (мы можем только проверять размер)
    EXPECT_EQ(arr.length(), 20); // Ожидаем, что в массиве будет 20 элементов
    EXPECT_EQ(arr.get(0), "Element 0");
    EXPECT_EQ(arr.get(19), "Element 19");
}
