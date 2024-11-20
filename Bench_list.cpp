#include <benchmark/benchmark.h>
#include "List.h" // Подключаем заголовочный файл с реализацией списка

// Бенчмарк для добавления элемента в начало списка
static void BM_AddHead(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addHead("Element");
    }
}
BENCHMARK(BM_AddHead);

// Бенчмарк для добавления элемента в конец списка
static void BM_AddTail(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addTail("Element");
    }
}
BENCHMARK(BM_AddTail);

// Бенчмарк для удаления головы списка
static void BM_RemoveHead(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addHead("Element1");
        list.addHead("Element2");
        list.removeHead();
    }
}
BENCHMARK(BM_RemoveHead);

// Бенчмарк для удаления хвоста списка
static void BM_RemoveTail(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addTail("Element1");
        list.addTail("Element2");
        list.removeTail();
    }
}
BENCHMARK(BM_RemoveTail);

// Бенчмарк для удаления элемента по значению
static void BM_RemoveByValue(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addHead("Element1");
        list.addTail("Element2");
        list.removeByValue("Element1");
    }
}
BENCHMARK(BM_RemoveByValue);

// Бенчмарк для поиска элемента
static void BM_Find(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addHead("Element1");
        list.addTail("Element2");
        list.find("Element1");
    }
}
BENCHMARK(BM_Find);

// Бенчмарк для сохранения данных в файл
static void BM_SaveToFile(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addHead("Element1");
        list.addTail("Element2");
        list.saveToFile("test.txt");
    }
}
BENCHMARK(BM_SaveToFile);

// Бенчмарк для загрузки данных из файла
static void BM_LoadFromFile(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.loadFromFile("test.txt");
    }
}
BENCHMARK(BM_LoadFromFile);

// Бенчмарк для сериализации в бинарный файл
static void BM_SerializeBinary(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addHead("Element1");
        list.addTail("Element2");
        list.serializeBinary("test.bin");
    }
}
BENCHMARK(BM_SerializeBinary);

// Бенчмарк для десериализации из бинарного файла
static void BM_DeserializeBinary(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.deserializeBinary("test.bin");
    }
}
BENCHMARK(BM_DeserializeBinary);

// Бенчмарк для очистки списка
static void BM_Clear(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.addHead("Element1");
        list.addTail("Element2");
        list.clear();
    }
}
BENCHMARK(BM_Clear);

// Бенчмарк для проверки на пустоту списка
static void BM_IsEmpty(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        list.isEmpty();
        list.addHead("Element1");
        list.isEmpty();
    }
}
BENCHMARK(BM_IsEmpty);

// Регистрация всех бенчмарков
BENCHMARK_MAIN();
