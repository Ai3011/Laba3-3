#ifndef LIST_H 
#define LIST_H 
 
#include <iostream> 
#include <fstream> 
#include <stdexcept> 
#include <string> 
 
using namespace std; 
 
// Узел односвязного списка 
class Node { 
public: 
    string data;  // Данные узла 
    Node* next;   // Указатель на следующий узел 
 
    // Конструктор для инициализации узла 
    Node(const string& data) : data(data), next(nullptr) {} 
}; 
 
// Односвязный список 
class LinkedList { 
private: 
    Node* head;  // Указатель на первый узел (голову) списка 
    Node* tail;  // Указатель на последний узел (хвост) списка 
 
public: 
    // Конструктор: инициализация пустого списка 
    LinkedList() : head(nullptr), tail(nullptr) {} 
 
    // Деструктор: освобождение памяти 
    ~LinkedList() { 
        clear(); 
    } 
 
    // Добавление элемента в начало списка 
    void addHead(const string& element) { 
        Node* newNode = new Node(element); 
        newNode->next = head; 
        head = newNode; 
        if (!tail) tail = head; 
    } 
 
    // Добавление элемента в конец списка 
    void addTail(const string& element) { 
        Node* newNode = new Node(element); 
        if (tail) { 
            tail->next = newNode; 
        } else { 
            head = newNode; 
        } 
        tail = newNode; 
    } 
 
    // Удаление головы списка 
    void removeHead() { 
        if (!head) return; 
        Node* temp = head; 
        head = head->next; 
        if (!head) tail = nullptr; 
        delete temp; 
    } 
 
    // Удаление хвоста списка 
    void removeTail() { 
        if (!head) return; 
        if (head == tail) { 
            delete head; 
            head = tail = nullptr; 
            return; 
        } 
        Node* current = head; 
        while (current->next != tail) { 
            current = current->next; 
        } 
        delete tail; 
        tail = current; 
        tail->next = nullptr; 
    } 
 
    // Вывод содержимого списка 
    void read() const { 
        Node* current = head; 
        size_t index = 0; 
        while (current) { 
            cout << index++ << ": " << current->data << endl; 
            current = current->next; 
        } 
    } 
 
    // Поиск элемента по значению с выводом индекса 
    int find(const string& element) const { 
        Node* current = head; 
        int index = 0; 
        while (current) { 
            if (current->data == element) return index; 
            current = current->next; 
            ++index; 
        } 
        return -1; 
    } 
 
    // Удаление элемента по значению 
    bool removeByValue(const string& value) { 
        Node* current = head; 
        Node* previous = nullptr; 
 
        while (current) { 
            if (current->data == value) { 
                if (previous) { 
                    previous->next = current->next; 
                } else { 
                    head = current->next; 
                } 
                if (current == tail) { 
                    tail = previous; 
                } 
                delete current; 
                return true; 
            } 
            previous = current; 
            current = current->next; 
        } 
        return false; 
    } 
 
    // Загрузка данных из файла 
    void loadFromFile(const string& filename) { 
        clear(); 
        ifstream file(filename); 
        if (!file.is_open()) throw runtime_error("Unable to open file"); 
        string line; 
        while (getline(file, line)) { 
            addTail(line); 
        } 
        file.close(); 
    } 
 
    // Сохранение данных в файл 
    void saveToFile(const string& filename) const { 
        ofstream file(filename); 
        if (!file.is_open()) throw runtime_error("Unable to open file"); 
        Node* current = head; 
        while (current) { 
            file << current->data << endl; 
            current = current->next; 
        } 
        file.close(); 
    } 
 
    // Очистка всего списка 
    void clear() { 
        while (head) { 
            removeHead(); 
        } 
    } 
 
    // Получение текущей длины списка 
    size_t length() const {
        size_t count = 0; 
        Node* current = head; 
        while (current) { 
            ++count; 
            current = current->next; 
        } 
        return count; 
    } 
 
    // Проверка на пустоту списка 
    bool isEmpty() const { 
        return head == nullptr; 
    } 
    // Сериализация в бинарный файл
    void serializeBinary(const string& filename) const {
        ofstream file(filename, ios::binary); // Открытие файла в бинарном режиме
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for serialization");
        }

        Node* current = head;
        while (current) {
            size_t dataSize = current->data.size();
            file.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize)); // Запись размера строки
            file.write(current->data.c_str(), dataSize); // Запись строки
            current = current->next;
        }

        file.close();
    }

    // Десериализация из бинарного файла
    void deserializeBinary(const string& filename) {
        ifstream file(filename, ios::binary); // Открытие файла в бинарном режиме
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for deserialization");
        }

        clear(); // Очистка списка перед загрузкой данных

        size_t dataSize;
        while (file.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize))) {
            string data(dataSize, '\0');
            file.read(&data[0], dataSize); // Чтение строки из файла
            addTail(data); // Добавление строки в конец списка
        }

        file.close();
    }
};
 
#endif // LIST_H
