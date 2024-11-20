#include <benchmark/benchmark.h>
#include "Hash.h"  // Ваш заголовочный файл с HashTable
#include <string>

// Функция для вставки 10 000 элементов в таблицу
static void BM_Insert(benchmark::State& state) {
    for (auto _ : state) {
        HashTable hashTable;
        for (int i = 0; i < 10000; ++i) {
            hashTable.insert("key" + std::to_string(i), "value" + std::to_string(i));
        }
    }
}

// Функция для получения 10 000 элементов из таблицы
static void BM_Get(benchmark::State& state) {
    HashTable hashTable;
    // Вставляем 10 000 элементов заранее
    for (int i = 0; i < 10000; ++i) {
        hashTable.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    for (auto _ : state) {
        for (int i = 0; i < 10000; ++i) {
            benchmark::DoNotOptimize(hashTable.get("key" + std::to_string(i)));
        }
    }
}

// Функция для удаления 10 000 элементов из таблицы
static void BM_Remove(benchmark::State& state) {
    HashTable hashTable;
    // Вставляем 10 000 элементов заранее
    for (int i = 0; i < 10000; ++i) {
        hashTable.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    for (auto _ : state) {
        for (int i = 0; i < 10000; ++i) {
            hashTable.remove("key" + std::to_string(i));
        }
    }
}

// Функция для сохранения в файл и загрузки из файла 10 000 элементов
static void BM_SaveAndLoadFromFile(benchmark::State& state) {
    for (auto _ : state) {
        HashTable hashTable;
        // Вставляем 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            hashTable.insert("key" + std::to_string(i), "value" + std::to_string(i));
        }

        // Сохраняем в файл
        hashTable.saveToFileAndClear("test.txt");

        // Загружаем из файла
        HashTable newHashTable;
        newHashTable.loadFromFile("test.txt");
    }
}

// Функция для сохранения в бинарный файл и загрузки из него 10 000 элементов
static void BM_SaveAndLoadFromBinaryFile(benchmark::State& state) {
    for (auto _ : state) {
        HashTable hashTable;
        // Вставляем 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            hashTable.insert("key" + std::to_string(i), "value" + std::to_string(i));
        }

        // Сохраняем в бинарный файл
        hashTable.saveToBinaryFile("test_binary.dat");

        // Загружаем из бинарного файла
        HashTable newHashTable;
        newHashTable.loadFromBinaryFile("test_binary.dat");
    }
}

// Регистрируем бенчмарки
BENCHMARK(BM_Insert);
BENCHMARK(BM_Get);
BENCHMARK(BM_Remove);
BENCHMARK(BM_SaveAndLoadFromFile);
BENCHMARK(BM_SaveAndLoadFromBinaryFile);

// Запуск всех бенчмарков
BENCHMARK_MAIN();
