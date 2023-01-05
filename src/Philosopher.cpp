#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

constexpr uint8_t NUM_OF_PHILOSOPHERS = 5;
std::array<std::mutex, NUM_OF_PHILOSOPHERS> mutexes;
std::mutex iostream_mt;
std::random_device rd;

int getRandomTime()
{
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<> distrib(250, 1500);
    return distrib(rng);
}

void think(const int i)
{
    {
        std::lock_guard lg{iostream_mt};
        std::cout << "Philosopher nr: " << i << " thinking..." << std::endl;
    }
    std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(getRandomTime()));
}

void takeFork(const int i)
{
    std::lock_guard lg{iostream_mt};
    std::cout << "Philosopher nr: " << i << " taking fork..." << std::endl;
}

void eat(const int i)
{
    {
        std::lock_guard lg{iostream_mt};
        std::cout << "Philosopher nr: " << i << " eating..." << std::endl;
    }
    std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(getRandomTime()));
}

void putFork(const int i)
{
    std::lock_guard lg{iostream_mt};
    std::cout << "Philosopher nr: " << i << " putting fork down..." << std::endl;
}

auto philosopher = [eatenPortions = 0](const auto i, auto dinnerReady) mutable
{
    do
    {
        think(i);
        {
            std::scoped_lock sl(mutexes.at(i), mutexes.at((i + 1) % 5));
            takeFork(i);
            eat(i);
            eatenPortions++;
            putFork(i);
        }
    } while (dinnerReady.get() == true);
    {
        std::lock_guard lg{iostream_mt};
        std::cout << "Philosopher nr: " << i << " finished dinner, ate " << eatenPortions << " portions" << std::endl;
    }
};