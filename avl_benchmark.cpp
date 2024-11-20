#include <benchmark/benchmark.h>
#include <cstdlib>
#include "AVL.h"  // Подключаем ваш класс AVL-дерева

// Генерация случайных чисел для вставки в дерево
void generateRandomNumbers(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000;  // Случайное число от 0 до 9999
    }
}

// Бенчмарки

// Вставка элементов
static void BM_Insert(benchmark::State& state) {
    for (auto _ : state) {
        AVLTree tree;
        int arr[1000];
        generateRandomNumbers(arr, 1000);
        
        // Вставляем элементы в дерево
        for (int i = 0; i < 1000; ++i) {
            tree.root = tree.insert(tree.root, arr[i]);
        }
        
    }
}
BENCHMARK(BM_Insert);

// Поиск элемента
static void BM_Find(benchmark::State& state) {
    for (auto _ : state) {
        AVLTree tree;
        int arr[1000];
        generateRandomNumbers(arr, 1000);
        
        // Вставляем элементы в дерево
        for (int i = 0; i < 1000; ++i) {
            tree.root = tree.insert(tree.root, arr[i]);
        }

        

        tree.find(tree.root, arr[500]);  // Поиск элемента с ключом из середины
    }
}
BENCHMARK(BM_Find);

// Удаление элемента
static void BM_Remove(benchmark::State& state) {
    for (auto _ : state) {
        AVLTree tree;
        int arr[1000];
        generateRandomNumbers(arr, 1000);
        
        // Вставляем элементы в дерево
        for (int i = 0; i < 1000; ++i) {
            tree.root = tree.insert(tree.root, arr[i]);
        }

        

        tree.root = tree.remove(tree.root, arr[500]);  // Удаление элемента
    }
}
BENCHMARK(BM_Remove);

// Поиск минимального узла
static void BM_FindMin(benchmark::State& state) {
    for (auto _ : state) {
        AVLTree tree;
        int arr[1000];
        generateRandomNumbers(arr, 1000);
        
        // Вставляем элементы в дерево
        for (int i = 0; i < 1000; ++i) {
            tree.root = tree.insert(tree.root, arr[i]);
        }

        tree.findMin(tree.root);  // Поиск минимального узла
    }
}
BENCHMARK(BM_FindMin);

// Удаление минимального узла
static void BM_RemoveMin(benchmark::State& state) {
    for (auto _ : state) {
        AVLTree tree;
        int arr[1000];
        generateRandomNumbers(arr, 1000);
        
        // Вставляем элементы в дерево
        for (int i = 0; i < 1000; ++i) {
            tree.root = tree.insert(tree.root, arr[i]);
        }

    
        tree.root = tree.removeMin(tree.root);  // Удаление минимального узла
    }
}
BENCHMARK(BM_RemoveMin);

BENCHMARK_MAIN();
