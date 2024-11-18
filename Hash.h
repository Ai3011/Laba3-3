#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

const int TABLE_SIZE = 100; // Размер таблицы хеширования

// Класс для элемента списка (узел)
class HNode {
public:
    string key;   // Ключ
    string value; // Значение
    HNode* next;       // Указатель на следующий элемент в списке (цепочке)
    
    // Конструктор для инициализации узла
    HNode(const string& key, const string& value, HNode* next = nullptr)
        : key(key), value(value), next(next) {}
};

// Класс для хеш-таблицы
class HashTable {
private:
    HNode** table; // Массив указателей на узлы (цепочки)

    // Хеш-функция
    unsigned hashFunction(const string& key) const {
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
    void insert(const string& key, const string& value) {
        unsigned index = hashFunction(key);
        if (get(key) != "") {
            cout << "This key is not unique.\n";
            return;
        }
        HNode* newNode = new HNode(key, value, table[index]);
        table[index] = newNode;
    }

    // Получение значения по ключу
    string get(const string& key) const {
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
    void remove(const string& key) {
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
                cout << "Index " << i << " - ";
                while (curNode) {
                    cout << "[" << curNode->key << ": " << curNode->value << "] ";
                    curNode = curNode->next;
                }
                cout << endl;
            }
        }
    }

    // Сохранение содержимого в файл и очистка таблицы
    void saveToFileAndClear(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            throw runtime_error("Cannot open file for saving: " + filename);
        }

        for (int i = 0; i < TABLE_SIZE; i++) {
            HNode* curNode = table[i];
            while (curNode) {
                outFile << curNode->key << "=" << curNode->value << endl;
                curNode = curNode->next;
            }
        }

        outFile.close();
        clear();
        table = new HNode*[TABLE_SIZE]();  // Переинициализация таблицы
    }

    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        clear();
        table = new HNode*[TABLE_SIZE]();  // Переинициализация таблицы

        ifstream inFile(filename);
        if (!inFile) {
            throw runtime_error("Cannot open file for loading: " + filename);
        }

        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            size_t pos = line.find('=');
            if (pos == string::npos) continue;

            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);


            insert(key, value);
        }

        inFile.close();
    }
};

#endif
