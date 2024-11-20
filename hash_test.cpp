#include <gtest/gtest.h>
#include "Hash.h"
#include <fstream>

// Тест для вставки и получения значений
TEST(HashTableTest, InsertAndGet) {
    HashTable hashTable;

    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");

    EXPECT_EQ(hashTable.get("key1"), "value1");
    EXPECT_EQ(hashTable.get("key2"), "value2");
    EXPECT_EQ(hashTable.get("key3"), "");  // Не существующий ключ
}

// Тест для удаления элемента
TEST(HashTableTest, Remove) {
    HashTable hashTable;

    hashTable.insert("key1", "value1");
    hashTable.remove("key1");

    EXPECT_EQ(hashTable.get("key1"), "");  // После удаления должно быть пусто
}


// Тест для сохранения и загрузки из текстового файла
TEST(HashTableTest, SaveAndLoadFromFile) {
    HashTable hashTable;

    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");

    // Сохраняем в файл
    hashTable.saveToFileAndClear("test.txt");

    // Загружаем из файла
    HashTable newHashTable;
    newHashTable.loadFromFile("test.txt");

    EXPECT_EQ(newHashTable.get("key1"), "value1");
    EXPECT_EQ(newHashTable.get("key2"), "value2");
}

// Тест для сериализации в бинарный файл и десериализации
TEST(HashTableTest, SaveAndLoadFromBinaryFile) {
    HashTable hashTable;

    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");

    // Сохраняем в бинарный файл
    hashTable.saveToBinaryFile("test_binary.dat");

    // Загружаем из бинарного файла
    HashTable newHashTable;
    newHashTable.loadFromBinaryFile("test_binary.dat");

    EXPECT_EQ(newHashTable.get("key1"), "value1");
    EXPECT_EQ(newHashTable.get("key2"), "value2");
}

// Тест для уникальности ключей
TEST(HashTableTest, InsertDuplicateKey) {
    HashTable hashTable;

    hashTable.insert("key1", "value1");
    hashTable.insert("key1", "value2");  // Попытка вставить с тем же ключом, но с другим значением

    EXPECT_EQ(hashTable.get("key1"), "value1");  // Ключ должен иметь старое значение
}

// Тест для обработки ошибки при открытии файла
TEST(HashTableTest, FileError) {
    HashTable hashTable;

    EXPECT_THROW(hashTable.loadFromFile("non_existent_file.txt"), std::runtime_error);
    EXPECT_THROW(hashTable.saveToFileAndClear("non_writable_directory/test.txt"), std::runtime_error);
}

// Тест для правильности загрузки из бинарного файла с неправильным форматом
TEST(HashTableTest, BinaryFileError) {
    HashTable hashTable;

    // Создаем неверный бинарный файл (например, с поврежденными данными)
    std::ofstream outFile("test_binary_error.dat", std::ios::binary);
    outFile.write("Invalid data", 12);
    outFile.close();

    EXPECT_THROW(hashTable.loadFromBinaryFile("test_binary_error.dat"), std::runtime_error);
}
