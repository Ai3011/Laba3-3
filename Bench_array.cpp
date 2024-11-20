#include <benchmark/benchmark.h>
#include "Array.h"

// Бенчмарк для метода add (добавление элементов)
static void BM_AddElement(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }
    }
}
BENCHMARK(BM_AddElement);

// Бенчмарк для метода insert (вставка элементов)
static void BM_InsertElement(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }

        // Вставка элемента в середину массива
        arr.insert(5000, "Inserted Element");
    }
}
BENCHMARK(BM_InsertElement);

// Бенчмарк для метода remove (удаление элементов)
static void BM_RemoveElement(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }

        // Удаление всех элементов
        for (int i = 0; i < 10000; ++i) {
            arr.remove(0);
        }
    }
}
BENCHMARK(BM_RemoveElement);

// Бенчмарк для метода replace (замена элементов)
static void BM_ReplaceElement(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }

        // Замена элемента
        arr.replace(5000, "Replaced Element");
    }
}
BENCHMARK(BM_ReplaceElement);

// Бенчмарк для метода get (получение элемента)
static void BM_GetElement(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }

        // Получение элемента
        benchmark::DoNotOptimize(arr.get(5000));
    }
}
BENCHMARK(BM_GetElement);

// Бенчмарк для метода clear (очистка массива)
static void BM_ClearArray(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }

        // Очистка массива
        arr.clear();
    }
}
BENCHMARK(BM_ClearArray);

// Бенчмарк для метода loadFromFile (загрузка из файла)
static void BM_LoadFromFile(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }

        // Сохранение в файл
        arr.saveToFile("test.txt");

        // Загрузка из файла
        StringArray arrLoaded;
        arrLoaded.loadFromFile("test.txt");
    }
}
BENCHMARK(BM_LoadFromFile);

// Бенчмарк для метода saveToFile (сохранение в файл)
static void BM_SaveToFile(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }

        // Сохранение в файл
        arr.saveToFile("test.txt");
    }
}
BENCHMARK(BM_SaveToFile);

// Бенчмарк для метода serializeBinary (сериализация)
static void BM_SerializeBinary(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            arr.add("Element " + std::to_string(i));
        }

        // Сериализация в бинарный файл
        arr.serializeBinary("test.bin");
    }
}
BENCHMARK(BM_SerializeBinary);

// Бенчмарк для метода deserializeBinary (десериализация)
static void BM_DeserializeBinary(benchmark::State& state) {
    for (auto _ : state) {
        StringArray arr;
        // Сериализация в бинарный файл
        arr.add("Element 1");
        arr.add("Element 2");
        arr.serializeBinary("test.bin");

        // Десериализация из бинарного файла
        StringArray arrLoaded;
        arrLoaded.deserializeBinary("test.bin");
    }
}
BENCHMARK(BM_DeserializeBinary);

// Запуск всех бенчмарков
BENCHMARK_MAIN();
