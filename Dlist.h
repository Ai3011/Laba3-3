#include <iostream>

#include <fstream>

#include <stdexcept>

#include <string>

using namespace std;



struct DoubleNode {

    string data;

    DoubleNode* next;

    DoubleNode* prev;



    DoubleNode(const string& data) : data(data), next(nullptr), prev(nullptr) {}

};



struct DoublyLinkedList {

    DoubleNode* head;

    DoubleNode* tail;



    DoublyLinkedList() : head(nullptr), tail(nullptr) {}



    ~DoublyLinkedList() {

        clear();

    }



    void addHead(const string& element) {

        DoubleNode* newNode = new DoubleNode(element);

        newNode->next = head;

        if (head) 

            head->prev = newNode;

        head = newNode;

        if (!tail) 

            tail = head;

    }



    void addTail(const string& element) {

        DoubleNode* newNode = new DoubleNode(element);

        if (tail) {

            tail->next = newNode;

            newNode->prev = tail;

        } else {

            head = newNode;

        }

        tail = newNode;

    }



    void removeHead() {

    if (!head) return;  // Если список пуст, ничего не делаем



    DoubleNode* temp = head;

    head = head->next;  // Перемещаем указатель на первый элемент



    if (head) {

        head->prev = nullptr;  // Если новый первый элемент существует, сбрасываем его предыдущий указатель

    } else {

        tail = nullptr;  // Если список стал пустым, сбрасываем хвост

    }



    delete temp;  // Удаляем старую голову

    }      







    void removeTail() {

        if (!tail) return;

        DoubleNode* temp = tail;

        tail = tail->prev;

        if (tail) tail->next = nullptr;

        else head = nullptr;

        delete temp;

    }



    void read() const {

        DoubleNode* current = head;

        size_t index = 0;

        while (current) {

            cout << index++ << ": " << current->data << endl;

            current = current->next;

        }

    }



    int find(const std::string& value) const {

    int index = 0;

    DoubleNode* current = head;

    while (current) {

        if (current->data == value) {

            return index;

        }

        current = current->next;

        ++index;

    }

    return -1;  // Если элемент не найден

    }







    bool removeValue(const string& value) {

        if (!head)

            return false;



        DoubleNode* current = head;

        while (current) {

            if (current->data == value) {

                if (current->prev) {

                    current->prev->next = current->next;

                } else {

                    head = current->next;

                }

                if (current->next) {

                    current->next->prev = current->prev;

                } else {

                    tail = current->prev;

                }

                delete current;

                return true;

            }

            current = current->next;

        }

        return false;

    }



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



    void saveToFile(const string& filename) const {

        ofstream file(filename);

        if (!file.is_open()) 

            throw runtime_error("Unable to open file");

        DoubleNode* current = head;

        while (current) {

            file << current->data << endl;

            current = current->next;

        }

        file.close();

    }



    void saveToBinaryFile(const string& filename) const {

        ofstream file(filename, ios::binary);

        if (!file.is_open()) 

            throw runtime_error("Unable to open file for binary saving");



        DoubleNode* current = head;

        while (current) {

            size_t length = current->data.size();

            file.write(reinterpret_cast<char*>(&length), sizeof(size_t));

            file.write(current->data.c_str(), length);

            current = current->next;

        }



        file.close();

    }



    void loadFromBinaryFile(const string& filename) {

        clear();

        ifstream file(filename, ios::binary);

        if (!file.is_open()) 

            throw runtime_error("Unable to open file for binary loading");



        size_t length = 0;

        while (file.read(reinterpret_cast<char*>(&length), sizeof(size_t))) {

            string data(length, '\0');

            file.read(&data[0], length);

            addTail(data);

        }



        file.close();

    }



    void clear() {

        while (head) {

            removeHead();

        }

    }

};

