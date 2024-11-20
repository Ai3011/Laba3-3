#ifndef HASH_H

#define HASH_H



#include <iostream>

#include <fstream>

#include <string>

#include <stdexcept>

#include <cstring>



const int TABLE_SIZE = 100; // Размер таблицы хеширования



// Класс для элемента списка (узел)

class HNode {

public:

    std::string key;   // Ключ

    std::string value; // Значение

    HNode* next;       // Указатель на следующий элемент в списке (цепочке)

    

    // Конструктор для инициализации узла

    HNode(const std::string& key, const std::string& value, HNode* next = nullptr)

        : key(key), value(value), next(next) {}

};



// Класс для хеш-таблицы

class HashTable {

private:

    HNode** table; // Массив указателей на узлы (цепочки)



    // Хеш-функция

    unsigned hashFunction(const std::string& key) const {

        unsigned hash = 0;

        for (auto ch : key) {

            hash = (hash * 31 + ch) % TABLE_SIZE;

        }

        return hash;

    }



public:

    // Конструктор для инициализации хеш-таблицы

    HashTable() {

        table = new HNode*[TABLE_SIZE]();  // Инициализация массива указателей на null

    }



    // Деструктор для освобождения памяти

    ~HashTable() {

        clear();

    }



    // Вставка элемента в таблицу

    void insert(const std::string& key, const std::string& value) {

        unsigned index = hashFunction(key);

        if (get(key) != "") {

            std::cout << "This key is not unique.\n";

            return;

        }

        HNode* newNode = new HNode(key, value, table[index]);

        table[index] = newNode;

    }



    // Получение значения по ключу

    std::string get(const std::string& key) const {

        unsigned hashIndex = hashFunction(key);

        HNode* current = table[hashIndex];

        while (current) {

            if (current->key == key) {

                return current->value;

            }

            current = current->next;

        }

        return ""; // Если не найдено

    }



    // Удаление элемента по ключу

    void remove(const std::string& key) {

        unsigned index = hashFunction(key);

        HNode* curNode = table[index];

        HNode* prevNode = nullptr;



        while (curNode && curNode->key != key) {

            prevNode = curNode;

            curNode = curNode->next;

        }



        if (curNode == nullptr) {

            return;

        }



        if (prevNode) {

            prevNode->next = curNode->next;

        } else {

            table[index] = curNode->next;

        }



        delete curNode;

    }



    // Очистка таблицы

    void clear() {

        for (int i = 0; i < TABLE_SIZE; i++) {

            HNode* current = table[i];

            while (current) {

                HNode* temp = current;

                current = current->next;

                delete temp;

            }

            table[i] = nullptr;

        }

        delete[] table;

    }



    // Печать содержимого таблицы

    void print() const {

        for (int i = 0; i < TABLE_SIZE; i++) {

            HNode* curNode = table[i];

            if (curNode) {

                std::cout << "Index " << i << " - ";

                while (curNode) {

                    std::cout << "[" << curNode->key << ": " << curNode->value << "] ";

                    curNode = curNode->next;

                }

                std::cout << std::endl;

            }

        }

    }



    // Сохранение содержимого в файл и очистка таблицы

    void saveToFileAndClear(const std::string& filename) {

        std::ofstream outFile(filename);

        if (!outFile) {

            throw std::runtime_error("Cannot open file for saving: " + filename);

        }



        for (int i = 0; i < TABLE_SIZE; i++) {

            HNode* curNode = table[i];

            while (curNode) {

                outFile << curNode->key << "=" << curNode->value << std::endl;

                curNode = curNode->next;

            }

        }



        outFile.close();

        clear();

        table = new HNode*[TABLE_SIZE]();  // Переинициализация таблицы

    }



    // Загрузка данных из файла

    void loadFromFile(const std::string& filename) {

        clear();

        table = new HNode*[TABLE_SIZE]();  // Переинициализация таблицы



        std::ifstream inFile(filename);

        if (!inFile) {

            throw std::runtime_error("Cannot open file for loading: " + filename);

        }



        std::string line;

        while (std::getline(inFile, line)) {

            if (line.empty()) continue;



            size_t pos = line.find('=');

            if (pos == std::string::npos) continue;



            std::string key = line.substr(0, pos);

            std::string value = line.substr(pos + 1);



            insert(key, value);

        }



        inFile.close();

    }



    // Сериализация в бинарный формат

    void saveToBinaryFile(const std::string& filename) {

        std::ofstream outFile(filename, std::ios::binary);

        if (!outFile) {

            throw std::runtime_error("Cannot open file for binary saving: " + filename);

        }



        for (int i = 0; i < TABLE_SIZE; i++) {

            HNode* curNode = table[i];

            while (curNode) {

                size_t keyLength = curNode->key.size();

                size_t valueLength = curNode->value.size();

                

                outFile.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));

                outFile.write(curNode->key.c_str(), keyLength);

                outFile.write(reinterpret_cast<const char*>(&valueLength), sizeof(valueLength));

                outFile.write(curNode->value.c_str(), valueLength);



                curNode = curNode->next;

            }

        }



        outFile.close();

    }



    void loadFromBinaryFile(const std::string& filename) {

    clear();

    table = new HNode*[TABLE_SIZE]();  // Переинициализация таблицы



    std::ifstream inFile(filename, std::ios::binary);

    if (!inFile) {

        throw std::runtime_error("Cannot open file for binary loading: " + filename);

    }



    try {

        while (inFile) {

            size_t keyLength, valueLength;

            inFile.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));

            if (inFile.eof()) break;  // Если достигнут конец файла, выходим



            if (inFile.fail()) {

                throw std::runtime_error("Failed to read key length from binary file");

            }



            std::string key(keyLength, '\0');

            inFile.read(&key[0], keyLength);

            if (inFile.fail()) {

                throw std::runtime_error("Failed to read key data from binary file");

            }



            inFile.read(reinterpret_cast<char*>(&valueLength), sizeof(valueLength));

            if (inFile.fail()) {

                throw std::runtime_error("Failed to read value length from binary file");

            }



            std::string value(valueLength, '\0');

            inFile.read(&value[0], valueLength);

            if (inFile.fail()) {

                throw std::runtime_error("Failed to read value data from binary file");

            }



            insert(key, value);

        }

    } catch (const std::exception& e) {

        throw std::runtime_error("Error during binary file loading: " + std::string(e.what()));

    }



    inFile.close();

}



};



#endif

