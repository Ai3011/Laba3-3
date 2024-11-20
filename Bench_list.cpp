#include <benchmark/benchmark.h>
#include "List.h" // Подключаем заголовочный файл с реализацией списка

// Бенчмарк для добавления элемента в начало списка
static void BM_AddHead(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов в начало
        for (int i = 0; i < 10000; ++i) {
            list.addHead("Element" + std::to_string(i));
        }
    }
}
BENCHMARK(BM_AddHead);

// Бенчмарк для добавления элемента в конец списка
static void BM_AddTail(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов в конец
        for (int i = 0; i < 10000; ++i) {
            list.addTail("Element" + std::to_string(i));
        }
    }
}
BENCHMARK(BM_AddTail);

// Бенчмарк для удаления головы списка
static void BM_RemoveHead(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов в начало
        for (int i = 0; i < 10000; ++i) {
            list.addHead("Element" + std::to_string(i));
        }
        // Удаление головы 10 000 раз
        for (int i = 0; i < 10000; ++i) {
            list.removeHead();
        }
    }
}
BENCHMARK(BM_RemoveHead);

// Бенчмарк для удаления хвоста списка
static void BM_RemoveTail(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов в конец
        for (int i = 0; i < 10000; ++i) {
            list.addTail("Element" + std::to_string(i));
        }
        // Удаление хвоста 10 000 раз
        for (int i = 0; i < 10000; ++i) {
            list.removeTail();
        }
    }
}
BENCHMARK(BM_RemoveTail);

// Бенчмарк для удаления элемента по значению
static void BM_RemoveByValue(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            list.addTail("Element" + std::to_string(i));
        }
        // Удаление 10 000 элементов по значению
        for (int i = 0; i < 10000; ++i) {
            list.removeByValue("Element" + std::to_string(i));
        }
    }
}
BENCHMARK(BM_RemoveByValue);

// Бенчмарк для поиска элемента
static void BM_Find(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            list.addTail("Element" + std::to_string(i));
        }
        // Поиск элемента
        list.find("Element5000");
    }
}
BENCHMARK(BM_Find);

// Бенчмарк для сохранения данных в файл
static void BM_SaveToFile(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            list.addTail("Element" + std::to_string(i));
        }
        // Сохранение в файл
        list.saveToFile("test.txt");
    }
}
BENCHMARK(BM_SaveToFile);

// Бенчмарк для загрузки данных из файла
static void BM_LoadFromFile(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Загрузка из файла
        list.loadFromFile("test.txt");
    }
}
BENCHMARK(BM_LoadFromFile);

// Бенчмарк для сериализации в бинарный файл
static void BM_SerializeBinary(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            list.addTail("Element" + std::to_string(i));
        }
        // Сериализация в бинарный файл
        list.serializeBinary("test.bin");
    }
}
BENCHMARK(BM_SerializeBinary);

// Бенчмарк для десериализации из бинарного файла
static void BM_DeserializeBinary(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Десериализация из бинарного файла
        list.deserializeBinary("test.bin");
    }
}
BENCHMARK(BM_DeserializeBinary);

// Бенчмарк для очистки списка
static void BM_Clear(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        // Добавление 10 000 элементов
        for (int i = 0; i < 10000; ++i) {
            list.addTail("Element" + std::to_string(i));
        }
        // Очистка списка
        list.clear();
    }
}
BENCHMARK(BM_Clear);

// Бенчмарк для проверки на пустоту списка
static void BM_IsEmpty(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.isEmpty();
        // Добавление элемента
        list.addHead("Element1");
        list.isEmpty();
    }
}
BENCHMARK(BM_IsEmpty);

// Регистрация всех бенчмарков
BENCHMARK_MAIN();
