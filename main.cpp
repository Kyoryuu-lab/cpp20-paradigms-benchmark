#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <chrono>
#include <algorithm>
#include <cctype>

// Набор допустимых символов
constexpr char CHARSET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

// ==========================================
// 1. КЛАССИЧЕСКИЙ ВАРИАНТ (обычные циклы)
// ==========================================
struct ClassicCompare {
    bool operator()(char a, char b) const {
        return std::tolower(static_cast<unsigned char>(a)) >
               std::tolower(static_cast<unsigned char>(b));
    }
};

void run_classic(size_t n, std::mt19937& rng) {
    std::cout << "\n--- 1. Klassische Variante ---\n";
    std::uniform_int_distribution<size_t> dist(0, sizeof(CHARSET) - 2);

    // Заполнение вектора циклом
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<char> vec;
    vec.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        vec.push_back(CHARSET[dist(rng)]);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto fill_vec_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "Fill vector used time was: " << fill_vec_time << " us\n";
    std::cout << "Vector:\n";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
    }
    std::cout << "\n";

    // Заполнение очереди циклом
    auto t3 = std::chrono::high_resolution_clock::now();
    std::priority_queue<char, std::vector<char>, ClassicCompare> pq;
    for (size_t i = 0; i < vec.size(); ++i) {
        pq.push(vec[i]);
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    auto fill_queue_time = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "Fill queue used time was: " << fill_queue_time << " us\n";
    std::cout << "Queue:\n";
    while (!pq.empty()) {
        std::cout << pq.top();
        pq.pop();
    }
    std::cout << "\n";
}

// ==========================================
// 2. ФУНКЦИОНАЛЬНЫЙ ВАРИАНТ (функторы + STL)
// ==========================================
class CharGenerator {
    std::mt19937& rng;
    std::uniform_int_distribution<size_t> dist;
public:
    explicit CharGenerator(std::mt19937& r)
        : rng(r), dist(0, sizeof(CHARSET) - 2) {}

    char operator()() {
        return CHARSET[dist(rng)];
    }
};

struct CharPrinter {
    void operator()(char c) const { std::cout << c; }
};

struct CaseInsensitiveGreater {
    bool operator()(char a, char b) const {
        return std::tolower(static_cast<unsigned char>(a)) >
               std::tolower(static_cast<unsigned char>(b));
    }
};

template <typename Queue>
struct QueuePusher {
    Queue& q;
    explicit QueuePusher(Queue& target) : q(target) {}
    void operator()(char c) { q.push(c); }
};

void run_functional(size_t n, std::mt19937& rng) {
    std::cout << "\n--- 2. Funktionale Variante (Funktoren) ---\n";
    std::vector<char> vec(n);
    CharGenerator generator(rng);

    // Заполнение через std::generate
    auto t1 = std::chrono::high_resolution_clock::now();
    std::generate(vec.begin(), vec.end(), generator);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto fill_vec_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "Fill vector used time was: " << fill_vec_time << " us\n";
    std::cout << "Vector:\n";
    std::for_each(vec.begin(), vec.end(), CharPrinter{});
    std::cout << "\n";

    // Заполнение через std::for_each и функтор
    using QueueType = std::priority_queue<char, std::vector<char>, CaseInsensitiveGreater>;
    QueueType pq;
    QueuePusher<QueueType> pusher(pq);

    auto t3 = std::chrono::high_resolution_clock::now();
    std::for_each(vec.begin(), vec.end(), pusher);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto fill_queue_time = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "Fill queue used time was: " << fill_queue_time << " us\n";
    std::cout << "Queue:\n";

    // Рекурсивный вывод без цикла
    auto pop_and_print = [&pq](auto& self) -> void {
        if (pq.empty()) return;
        std::cout << pq.top();
        pq.pop();
        self(self);
    };
    pop_and_print(pop_and_print);
    std::cout << "\n";
}

// ==========================================
// 3. ЛЯМБДА-ВАРИАНТ (лямбда-выражения + STL)
// ==========================================
void run_lambda(size_t n, std::mt19937& rng) {
    std::cout << "\n--- 3. Lambda-Variante ---\n";
    std::uniform_int_distribution<size_t> dist(0, sizeof(CHARSET) - 2);

    auto rand_char = [&]() { return CHARSET[dist(rng)]; };
    auto comp = [](char a, char b) {
        return std::tolower(static_cast<unsigned char>(a)) >
               std::tolower(static_cast<unsigned char>(b));
    };

    std::vector<char> vec(n);

    // Заполнение с лямбдой
    auto t1 = std::chrono::high_resolution_clock::now();
    std::generate(vec.begin(), vec.end(), rand_char);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto fill_vec_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "Fill vector used time was: " << fill_vec_time << " us\n";
    std::cout << "Vector:\n";
    std::for_each(vec.begin(), vec.end(), [](char c) { std::cout << c; });
    std::cout << "\n";

    // Очередь с лямбда-компаратором (C++20 decltype)
    auto t3 = std::chrono::high_resolution_clock::now();
    std::priority_queue<char, std::vector<char>, decltype(comp)> pq(comp);
    std::for_each(vec.begin(), vec.end(), [&pq](char c) { pq.push(c); });
    auto t4 = std::chrono::high_resolution_clock::now();
    auto fill_queue_time = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "Fill queue used time was: " << fill_queue_time << " us\n";
    std::cout << "Queue:\n";

    auto pop_and_print = [&pq](auto& self) -> void {
        if (pq.empty()) return;
        std::cout << pq.top();
        pq.pop();
        self(self);
    };
    pop_and_print(pop_and_print);
    std::cout << "\n";
}

// ==========================================
// ОСНОВНАЯ ТОЧКА ВХОДА
// ==========================================
int main() {
    std::cout << "Hello, Char World!\n";
    std::cout << "Enter the number of characters: ";

    size_t n = 0;
    if (!(std::cin >> n) || n == 0) {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    std::random_device rd;
    std::mt19937 rng(rd());

    run_classic(n, rng);
    run_functional(n, rng);
    run_lambda(n, rng);

    return 0;
}