#include <benchmark/benchmark.h>
#include "Dlist.h" // Ваш заголовочный файл с реализацией двусвязного списка

// Бенчмарк для добавления элемента в начало списка
static void BM_AddHead(benchmark::State& state) {
    for (auto _ : state) {
        DoublyLinkedList list;
        // Добавление элемента в начало списка
        list.addHead("Element");
    }
}
BENCHMARK(BM_AddHead);

// Бенчмарк для добавления элемента в конец списка
static void BM_AddTail(benchmark::State& state) {
    for (auto _ : state) {
        DoublyLinkedList list;
        // Добавление элемента в конец списка
        list.addTail("Element");
    }
}
BENCHMARK(BM_AddTail);

// Бенчмарк для удаления элемента с головы списка
static void BM_RemoveHead(benchmark::State& state) {
    for (auto _ : state) {
        DoublyLinkedList list;
        // Заполнение списка 100 элементов
        for (int i = 0; i < 100; ++i) {
            list.addTail("Element " + std::to_string(i));
        }
        // Удаление всех элементов с головы списка
        while (list.head) {
            list.removeHead();
        }
    }
}
BENCHMARK(BM_RemoveHead);

// Бенчмарк для удаления элемента с хвоста списка
static void BM_RemoveTail(benchmark::State& state) {
    for (auto _ : state) {
        DoublyLinkedList list;
        // Заполнение списка 100 элементов
        for (int i = 0; i < 100; ++i) {
            list.addTail("Element " + std::to_string(i));
        }
        // Удаление всех элементов с хвоста списка
        while (list.tail) {
            list.removeTail();
        }
    }
}
BENCHMARK(BM_RemoveTail);

// Бенчмарк для поиска элемента в списке
static void BM_Find(benchmark::State& state) {
    for (auto _ : state) {
        DoublyLinkedList list;
        // Заполнение списка 100 элементов
        for (int i = 0; i < 100; ++i) {
            list.addTail("Element " + std::to_string(i));
        }
        // Поиск элемента в списке
        list.find("Element 50");
    }
}
BENCHMARK(BM_Find);

// Бенчмарк для удаления элемента по значению
static void BM_RemoveValue(benchmark::State& state) {
    for (auto _ : state) {
        DoublyLinkedList list;
        // Заполнение списка 100 элементов
        for (int i = 0; i < 100; ++i) {
            list.addTail("Element " + std::to_string(i));
        }
        // Удаление элемента по значению
        list.removeValue("Element 50");
    }
}
BENCHMARK(BM_RemoveValue);

// Запуск всех бенчмарков
BENCHMARK_MAIN();
