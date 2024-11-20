#include "AVL.h"
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>

// Проверка вставки узлов
TEST(AVLTreeTest, InsertNodes) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);

    EXPECT_EQ(tree.root->key, 10);
    EXPECT_EQ(tree.root->left->key, 5);
    EXPECT_EQ(tree.root->right->key, 20);
}

// Проверка баланса дерева после вставки
TEST(AVLTreeTest, TreeBalanceAfterInsert) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 30);

    EXPECT_EQ(tree.root->key, 20); // Корень должен быть 20 после балансировки
    EXPECT_EQ(tree.root->left->key, 10);
    EXPECT_EQ(tree.root->right->key, 30);
}

// Проверка удаления узлов
TEST(AVLTreeTest, DeleteNodes) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);

    tree.root = tree.remove(tree.root, 20);

    EXPECT_EQ(tree.root->key, 10);
    EXPECT_EQ(tree.root->left->key, 5);
    EXPECT_EQ(tree.root->right, nullptr);
}

// Проверка сохранения и загрузки в текстовый файл
TEST(AVLTreeTest, SaveAndLoadFromTextFile) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);

    std::ofstream file("tree.txt");
    tree.saveToFile(tree.root, file);
    file.close();

    AVLTree loadedTree;
    std::ifstream inputFile("tree.txt");
    loadedTree.root = loadedTree.loadFromFile(loadedTree.root, inputFile);
    inputFile.close();

    EXPECT_NE(loadedTree.root, nullptr);
    EXPECT_EQ(loadedTree.root->key, 10);
    EXPECT_EQ(loadedTree.root->left->key, 5);
    EXPECT_EQ(loadedTree.root->right->key, 20);
}

// Проверка сохранения и загрузки в бинарный файл
TEST(AVLTreeTest, SaveAndLoadFromBinaryFile) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);

    tree.saveToBinaryFile("tree.bin");

    AVLTree loadedTree;
    loadedTree.loadFromBinaryFile("tree.bin");

    EXPECT_NE(loadedTree.root, nullptr);
    EXPECT_EQ(loadedTree.root->key, 10);
    EXPECT_EQ(loadedTree.root->left->key, 5);
    EXPECT_EQ(loadedTree.root->right->key, 20);
}

// Проверка высоты дерева
TEST(AVLTreeTest, TreeHeight) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);

    EXPECT_EQ(tree.height(tree.root), 2);
}

TEST(AVLTreeTest, PrintByLevels) {
    // Создаем экземпляр дерева
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 5);
    tree.root = tree.insert(tree.root, 20);

    // Захват стандартного вывода
    testing::internal::CaptureStdout();
    
    // Печатаем дерево по уровням
    tree.printByLevels();

    // Получаем вывод в строку
    std::string actualOutput = testing::internal::GetCapturedStdout();

    // Для отладки выводим фактический вывод
    std::cout << "Actual Output:\n" << actualOutput << "\n";

    // Ожидаемый результат
    std::string expectedOutput = "10\t\n5\t20\t\n-\t-\t-\t-\t";

    // Сравнение реального вывода с ожидаемым
    EXPECT_EQ(actualOutput, expectedOutput);
}

// Проверка очистки дерева
TEST(AVLTreeTest, ClearTree) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);

    tree.clear(tree.root);

    EXPECT_EQ(tree.root, nullptr);
}

// Проверка вставки нескольких узлов и корректности баланса дерева
TEST(AVLTreeTest, InsertMultipleNodes) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);
    tree.root = tree.insert(tree.root, 15);
    tree.root = tree.insert(tree.root, 25);
    
    EXPECT_EQ(tree.root->key, 10);
    EXPECT_EQ(tree.root->left->key, 5);
    EXPECT_EQ(tree.root->right->key, 20);
    EXPECT_EQ(tree.root->right->left->key, 15);
    EXPECT_EQ(tree.root->right->right->key, 25);
}

// Проверка работы с пустым деревом
TEST(AVLTreeTest, PrintEmptyTree) {
    AVLTree tree;

    testing::internal::CaptureStdout();
    tree.printByLevels();
    std::string actualOutput = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "Дерево пустое.\n";
    EXPECT_EQ(actualOutput, expectedOutput);
}

// Проверка правого поворота
TEST(AVLTreeTest, RightRotation) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 5);
    tree.root = tree.insert(tree.root, 20);
    
    // После вставки дерева 10-5-20 должно быть выполнено правый поворот на узле 10.
    // Новый корень должен быть 5, и его правый ребенок должен быть 10.
    tree.root = tree.rotateRight(tree.root);

    EXPECT_EQ(tree.root->key, 5);     // Новый корень должен быть 5
    EXPECT_EQ(tree.root->right->key, 10); // Правый ребенок корня должен быть 10
    EXPECT_EQ(tree.root->right->right->key, 20); // Правый ребенок правого ребенка должен быть 20
}

// Проверка поиска минимального узла
TEST(AVLTreeTest, FindMinNode) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);
    tree.root = tree.insert(tree.root, 15);
    tree.root = tree.insert(tree.root, 2);
    
    // Минимальный узел должен быть 2, так как это самое левое значение
    EXPECT_EQ(tree.findMin(tree.root)->key, 2);
}

// Проверка удаления минимального узла
TEST(AVLTreeTest, DeleteMinNode) {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 5);

    // Минимальный узел на данный момент - 5
    tree.root = tree.removeMin(tree.root); // Удаляем минимальный узел

    // После удаления минимального узла, корень должен быть 10
    EXPECT_EQ(tree.root->key, 10);
    // Левый потомок корня теперь должен быть nullptr (так как 5 был удален)
    EXPECT_EQ(tree.root->left, nullptr);
}
