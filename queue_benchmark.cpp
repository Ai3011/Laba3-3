#include <benchmark/benchmark.h>
#include "Queue.h"

// Бенчмарк на добавление элемента в очередь
static void BM_QueuePush(benchmark::State& state) {
    for (auto _ : state) {
        Queue queue;
        queue.push("element");
    }
}
BENCHMARK(BM_QueuePush);

// Бенчмарк на удаление элемента из очереди
static void BM_QueuePop(benchmark::State& state) {
    for (auto _ : state) {
        Queue queue;
        queue.push("element");
        try {
            // Проверка на пустоту перед удалением
            if (!queue.isEmpty()) {
                queue.pop();
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in BM_QueuePop: " << e.what() << std::endl;
        }
    }
}
BENCHMARK(BM_QueuePop);

// Бенчмарк на сериализацию данных в бинарный файл
static void BM_SaveToBinaryFile(benchmark::State& state) {
    Queue queue;
    for (int i = 0; i < 1000; ++i) {
        queue.push("element_" + std::to_string(i));
    }

    for (auto _ : state) {
        // Очистка старого файла перед записью
        std::remove("queue_test.bin");
        queue.saveToBinaryFile("queue_test.bin");
    }
}
BENCHMARK(BM_SaveToBinaryFile);

// Бенчмарк на десериализацию данных из бинарного файла
static void BM_LoadFromBinaryFile(benchmark::State& state) {
    Queue queue;
    queue.saveToBinaryFile("queue_test.bin");

    for (auto _ : state) {
        try {
            queue.loadFromBinaryFile("queue_test.bin");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in BM_LoadFromBinaryFile: " << e.what() << std::endl;
        }
    }
}
BENCHMARK(BM_LoadFromBinaryFile);

// Запуск бенчмарков
BENCHMARK_MAIN();
