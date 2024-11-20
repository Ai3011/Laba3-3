#ifndef AVL_H

#define AVL_H



#include <iostream>

#include <fstream>

#include <stdexcept>



using namespace std;



// Класс для узла AVL-дерева

class AVLNode {

public:

    int key;           // Ключ (значение) узла

    AVLNode* left;     // Указатель на левое поддерево

    AVLNode* right;    // Указатель на правое поддерево

    int height;        // Высота узла



    // Конструктор узла

    AVLNode(int key) : key(key), left(nullptr), right(nullptr), height(1) {}

};



// Класс для узла очереди

class QueueNode {

public:

    AVLNode* treeNode;  // Указатель на узел дерева

    QueueNode* next;    // Указатель на следующий элемент очереди



    // Конструктор узла очереди

    QueueNode(AVLNode* node) : treeNode(node), next(nullptr) {}

};



// Класс самописной очереди

class QueueForAvl {

public:

    QueueNode* front;    // Начало очереди

    QueueNode* rear;     // Конец очереди

    int count;           // Счетчик узлов в очереди



    // Конструктор очереди

    QueueForAvl() : front(nullptr), rear(nullptr), count(0) {}



    // Проверка, пуста ли очередь

    bool isEmpty() const {

        return count == 0;  // Проверяем по счетчику

    }



    // Добавление узла дерева в очередь

    void enqueue(AVLNode* node) {

        QueueNode* newNode = new QueueNode(node);

        if (rear == nullptr) {

            front = rear = newNode;

        } else {

            rear->next = newNode;

            rear = newNode;

        }

        count++;

    }



    // Удаление узла из очереди и возвращение его

    AVLNode* dequeue() {

        if (isEmpty()) return nullptr;



        QueueNode* temp = front;

        AVLNode* result = front->treeNode;

        front = front->next;



        if (front == nullptr) {

            rear = nullptr;

        }



        delete temp;

        count--;

        return result;

    }



    // Метод получения размера очереди

    int size() const {

        return count;

    }

};



// Класс для работы с AVL-деревом

class AVLTree {

public:

    AVLNode* root;



    // Конструктор дерева

    AVLTree() : root(nullptr) {}



    // Создание нового узла

    AVLNode* createNode(int key) {

        return new AVLNode(key);

    }



    // Поиск элемента по ключу

    AVLNode* find(AVLNode* node, int key) const {

        if (node == nullptr || node->key == key)

            return node;

        if (key < node->key)

            return find(node->left, key);

        return find(node->right, key);

    }



    // Высота узла

    int height(AVLNode* node) const {

        return node ? node->height : 0;

    }



    // Баланс узла

    int balanceFactor(AVLNode* node) const {

        return height(node->right) - height(node->left);

    }



    // Обновление высоты узла

    void updateHeight(AVLNode* node) {

        int leftHeight = height(node->left);

        int rightHeight = height(node->right);

        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    }



    // Правый поворот

    AVLNode* rotateRight(AVLNode* p) {

        AVLNode* q = p->left;

        p->left = q->right;

        q->right = p;

        updateHeight(p);

        updateHeight(q);

        return q;

    }



    // Левый поворот

    AVLNode* rotateLeft(AVLNode* q) {

        AVLNode* p = q->right;

        q->right = p->left;

        p->left = q;

        updateHeight(q);

        updateHeight(p);

        return p;

    }



    // Балансировка узла

    AVLNode* balance(AVLNode* node) {

        updateHeight(node);

        if (balanceFactor(node) == 2) {

            if (balanceFactor(node->right) < 0)

                node->right = rotateRight(node->right);

            return rotateLeft(node);

        }

        if (balanceFactor(node) == -2) {

            if (balanceFactor(node->left) > 0)

                node->left = rotateLeft(node->left);

            return rotateRight(node);

        }

        return node;

    }



    // Вставка узла в дерево

    AVLNode* insert(AVLNode* node, int key) {

        if (node == nullptr)

            return createNode(key);



        if (key < node->key)

            node->left = insert(node->left, key);

        else

            node->right = insert(node->right, key);



        return balance(node);

    }



    // Поиск минимального узла

