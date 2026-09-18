#include <atomic>
#include <charconv>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <latch>
#include <mutex>
#include <numeric>
#include <shared_mutex>
#include <stdexcept>
#include <string_view>
#include <thread>
#include <vector>

constexpr int RUNS = 7;

uint64_t g_target = 0;
uint64_t g_counter = 0;
std::atomic<uint64_t> g_atomicCounter{0};
std::mutex g_mutex;
std::shared_mutex g_shareMutex;

template <typename Operation>
std::chrono::nanoseconds BenchmarkThreads(std::size_t thread_count, Operation&& oeration){}

std::chrono::nanoseconds BenchmarkMutex(std::size_t thread_count)
{
    g_counter = 0;
    const auto elapsed = BenchmarkThreads(thread_count, [](std::size_t, uint64_t operation){
        for (uint64_t index = 0; index < operation; ++index)
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            ++g_counter;
        }
    });
    return elapsed;
}

std::chrono::nanoseconds BenchmarkSharedMutex(std::size_t thread_count){}
std::chrono::nanoseconds BenchmarkAtomic(std::size_t thread_count){}
std::chrono::nanoseconds BenchmarkAtomicCas(std::size_t thread_count){}

template <typename Benchmark>
double Run(Benchmark&& benchmark)
{
    long double total_nanosecends = 0.0L;
    for (int run = 0; run < RUNS; ++run)
    {
        total_nanosecends += static_cast<long double>(benchmark().count());
    }
    return static_cast<double>(total_nanosecends / RUNS);
}

void PrintResult(std::string_view name, double total_nanosecends)
{
    const double nanosecend_per_operation = total_nanosecends / static_cast<double>(g_target);
    std::cout << std::left << std::setw(14) << name << std::right
              << total_nanosecends << "ns \t total, "
              << nanosecend_per_operation << " ns/op\n";
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        std::cerr << "Usage ./test_lock count\n";
        return -1;
    }

    g_counter = std::atoi(argv[1]);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "operations: " << g_target << ", average of " << RUNS << "runs \n\n";
    const std::vector<std::size_t> thread_counts = {1, 2, 4, 8, 16};

    for (const std::size_t thread_count : thread_counts)
    {
        std::cout << "threads: " << thread_count << "\n";
        // PrintResult();
    }
    
    return 0;
}

