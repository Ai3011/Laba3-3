#ifndef QUEUE_H

#define QUEUE_H



#include "List.h"

#include <stdexcept>

#include <string>

#include <fstream>

#include <iostream>



using namespace std;



class Queue {

private:

    LinkedList list; // Внутренний список для хранения элементов



public:

    // Конструктор по умолчанию

    Queue() = default;



    // Деструктор

    ~Queue() = default;



    // Добавление элемента в конец очереди

    void push(const string& element) {

        list.addTail(element);

    }



    // Удаление элемента из начала очереди

    void pop() {

        if (isEmpty())

            throw runtime_error("Queue is empty");

        list.removeHead();

    }



    // Проверка, пуста ли очередь

    bool isEmpty() const {

        return list.isEmpty();

    }



    // Очистка очереди

    void clear() {

        list.clear();

    }



    // Вывод содержимого очереди

    void read() const {

        list.read();

    }



    // Загрузка данных из файла

    void loadFromFile(const string& filename) {

        list.loadFromFile(filename);

    }



    // Сохранение данных в файл

    void saveToFile(const string& filename) const {

        list.saveToFile(filename);

    }



    // Сериализация очереди в бинарный файл

    void saveToBinaryFile(const string& filename) const {

    ofstream outFile(filename, ios::binary);

    if (!outFile)

        throw runtime_error("Failed to open file for writing");



    // Записываем количество элементов в очереди

    size_t size = list.length();  // Получаем размер списка

    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size_t));



    // Записываем все элементы очереди

    LinkedList::Node* current = list.getNode();  // Получаем первый узел

    while (current) {

        size_t length = current->data.length();  // Длина строки

        outFile.write(reinterpret_cast<const char*>(&length), sizeof(size_t));  // Записываем длину строки

        outFile.write(current->data.c_str(), length);  // Записываем саму строку

        current = current->next;

    }



    outFile.close();

    }





    // Десериализация очереди из бинарного файла

    void loadFromBinaryFile(const string& filename) {

        ifstream inFile(filename, ios::binary);

        if (!inFile)

            throw runtime_error("Failed to open file for reading");



        // Читаем количество элементов в очереди

        size_t size = 0;

        inFile.read(reinterpret_cast<char*>(&size), sizeof(size_t));



        // Восстанавливаем очередь

        for (size_t i = 0; i < size; ++i) {

            size_t length = 0;

            inFile.read(reinterpret_cast<char*>(&length), sizeof(size_t));  // Читаем длину строки



            string element(length, '\0');

            inFile.read(&element[0], length);  // Читаем саму строку



            push(element);  // Добавляем строку в очередь

        }



        inFile.close();

    }

};



#endif