    AVLNode* findMin(AVLNode* node) const {

        return node->left ? findMin(node->left) : node;

    }



    // Удаление минимального узла

    AVLNode* removeMin(AVLNode* node) {

        if (!node->left)

            return node->right;



        node->left = removeMin(node->left);

        return balance(node);

    }



    // Удаление узла с ключом

    AVLNode* remove(AVLNode* node, int key) {

        if (node == nullptr)

            return nullptr;



        if (key < node->key)

            node->left = remove(node->left, key);

        else if (key > node->key)

            node->right = remove(node->right, key);

        else {

            AVLNode* left = node->left;

            AVLNode* right = node->right;

            delete node;

            if (!right)

                return left;

            AVLNode* min = findMin(right);

            min->right = removeMin(right);

            min->left = left;

            return balance(min);

        }

        return balance(node);

    }



    // Очистка дерева

    void clear(AVLNode*& node) {

        if (node) {

            clear(node->left);

            clear(node->right);

            delete node;

            node = nullptr;

        }

    }



    // Сохранение дерева в файл

    void saveToFile(AVLNode*& node, ofstream& file) const {

        if (!file.is_open()) {

            throw runtime_error("Error: Unable to open file for writing.");

        }

        if (node) {

            file << node->key << " ";

            saveToFile(node->left, file);

            saveToFile(node->right, file);

        }

    }



    // Загрузка дерева из файла

    AVLNode* loadFromFile(AVLNode*& node, ifstream& file) {

        clear(node);

        int key;

        while (file >> key) {

            node = insert(node, key);

        }

        return node;

    }



    // Печать дерева по уровням

    void printByLevels() const {

        if (!root) {

            cout << "Дерево пустое." << endl;

            return;

        }



        QueueForAvl q;

        q.enqueue(root);



        while (!q.isEmpty()) {

            int levelSize = q.size();

            bool hasNodes = false;



            for (int i = 0; i < levelSize; ++i) {

                AVLNode* currentNode = q.dequeue();

                if (currentNode) {

                    cout << currentNode->key << "\t";

                    hasNodes = true;

                    q.enqueue(currentNode->left);

                    q.enqueue(currentNode->right);

                } else {

                    cout << "-\t";

                    q.enqueue(nullptr);

                    q.enqueue(nullptr);

                }

            }



            if (!hasNodes) break;



            cout << endl;

        }

    }

        // Сохранение узла в бинарный файл

    void saveNodeToBinaryFile(AVLNode* node, ofstream& file) const {

        if (node) {

            file.write(reinterpret_cast<const char*>(&node->key), sizeof(node->key));

            saveNodeToBinaryFile(node->left, file);

            saveNodeToBinaryFile(node->right, file);

        } else {

            int nullMarker = -1;  // Маркер, обозначающий отсутствие узла

            file.write(reinterpret_cast<const char*>(&nullMarker), sizeof(nullMarker));

        }

    }



    // Сохранение дерева в бинарный файл

    void saveToBinaryFile(const string& filename) const {

        ofstream file(filename, ios::binary);

        if (!file.is_open()) {

            throw runtime_error("Error: Unable to open file for writing.");

        }

        saveNodeToBinaryFile(root, file);

        file.close();

    }



    // Загрузка узла из бинарного файла

    AVLNode* loadNodeFromBinaryFile(ifstream& file) {

        int key;

        if (!file.read(reinterpret_cast<char*>(&key), sizeof(key))) {

            return nullptr;  // Ошибка чтения

        }

        if (key == -1) {  // Если встретился маркер отсутствия узла

            return nullptr;

        }



        AVLNode* node = createNode(key);

        node->left = loadNodeFromBinaryFile(file);

        node->right = loadNodeFromBinaryFile(file);

        updateHeight(node);  // Обновление высоты после загрузки

        return node;

    }



    // Загрузка дерева из бинарного файла

    void loadFromBinaryFile(const string& filename) {

        ifstream file(filename, ios::binary);

        if (!file.is_open()) {

            throw runtime_error("Error: Unable to open file for reading.");

        }

        clear(root);  // Очистка текущего дерева перед загрузкой

    root = loadNodeFromBinaryFile(file);

    file.close();

}





    

};



#endif
