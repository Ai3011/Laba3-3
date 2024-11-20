#ifndef STACK_H

#define STACK_H



#include "List.h"

#include <fstream>  // Для работы с файлами

#include <stdexcept> // Для обработки исключений



class Stack {



private:

    LinkedList list; // Внутренний список для хранения элементов стека



public:

    // Конструктор по умолчанию

    Stack() = default;

    

    // Деструктор   

    ~Stack() = default;

    

    // Добавление элемента в стек

    void push(const std::string& element) {        

        list.addHead(element); // Добавляем элемент в начало списка (вершина стека)

    }

    

    // Удаление элемента из стека    

    void pop() {

        if (isEmpty()) {

            throw std::out_of_range("Стек пуст. Невозможно выполнить pop.");

        }

        list.removeHead(); // Удаляем элемент с вершины стека   

    }

    

    // Вывод содержимого стека

    void read() const {        

        list.read(); // Выводим элементы списка

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



    // Получение длины стека

    size_t length() const {

        return list.length();  

    }



    // Проверка, пуст ли стек

    bool isEmpty() const {

        return list.isEmpty();  

    }



    // Поиск элемента в стеке

    int find(const std::string& element) const {

        return list.find(element);  

    }



    void clear() {

        list.clear();

    }

};



#endif 

