#include <benchmark/benchmark.h>
#include "Stack.h"

// Бенчмарк на добавление элемента в стек
static void BM_StackPush(benchmark::State& state) {
    for (auto _ : state) {
        Stack stack;
        stack.push("element");
    }
}
BENCHMARK(BM_StackPush);


// Бенчмарк на удаление элемента из стека
static void BM_StackPop(benchmark::State& state) {
    for (auto _ : state) {
        Stack stack;
        stack.push("element");
        try {
            if (!stack.isEmpty()) {
                stack.pop();
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in BM_StackPop: " << e.what() << std::endl;
        }
    }
}
BENCHMARK(BM_StackPop);

// Бенчмарк на очистку стека
static void BM_StackClear(benchmark::State& state) {
    for (auto _ : state) {
        Stack stack;
        for (int i = 0; i < 1000; ++i) {
            stack.push("element_" + std::to_string(i));
        }
        stack.clear();
    }
}
BENCHMARK(BM_StackClear);

// Бенчмарк на сериализацию данных в бинарный файл
static void BM_StackSaveToBinaryFile(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push("element_" + std::to_string(i));
    }

    for (auto _ : state) {
        std::remove("stack_test.bin"); // Очистка старого файла
        stack.saveToBinaryFile("stack_test.bin");
    }
}
BENCHMARK(BM_StackSaveToBinaryFile);

// Бенчмарк на десериализацию данных из бинарного файла
static void BM_StackLoadFromBinaryFile(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push("element_" + std::to_string(i));
    }
    stack.saveToBinaryFile("stack_test.bin");

    for (auto _ : state) {
        try {
            stack.loadFromBinaryFile("stack_test.bin");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in BM_StackLoadFromBinaryFile: " << e.what() << std::endl;
        }
    }
}
BENCHMARK(BM_StackLoadFromBinaryFile);

// Бенчмарк на сохранение стека в текстовый файл
static void BM_StackSaveToFile(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push("element_" + std::to_string(i));
    }

    for (auto _ : state) {
        std::remove("stack_test.txt"); // Очистка старого файла
        stack.saveToFile("stack_test.txt");
    }
}
BENCHMARK(BM_StackSaveToFile);

// Бенчмарк на загрузку стека из текстового файла
static void BM_StackLoadFromFile(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < 1000; ++i) {
        stack.push("element_" + std::to_string(i));
    }
    stack.saveToFile("stack_test.txt");

    for (auto _ : state) {
        try {
            stack.loadFromFile("stack_test.txt");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in BM_StackLoadFromFile: " << e.what() << std::endl;
        }
    }
}
BENCHMARK(BM_StackLoadFromFile);

// Запуск бенчмарков
BENCHMARK_MAIN();
