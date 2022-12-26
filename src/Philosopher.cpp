#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

enum class State
{
    THINKING,
    EATING
};

using namespace std::chrono_literals;

void think(const int i)
{
    std::cout << "Philosopher nr: " << i << " thinking..." << std::endl;
    std::this_thread::sleep_for(1s);
}

void takeFork(const int i, std::vector<State>& states, std::mutex& mt)
{
    std::lock_guard<std::mutex> lg{mt};
    std::cout << "Philosopher nr: " << i << " taking fork..." << std::endl;
    states.at(i) = State::EATING;
}

void eat(const int i)
{
    std::cout << "Philosopher nr: " << i << " eating..." << std::endl;
    std::this_thread::sleep_for(1s);
    
}

void putFork(const int i, std::vector<State>& states, std::mutex& mt)
{
    std::lock_guard<std::mutex> lg{mt};
    std::cout << "Philosopher nr: " << i << " puting fork down..." << std::endl;
    states.at(i) = State::THINKING;
}

auto philosopher = [remainingPortion = 5] (const auto i, auto states, auto mt) mutable
{
    while (remainingPortion != 0)
    {
        think(i);
        takeFork(i, states, mt);
        eat(i);
        remainingPortion--;
        putFork(i, states, mt);
    }
    std::cout << "Philosopher nr: " << i << " finished dinner" << std::endl;
};