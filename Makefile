# Переменные для путей к заголовочным файлам и библиотекам
GTEST_DIR = /usr/include/gtest
BENCHMARK_DIR = /usr/include/benchmark
LIB_DIR = /usr/lib/x86_64-linux-gnu

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++20 -I$(GTEST_DIR) -I$(BENCHMARK_DIR) -I. -w -fprofile-arcs -ftest-coverage
LDFLAGS = -L$(LIB_DIR) -lgtest -lgtest_main -pthread -lgcov -lbenchmark

# Источники и объекты для тестов и бенчмарков
TEST_SOURCES = array_test.cpp list_test.cpp dlist_test.cpp queue_test.cpp stack_test.cpp avl_test.cpp hash_test.cpp
BENCHMARK_SOURCES = array_benchmark.cpp list_benchmark.cpp dlist_benchmark.cpp queue_benchmark.cpp stack_benchmark.cpp avl_benchmark.cpp hash_benchmark.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
BENCHMARK_OBJECTS = $(BENCHMARK_SOURCES:.cpp=.o)
EXEC_TEST = array_test list_test dlist_test queue_test stack_test avl_test hash_test
EXEC_ARRAY_BENCHMARK = ArrayBenchmark
EXEC_LIST_BENCHMARK = ListBenchmark
EXEC_DLIST_BENCHMARK = DListBenchmark
EXEC_QUEUE_BENCHMARK = QueueBenchmark
EXEC_STACK_BENCHMARK = StackBenchmark
EXEC_AVL_BENCHMARK = AvlBenchmark
EXEC_HASH_BENCHMARK = HashBenchmark

# Директория для покрытия
COVERAGE_DIR = coverage

# Правила для компиляции и линковки
$(EXEC_TEST): $(TEST_OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEC_ARRAY_BENCHMARK): array_benchmark.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEC_LIST_BENCHMARK): list_benchmark.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEC_DLIST_BENCHMARK): dlist_benchmark.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEC_QUEUE_BENCHMARK): queue_benchmark.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEC_STACK_BENCHMARK): stack_benchmark.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEC_AVL_BENCHMARK): avl_benchmark.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXEC_HASH_BENCHMARK): hash_benchmark.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

# Тесты
test: $(EXEC_TEST)
	@echo "Запуск тестов..."
	./array_test
	./list_test
	./dlist_test
	./queue_test
	./stack_test
	./avl_test
	./hash_test

# Бенчмарки
benchmark: $(EXEC_ARRAY_BENCHMARK) $(EXEC_LIST_BENCHMARK) $(EXEC_DLIST_BENCHMARK) $(EXEC_QUEUE_BENCHMARK) $(EXEC_STACK_BENCHMARK) $(EXEC_AVL_BENCHMARK) $(EXEC_HASH_BENCHMARK)
	@echo "Запуск бенчмарков..."
	./ArrayBenchmark
	./ListBenchmark
	./DListBenchmark
	./QueueBenchmark
	./StackBenchmark
	./AvlBenchmark
	./HashBenchmark

# Запуск тестов и генерация отчета о покрытии
coverage: clean $(EXEC_TEST)
	@echo "Запуск тестов для сбора данных покрытия..."
	# Запуск тестов
	./array_test
	./list_test
	./dlist_test
	./queue_test
	./stack_test
	./avl_test
	./hash_test

	# Создание директории для покрытия, если она не существует
	mkdir -p $(COVERAGE_DIR)

	# Сбор покрытия с использованием lcov
	lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info --ignore-errors inconsistent --rc geninfo_unexecuted_blocks=1

	# Фильтрация системных файлов и библиотек
	lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' --output-file $(COVERAGE_DIR)/coverage_filtered.info

	# Генерация пофайловых HTML-отчетов
	genhtml $(COVERAGE_DIR)/coverage_filtered.info --output-directory $(COVERAGE_DIR) --demangle-cpp --show-details

	@echo "HTML-отчет о покрытии создан в $(COVERAGE_DIR)/index.html"

# Очистка скомпилированных файлов и отчетов о покрытии
clean:
	rm -f $(EXEC_TEST) $(TEST_OBJECTS) $(EXEC_ARRAY_BENCHMARK) $(EXEC_LIST_BENCHMARK) $(EXEC_DLIST_BENCHMARK) $(EXEC_QUEUE_BENCHMARK) $(EXEC_STACK_BENCHMARK) $(EXEC_AVL_BENCHMARK) $(EXEC_HASH_BENCHMARK) $(BENCHMARK_OBJECTS) *.gcda *.gcno
	rm -rf $(COVERAGE_DIR)
