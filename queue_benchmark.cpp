#include <benchmark/benchmark.h>
#include "Queue.h"

// Бенчмарк на добавление элемента в очередь
static void BM_QueuePush(benchmark::State& state) {
    for (auto _ : state) {
        Queue queue;
        // Добавление 10 000 элементов в очередь
        for (int i = 0; i < 10000; ++i) {
            queue.push("element_" + std::to_string(i));
        }
    }
}
BENCHMARK(BM_QueuePush);

// Бенчмарк на удаление элемента из очереди
static void BM_QueuePop(benchmark::State& state) {
    for (auto _ : state) {
        Queue queue;
        // Добавление 10 000 элементов в очередь
        for (int i = 0; i < 10000; ++i) {
            queue.push("element_" + std::to_string(i));
        }
        // Удаление всех элементов из очереди
        while (!queue.isEmpty()) {
            queue.pop();
        }
    }
}
BENCHMARK(BM_QueuePop);

// Бенчмарк на проверку очереди на пустоту
static void BM_QueueIsEmpty(benchmark::State& state) {
    Queue queue;
    // Заполнение очереди 10 000 элементами
    for (int i = 0; i < 10000; ++i) {
        queue.push("element_" + std::to_string(i));
    }
    for (auto _ : state) {
        queue.isEmpty();
    }
}
BENCHMARK(BM_QueueIsEmpty);

// Бенчмарк на очистку очереди
static void BM_QueueClear(benchmark::State& state) {
    Queue queue;
    // Заполнение очереди 10 000 элементами
    for (int i = 0; i < 10000; ++i) {
        queue.push("element_" + std::to_string(i));
    }
    for (auto _ : state) {
        queue.clear();
    }
}
BENCHMARK(BM_QueueClear);

// Бенчмарк на сохранение данных в текстовый файл
static void BM_SaveToFile(benchmark::State& state) {
    Queue queue;
    // Заполнение очереди 10 000 элементами
    for (int i = 0; i < 10000; ++i) {
        queue.push("element_" + std::to_string(i));
    }
    for (auto _ : state) {
        queue.saveToFile("queue_test.txt");
    }
}
BENCHMARK(BM_SaveToFile);

// Бенчмарк на загрузку данных из текстового файла
static void BM_LoadFromFile(benchmark::State& state) {
    Queue queue;
    // Сначала сохраняем данные в текстовый файл
    for (int i = 0; i < 10000; ++i) {
        queue.push("element_" + std::to_string(i));
    }
    queue.saveToFile("queue_test.txt");
    for (auto _ : state) {
        queue.loadFromFile("queue_test.txt");
    }
}
BENCHMARK(BM_LoadFromFile);

// Бенчмарк на сериализацию данных в бинарный файл
static void BM_SaveToBinaryFile(benchmark::State& state) {
    Queue queue;
    // Заполнение очереди 10 000 элементами
    for (int i = 0; i < 10000; ++i) {
        queue.push("element_" + std::to_string(i));
    }
    for (auto _ : state) {
        queue.saveToBinaryFile("queue_test.bin");
    }
}
BENCHMARK(BM_SaveToBinaryFile);

// Бенчмарк на десериализацию данных из бинарного файла
static void BM_LoadFromBinaryFile(benchmark::State& state) {
    Queue queue;
    // Сначала сохраняем данные в бинарный файл
    for (int i = 0; i < 10000; ++i) {
        queue.push("element_" + std::to_string(i));
    }
    queue.saveToBinaryFile("queue_test.bin");
    for (auto _ : state) {
        queue.loadFromBinaryFile("queue_test.bin");
    }
}
BENCHMARK(BM_LoadFromBinaryFile);

// Запуск бенчмарков
BENCHMARK_MAIN();
