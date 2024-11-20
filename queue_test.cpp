#include "gtest/gtest.h"
#include "Queue.h"
#include <fstream>
#include <stdexcept>

using namespace std;

// Тест на добавление элемента в очередь
TEST(QueueTest, PushTest) {
    Queue queue;
    queue.push("first");
    queue.push("second");
    
    EXPECT_FALSE(queue.isEmpty());
}

// Тест на удаление элемента из очереди
TEST(QueueTest, PopTest) {
    Queue queue;
    queue.push("first");
    queue.push("second");

    queue.pop();
    EXPECT_FALSE(queue.isEmpty());
    
    // Попробуем удалить ещё один элемент
    queue.pop();
    EXPECT_TRUE(queue.isEmpty());
}

// Тест на ошибку при попытке удалить элемент из пустой очереди
TEST(QueueTest, PopEmptyQueueTest) {
    Queue queue;
    EXPECT_THROW(queue.pop(), runtime_error);
}

// Тест на проверку, пуста ли очередь
TEST(QueueTest, IsEmptyTest) {
    Queue queue;
    EXPECT_TRUE(queue.isEmpty());
    queue.push("element");
    EXPECT_FALSE(queue.isEmpty());
}

// Тест на очистку очереди
TEST(QueueTest, ClearTest) {
    Queue queue;
    queue.push("first");
    queue.push("second");
    queue.clear();
    EXPECT_TRUE(queue.isEmpty());
}

// Тест на сохранение и загрузку из текстового файла
TEST(QueueTest, SaveLoadFromFileTest) {
    Queue queue;
    queue.push("first");
    queue.push("second");
    queue.saveToFile("queue_test.txt");

    Queue newQueue;
    newQueue.loadFromFile("queue_test.txt");

    EXPECT_FALSE(newQueue.isEmpty());
}

// Тест на сериализацию и десериализацию в бинарный файл
TEST(QueueTest, SaveLoadFromBinaryFileTest) {
    Queue queue;
    queue.push("first");
    queue.push("second");
    queue.saveToBinaryFile("queue_test.bin");

    Queue newQueue;
    newQueue.loadFromBinaryFile("queue_test.bin");

    EXPECT_FALSE(newQueue.isEmpty());
}
